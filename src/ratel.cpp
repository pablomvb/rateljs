#include "ratel.h"
#include <QCoreApplication>
#include <QJSEngine>
#include <QFile>
#include <QTimer>
#include <QThread>
#include <QRegularExpression>
#include "console.h"
#include "browser.h"
#include "jseditor.h"
#include "common.h"
#include "rateloptions.h"
#include <QDebug>


Ratel::Ratel(QObject *parent) : QObject(parent),
    m_jsEngine(new QJSEngine),
    m_opts(new RatelOptions),
    mIPCChannelMode(DisableIPC),
    mFilterMode(DisableFilter),
    m_appTimeOut(0)
{
    Globals::registerObject(m_jsEngine);
    m_scriptArgs = QCoreApplication::arguments();
    m_scriptArgs.removeFirst();
}

Ratel::~Ratel()
{
    delete m_jsEngine;
    qDebug()<<"# DELETE Ratel";
}

void Ratel::start()
{
    if( ! m_opts->readCommandLine( m_scriptArgs ) )
    {
        qInfo().noquote().nospace()<<m_opts->lastError();
        emit exit(1);
        return;
    }

    if( m_opts->printHelp() )
    {
        qInfo()<<"Use: rateljs [OPTIONS] script_file";
        emit exit(0);
        return;
    }

    if( m_opts->timeout() > 0 )
    {
        m_appTimeOut = m_opts->timeout();
        QTimer* app_killer = new QTimer;
        connect(app_killer,&QTimer::timeout,[this]{
            qInfo()<<"App reached the allowed time of "<<this->m_appTimeOut<<" second(s) to run the script.";
            emit this->exit(2);
        });
    }

    qDebug().noquote()<<"Snippets:"<<m_opts->snippetList().join(", ");

    initializeJSEngine();

    qDebug().noquote()<<"# INFO inject script file:"<<m_opts->scriptName();

    QJSValue out = m_jsEngine->evaluate( m_opts->script(), m_opts->scriptName() );

    if( Utils::evalError(out) )
    {
        qInfo().noquote()<<"Can't inject file:"<<m_opts->scriptName();
        emit exit(1);
    }
}

void Ratel::stop()
{
    m_jsEngine->collectGarbage();
}

void Ratel::initializeJSEngine()
{
    auto* cls = new Console;
    QJSValue console = m_jsEngine->newQObject( cls );
    Utils::setIndestructibleQObject(cls);
    m_jsEngine->globalObject().setProperty("console",console);

    auto* bws = new Browser;
    QJSValue browser = m_jsEngine->newQObject( bws );
    Utils::setIndestructibleQObject( bws );
    m_jsEngine->globalObject().setProperty("browser",browser);

    QJSValue ratel = m_jsEngine->newQObject(this);
    Utils::setIndestructibleQObject( this );
    m_jsEngine->globalObject().setProperty("ratel",ratel);
    m_jsEngine->globalObject().setProperty("setInterval",ratel.property("setInterval"));
    m_jsEngine->globalObject().setProperty("clearInterval",ratel.property("clearInterval"));
    m_jsEngine->globalObject().setProperty("setTimeout",ratel.property("setTimeout"));
    m_jsEngine->globalObject().setProperty("clearTimeout",ratel.property("clearTimeout"));
}

void Ratel::handleTimerShot(QObject *timer)
{
    QJSValue handler = m_timerHandlers.value(timer);
    handler.call();
}

QObject *Ratel::createTimer(bool singleShot, int interval, const QJSValue &handler)
{
    QTimer* t = new QTimer;
    Utils::setIndestructibleQObject(t);
    t->setSingleShot(singleShot);
    t->setInterval(interval);
    m_timerHandlers.insert(t,handler);
    connect(t,&QTimer::timeout,[=]{ this->handleTimerShot(t); });
    t->start();
    return t;
}

void Ratel::destroyTimer(const QJSValue &ref)
{
    if( ! ref.isQObject() ) return;

    QTimer* timer = dynamic_cast<QTimer*>(ref.toQObject());

    if( timer )
    {
        disconnect(timer);
        timer->stop();
        m_timerHandlers.remove(timer);
        timer->deleteLater();
    }
}

QStringList Ratel::args() const
{
    return m_scriptArgs;
}

QObject *Ratel::setInterval(int interval, const QJSValue &handler)
{
    return createTimer(false,interval,handler);
}

void Ratel::clearInterval(const QJSValue &ref)
{
    destroyTimer(ref);
}

QObject *Ratel::setTimeout(int interval, const QJSValue &handler)
{
    return createTimer(true,interval,handler);
}

void Ratel::clearTimeout(const QJSValue &ref)
{
    destroyTimer(ref);
}

QString Ratel::snippet(const QJSValue &ref) const
{
    return m_opts->snippet(ref.toString());
}
