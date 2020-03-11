#ifndef JSWEBBROWSER_H
#define JSWEBBROWSER_H

#include <QObject>
#include <QMap>
#include <QJSValue>
class BrowserTab;
class QWebEngineSettings;
class WebPageSettingsAttribute;

class Browser : public QObject
{
    Q_OBJECT
    QWebEngineSettings* m_settings;
    WebPageSettingsAttribute* m_listAttr;
    QList<BrowserTab*> m_tabs;

    QJSEngine* m_jsEngine;

public:
    explicit Browser(QObject *parent = nullptr);
    ~Browser();

signals:

public slots:
    QObject *newTab();
    QJSValue settings() const;
    QJSValue settings(const QString& key) const;
};

#endif // JSWEBBROWSER_H
