#include "webpage.h"
#include "browsertab.h"
#include <QDebug>

WebPage::WebPage(BrowserTab *parent) : QWebEnginePage(parent), m_browserTab(parent)
{

}

WebPage::~WebPage()
{
    qDebug()<<"# DELETE WebPage of tab:"<<m_browserTab->tabID();
}

bool WebPage::acceptNavigationRequest(const QUrl &url, QWebEnginePage::NavigationType type, bool isMainFrame)
{
    bool isNavigationLocked = m_browserTab->navigationLocked();

    emit navigationRequested(url,type,isMainFrame,isNavigationLocked);

    return !isNavigationLocked;
}
