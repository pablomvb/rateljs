#ifndef WEBPAGE_H
#define WEBPAGE_H

#include <QObject>
#include <QWebEnginePage>
class BrowserTab;

class WebPage : public QWebEnginePage
{
    Q_OBJECT
    BrowserTab* m_browserTab;

public:
    explicit WebPage(BrowserTab *parent = nullptr);
    ~WebPage();

signals:
    void navigationRequested(const QUrl& url, QWebEnginePage::NavigationType type, bool isMainFrame, bool isNavigationLocked);

protected:
    virtual bool acceptNavigationRequest(const QUrl &url, QWebEnginePage::NavigationType type, bool isMainFrame) final;
};

#endif // WEBPAGE_H
