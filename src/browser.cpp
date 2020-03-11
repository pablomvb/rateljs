#include "browser.h"
#include "browsertab.h"
#include "common.h"
#include <QJsonObject>
#include <QJSEngine>
#include "webpagesettingsattribute.h"

Browser::Browser(QObject *parent) : QObject( parent ),
    m_settings( QWebEngineSettings::defaultSettings() ),
    m_listAttr( new WebPageSettingsAttribute )
{

}

Browser::~Browser()
{
//    for( BrowserTab* tab : m_tabs ) tab->deleteLater();
    m_tabs.clear();
    delete m_listAttr;
    qDebug()<<"# DELETE Browser";
}

QObject* Browser::newTab()
{
    BrowserTab* tab = new BrowserTab;
    m_tabs.append( tab );
    tab->setTabID( m_tabs.indexOf( tab ) );
    return tab;
}

QJSValue Browser::settings() const
{
    QJsonObject list;

    for( int key : m_listAttr->keyCodes() )
    {
        QWebEngineSettings::WebAttribute ekey = static_cast<QWebEngineSettings::WebAttribute>(key);
        list.insert( m_listAttr->keyToString(ekey), m_settings->testAttribute(ekey) );
    }

    return Globals::JSEngine()->toScriptValue<QJsonObject>(list);
}

QJSValue Browser::settings(const QString &key) const
{
    if( ! m_listAttr->existsKey( key ) ) return QJSValue( QJSValue::NullValue );

    return QJSValue( m_settings->testAttribute( m_listAttr->stringToKey(key) ) );
}
