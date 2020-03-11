#include "browsertab.h"
#include "browserwindow.h"
#include "webpage.h"
#include "common.h"

#include <QWebEngineProfile>

#include <QtQml/QJSEngine>
#include <QUrl>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>

BrowserTab::BrowserTab(QObject *parent) : QObject(parent),
    m_tabID(-1),
    m_page(new WebPage(this)),
    m_onLoadFinished(QJSValue(QJSValue::NullValue)),
    m_navigationLocked(false),
    m_navigationTypes(QMetaEnum::fromType<QWebEnginePage::NavigationType>()),
    m_onNavigationRequested(QJSValue(QJSValue::NullValue)),
    m_window(new BrowserWindow(this)),
    m_onWindowClose(QJSValue(QJSValue::NullValue))
{
#ifdef QT_DEBUG
    connect( m_page, &WebPage::loadStarted, this, &BrowserTab::trigger_onLoadStarted );
    connect( m_page, &WebPage::loadProgress, this, &BrowserTab::trigger_onLoadProgress );
#endif
    connect( m_page, &WebPage::loadFinished, this, &BrowserTab::trigger_onLoadFinished );
    connect( m_page, &WebPage::navigationRequested, this, &BrowserTab::trigger_onNavigationRequested );

    Utils::setIndestructibleQObject( m_page );
    Utils::setIndestructibleQObject( m_window );
}

BrowserTab::~BrowserTab()
{
    //m_window->deleteLater();
    //m_page->deleteLater();
    qDebug().noquote()<<"# DELETE"<<strTabID();
}

void BrowserTab::setTabID(int id)
{
    m_tabID = id;
    setObjectName( QString::number( id ) );
}

int BrowserTab::tabID() const
{
    return m_tabID;
}

QString BrowserTab::url() const
{
    return m_page->url().toString();
}

QString BrowserTab::title() const
{
    return m_page->title();
}

void BrowserTab::setOnLoadFinished(const QJSValue &handler)
{
    m_onLoadFinished = handler;
}

QJSValue BrowserTab::onLoadFinished() const
{
    return m_onLoadFinished;
}

void BrowserTab::setNavigationLocked(bool locker)
{
    m_navigationLocked = locker;
}

bool BrowserTab::navigationLocked() const
{
    return m_navigationLocked;
}

void BrowserTab::setOnNavigationRequested(const QJSValue &handler)
{
    m_onNavigationRequested = handler;
}

QJSValue BrowserTab::onNavigationRequested() const
{
    return m_onNavigationRequested;
}

QObject *BrowserTab::window() const
{
    return m_window;
}

void BrowserTab::setOnWindowClose(const QJSValue &handler)
{
    m_onWindowClose = handler;
}

QJSValue BrowserTab::onWindowClose() const
{
    return m_onWindowClose;
}

QWebEnginePage *BrowserTab::page()
{
    return m_page;
}

void BrowserTab::open(const QJSValue &uri, QJSValue handler)
{
    if( ! uri.isString() )
    {
        Utils::exitError(strTabID(),"open","typeof uri != 'string'");
        return;
    }

    // if( ! uri.startsWith(QLatin1String("http")) ) uri.prepend(QLatin1String("https://"));
    QUrl url = QUrl::fromUserInput( uri.toString() );

    if( url.isEmpty() )
    {
        Utils::exitError(strTabID(),"open","uri is empty");
        return;
    }

    if( ! url.isValid() )
    {
        Utils::exitError(strTabID(),"open","uri is not valid.");
        return;
    }

    if( ! handler.isNull() ) m_onLoadFinished = handler;

    m_page->load( url );
}

QJSValue BrowserTab::evaluate(QJSValue source)
{
    if( ! source.isString() )
    {
        Utils::exitError(strTabID(),"evaluate","typeof source != 'string'");
        return QJSValue(QJSValue::NullValue);
    }

    QVariant js_out;
    QEventLoop wait_js_finished;

    m_page->runJavaScript( source.toString(), [&wait_js_finished,&js_out](const QVariant& out)
    {
        js_out = out;
        wait_js_finished.exit();
    });

    wait_js_finished.exec();

    qDebug().noquote().nospace()<<"# INFO "<<strTabID()<<".evaluate: typeof $return = "<<js_out.typeName();

    if( js_out.type() == QVariant::String )
    {
        QString str = js_out.toString();
        if( str.startsWith('{') && str.endsWith('}') )
        {
            qDebug().noquote().nospace()<<"# INFO "<<strTabID()<<".evaluate:"
                                       <<" detected possible JsonObject in $return, try read as json";
            QJsonParseError parserError;
            QJsonObject obj = QJsonDocument::fromJson(str.toLatin1(),&parserError).object();
            if( parserError.error == QJsonParseError::NoError )
                return Globals::JSEngine()->toScriptValue<QJsonObject>(obj);
        }
    }

    QJSValue value = Globals::JSEngine()->toScriptValue<QVariant>(js_out);
    if( Utils::evalError(value) ) return QJSValue( QJSValue::NullValue );
    return value;
}

void BrowserTab::trigger_onLoadFinished(const bool &status)
{
    qDebug().noquote().nospace()<<"# INFO "<<strTabID()<<": load finished, with status = "<<( status ? "true" : "false" );

    if( ! m_onLoadFinished.isNull() )
    {
        Utils::evalError( m_onLoadFinished.call( QJSValueList() << status ) );
    }
}

#ifdef QT_DEBUG
void BrowserTab::trigger_onLoadStarted()
{
    qDebug().noquote().nospace()<<"# INFO "<<strTabID()<<": load started";
}

void BrowserTab::trigger_onLoadProgress(int nProgess)
{
    qDebug().noquote().nospace()<<"# INFO "<<strTabID()<<": loading "<<nProgess<<"%";
}
#endif

void BrowserTab::trigger_onNavigationRequested(const QUrl &url, int type, bool isMainFrame, bool isNavigationLocked)
{
    QWebEnginePage::NavigationType navType = static_cast<QWebEnginePage::NavigationType>(type);

    if( ! m_onNavigationRequested.isNull() )
    {
        QJSValueList args;
        args << url.toString() << m_navigationTypes.valueToKey(navType) << isNavigationLocked << isMainFrame;
        Utils::evalError( m_onNavigationRequested.call( args ) );
    }
}

void BrowserTab::trigger_onWindowClose()
{
    if( ! m_onWindowClose.isNull() ) Utils::evalError( m_onWindowClose.call() );
}

QString BrowserTab::strTabID() const
{
    return QString("BrowserTab[ %1 ]").arg( tabID() );
}
