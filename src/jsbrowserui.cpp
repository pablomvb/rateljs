#include "jsbrowserui.h"
#include "ui_jsbrowserui.h"
#include <QWebEnginePage>
#include <QWebEngineView>
#include <QVBoxLayout>
#include <QDebug>

JsBrowserUi::JsBrowserUi(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::JsBrowserUi)
{
    ui->setupUi(this);

    setRunStatus(false);

    connect(ui->btnPlay,&QPushButton::clicked,this,&JsBrowserUi::run);
    connect(ui->btnStop,&QPushButton::clicked,this,&JsBrowserUi::stop);
}

JsBrowserUi::~JsBrowserUi()
{
    delete ui;
}

void JsBrowserUi::setRunStatus(bool isRun)
{
    m_isRun = isRun;

    if(this->m_isRun)
    {
        ui->btnPlay->setDisabled(true);
        ui->btnStop->setEnabled(true);
    }
    else
    {
        ui->btnPlay->setEnabled(true);
        ui->btnStop->setDisabled(true);
    }
}

void JsBrowserUi::run()
{
    qDebug()<<"run";

    QString uri = ui->txtUri->text().simplified();
    QString code = ui->txtCode->toPlainText();

    if(uri.isEmpty())
    {
        qDebug()<<"uri empty";
        return;
    }

    if(!uri.startsWith("http"))
    {
        uri.prepend("https://");
    }

    code.prepend("window.location = \""+uri+"\"");

    m_page = new QWebEnginePage();

    if(ui->swithShowBrowser->isChecked())
    {
        //QWidget* w = new QWidget(this);
        m_pageView = new QWebEngineView();
        m_pageView->setPage(m_page);
        m_page->setView(m_pageView);
        m_pageView->resize(600,480);
        m_pageView->show();
        /*QVBoxLayout* grid = new QVBoxLayout(w);
        grid->addWidget(m_pageView);
        w->show();*/
    }

    connect(m_page,&QWebEnginePage::loadStarted,this,&JsBrowserUi::handler_loadStart);
    connect(m_page,&QWebEnginePage::loadProgress,this,&JsBrowserUi::handler_loadProgess);
    connect(m_page,&QWebEnginePage::loadFinished,this,&JsBrowserUi::handler_loadEnd);

    m_page->runJavaScript(code);

    setRunStatus(true);
}

void JsBrowserUi::stop()
{
    disconnect(m_page);

    if(m_pageView)
    {
        //delete m_pageView;
        m_pageView->deleteLater();
    }

    //delete m_page;
    m_page->deleteLater();

    setRunStatus(false);
}

void JsBrowserUi::handler_loadStart()
{
    qDebug()<<"page.load: started";
}

void JsBrowserUi::handler_loadProgess(int nProgess)
{
    qDebug()<<"page.load: "<<nProgess<<"%";
}

void JsBrowserUi::handler_loadEnd(bool isEnd)
{
    qDebug()<<"page.load: end is < "<<(isEnd?"true":"false")<<" >";
}
