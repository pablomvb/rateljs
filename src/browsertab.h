#ifndef BROWSERTAB_H
#define BROWSERTAB_H

#include <QObject>
#include <QMetaEnum>
#include <QJSValue>
#include <QWebEnginePage>
class QWebEngineView;
class WebPage;

class BrowserTab : public QObject
{
    Q_OBJECT
    int m_tabID;
    WebPage* m_page;
    QJSValue m_onLoadFinished;
    bool m_navigationLocked;
    QMetaEnum m_navigationTypes;
    QJSValue m_onNavigationRequested;

    QObject* m_window;
    QJSValue m_onWindowClose;

    Q_PROPERTY(int tabID READ tabID)
    Q_PROPERTY(QString url READ url)
    Q_PROPERTY(QString title READ title)
    Q_PROPERTY(QJSValue onLoadFinished READ onLoadFinished WRITE setOnLoadFinished)
    Q_PROPERTY(bool navigationLocked READ navigationLocked WRITE setNavigationLocked)
    Q_PROPERTY(QJSValue onNavigationRequested READ onNavigationRequested WRITE setOnNavigationRequested)
    Q_PROPERTY(QObject* window READ window)
    Q_PROPERTY(QJSValue onWindowClose READ onWindowClose WRITE setOnWindowClose)

public:
    explicit BrowserTab(QObject *parent = nullptr);
    ~BrowserTab();

    void setTabID(int id);
    int tabID() const;

    QString url() const;
    QString title() const;

    void setOnLoadFinished(const QJSValue& handler);
    QJSValue onLoadFinished() const;

    void setNavigationLocked(bool locker);
    bool navigationLocked() const;

    void setOnNavigationRequested(const QJSValue& handler);
    QJSValue onNavigationRequested() const;

    QObject* window() const;

    void setOnWindowClose(const QJSValue& handler);
    QJSValue onWindowClose() const;

    QWebEnginePage* page();

signals:

public slots:
    void open(const QJSValue& uri, QJSValue handler = QJSValue(QJSValue::NullValue));
    QJSValue evaluate(QJSValue source);

private:
    void trigger_onLoadFinished(const bool& status);
#ifdef QT_DEBUG
    void trigger_onLoadStarted();
    void trigger_onLoadProgress(int nProgess);
#endif

    void trigger_onNavigationRequested(const QUrl& url, int type, bool isMainFrame, bool isNavigationLocked);

    void trigger_onWindowClose();

    QString strTabID() const;
};

#endif // BROWSERTAB_H
