#ifndef WEBPAGESETTINGSATTRIBUTE_H
#define WEBPAGESETTINGSATTRIBUTE_H

#include <QWebEngineSettings>
#include <QString>
#include <QMap>

class WebPageSettingsAttribute
{
    QMap<int,QString> m_attrIntString;
    QMap<QString,int> m_attrStringInt;
public:
    WebPageSettingsAttribute()
    {
        addAttribute(QWebEngineSettings::AutoLoadImages,"AutoLoadImages");
        addAttribute(QWebEngineSettings::JavascriptEnabled,"JavascriptEnabled");
        addAttribute(QWebEngineSettings::JavascriptCanOpenWindows,"JavascriptCanOpenWindows");
        addAttribute(QWebEngineSettings::JavascriptCanAccessClipboard,"JavascriptCanAccessClipboard");
        addAttribute(QWebEngineSettings::LinksIncludedInFocusChain,"LinksIncludedInFocusChain");
        addAttribute(QWebEngineSettings::LocalStorageEnabled,"LocalStorageEnabled");
        addAttribute(QWebEngineSettings::LocalContentCanAccessRemoteUrls,"LocalContentCanAccessRemoteUrls");
        addAttribute(QWebEngineSettings::XSSAuditingEnabled,"XSSAuditingEnabled");
        addAttribute(QWebEngineSettings::SpatialNavigationEnabled,"SpatialNavigationEnabled");
        addAttribute(QWebEngineSettings::LocalContentCanAccessFileUrls,"LocalContentCanAccessFileUrls");
        addAttribute(QWebEngineSettings::HyperlinkAuditingEnabled,"HyperlinkAuditingEnabled");
        addAttribute(QWebEngineSettings::ScrollAnimatorEnabled,"ScrollAnimatorEnabled");
        addAttribute(QWebEngineSettings::ErrorPageEnabled,"ErrorPageEnabled");
        addAttribute(QWebEngineSettings::PluginsEnabled,"PluginsEnabled");
        addAttribute(QWebEngineSettings::FullScreenSupportEnabled,"FullScreenSupportEnabled");
        addAttribute(QWebEngineSettings::ScreenCaptureEnabled,"ScreenCaptureEnabled");
        addAttribute(QWebEngineSettings::WebGLEnabled,"WebGLEnabled");
        addAttribute(QWebEngineSettings::Accelerated2dCanvasEnabled,"Accelerated2dCanvasEnabled");
        addAttribute(QWebEngineSettings::AutoLoadIconsForPage,"AutoLoadIconsForPage");
        addAttribute(QWebEngineSettings::TouchIconsEnabled,"TouchIconsEnabled");
        addAttribute(QWebEngineSettings::FocusOnNavigationEnabled,"FocusOnNavigationEnabled");
        addAttribute(QWebEngineSettings::PrintElementBackgrounds,"PrintElementBackgrounds");
        addAttribute(QWebEngineSettings::AllowRunningInsecureContent,"AllowRunningInsecureContent");
        addAttribute(QWebEngineSettings::AllowGeolocationOnInsecureOrigins,"AllowGeolocationOnInsecureOrigins");
        addAttribute(QWebEngineSettings::AllowWindowActivationFromJavaScript,"AllowWindowActivationFromJavaScript");
        addAttribute(QWebEngineSettings::ShowScrollBars,"ShowScrollBars");
        addAttribute(QWebEngineSettings::PlaybackRequiresUserGesture,"PlaybackRequiresUserGesture");
        addAttribute(QWebEngineSettings::JavascriptCanPaste,"JavascriptCanPaste");
        addAttribute(QWebEngineSettings::WebRTCPublicInterfacesOnly,"WebRTCPublicInterfacesOnly");
    }

    QWebEngineSettings::WebAttribute stringToKey(const QString& name) const
    {
        return static_cast<QWebEngineSettings::WebAttribute>( m_attrStringInt.value(name) );
    }

    QString keyToString(QWebEngineSettings::WebAttribute code) const
    {
        return m_attrIntString.value(code);
    }

    bool existsKey(const QString& name) const
    {
        return m_attrStringInt.contains(name);
    }

    bool existsKey( QWebEngineSettings::WebAttribute code) const
    {
        return m_attrIntString.contains(code);
    }

    QStringList keyNames() const
    {
        return m_attrStringInt.keys();
    }

    QList<int> keyCodes() const
    {
        return m_attrIntString.keys();
    }

private:
    void addAttribute(QWebEngineSettings::WebAttribute code, const QString& name)
    {
        m_attrIntString.insert(code,name);
        m_attrStringInt.insert(name,code);
    }
};

#endif // WEBPAGESETTINGSATTRIBUTE_H
