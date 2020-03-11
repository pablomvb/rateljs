#include "common.h"
#include "ratel.h"
#include <QJSEngine>
#include <QQmlEngine>
#include <QDebug>

Globals::Globals()
{
    
}

void Globals::registerObject(QObject *ref)
{
    if( Ratel* obj = dynamic_cast<Ratel*>(ref) ) m_app = obj;
    else if( QJSEngine* obj = dynamic_cast<QJSEngine*>(ref) ) m_jsengine = obj;
}

Ratel *Globals::RatelJS()
{
    return m_app;
}

QJSEngine *Globals::JSEngine()
{
    return m_jsengine;
}

Utils::Utils()
{

}

bool Utils::evalError(const QJSValue &output)
{
    if( output.isError() )
    {
        qInfo().noquote()<<"Uncaught exception at line:"<<output.property("lineNumber").toInt();
        qInfo().noquote()<<output.toString();

        emit Globals::RatelJS()->exit(1);
        return true;
    }

    return false;
}

void Utils::evalType(const QJSValue &value)
{
    if( value.isBool() ) { qInfo()<<"Value Type: boolean"; }
    if( value.isDate() ) { qInfo()<<"Value Type: date"; }
    if( value.isNull() ) { qInfo()<<"Value Type: null"; }
    if( value.isArray() ) { qInfo()<<"Value Type: array"; }
    if( value.isError() ) { qInfo()<<"Value Type: error"; }
    if( value.isNumber() ) { qInfo()<<"Value Type: number"; }
    if( value.isObject() ) { qInfo()<<"Value Type: object"; }
    if( value.isRegExp() ) { qInfo()<<"Value Type: regexp"; }
    if( value.isString() ) { qInfo()<<"Value Type: string"; }
    if( value.isQObject() ) { qInfo()<<"Value Type: qobject"; }
    if( value.isVariant() ) { qInfo()<<"Value Type: variant"; }
    if( value.isCallable() ) { qInfo()<<"Value Type: callable || function"; }
    if( value.isUndefined() ) { qInfo()<<"Value Type: undefined"; }
    if( value.isQMetaObject() ) { qInfo()<<"Value Type: qmetaobject"; }
}

void Utils::exitError(const QString& obj, const QString& method, const QString& msg)
{
    qInfo().noquote()<<"ERROR!!! in"<<obj
                   <<"\n   Method :"<<method
                   <<"\n   Message:"<<msg;
    emit Globals::RatelJS()->exit(1);
}

void Utils::setIndestructibleQObject(QObject *object)
{
    QQmlEngine::setObjectOwnership( object, QQmlEngine::CppOwnership );
}
