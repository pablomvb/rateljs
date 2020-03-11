#include "browserwindow.h"
#include "browsertab.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QEvent>

#include <QIcon>
#include <QFrame>
#include <QLineEdit>
#include <QPushButton>
#include <QToolButton>
#include <QWebEngineView>

BrowserWindow::BrowserWindow(BrowserTab *parent) : QObject(parent),
    m_tab(parent),
    m_window(new QWidget),
    m_autoUpdateTitle(true),
    m_addressBar(new QFrame),
    m_txtAddress(new QLineEdit),
    m_toolBar(new QFrame),
    m_pageView(new QWebEngineView)
{
    m_window->setAttribute(Qt::WA_QuitOnClose,false);
    m_window->resize(600,450);

    auto* layoutAddressBar = new QHBoxLayout;
    layoutAddressBar->addWidget( m_txtAddress );
    m_addressBar->setLayout( layoutAddressBar );

    auto* btnBack = new QToolButton;
    btnBack->setIcon(QIcon( QLatin1String(":/nav-back.svg") ));
    btnBack->setToolTip(QLatin1String("Back"));

    auto* btnNext = new QToolButton;
    btnNext->setIcon(QIcon( QLatin1String(":/nav-forward.svg") ));
    btnNext->setToolTip(QLatin1String("Forward"));

    auto* btnUpdate = new QToolButton;
    btnUpdate->setIcon(QIcon( QLatin1String(":/nav-update.svg") ));
    btnUpdate->setToolTip(QLatin1String("Update"));

    auto* layoutToolBar = new QHBoxLayout;
    layoutToolBar->addWidget( btnBack );
    layoutToolBar->addWidget( btnNext );
    layoutToolBar->addWidget( btnUpdate );
    layoutToolBar->addItem( new QSpacerItem( 100, 16, QSizePolicy::MinimumExpanding ) );
    m_toolBar->setLayout( layoutToolBar );

    m_pageView->setSizePolicy( QSizePolicy( QSizePolicy::Minimum, QSizePolicy::MinimumExpanding ) );

    auto* layoutWindow = new QVBoxLayout;
    layoutWindow->setMargin(0);
    layoutWindow->setSpacing(0);
    layoutWindow->addWidget( m_addressBar );
    layoutWindow->addWidget( m_pageView );
    layoutWindow->addWidget( m_toolBar );
    m_window->setLayout( layoutWindow );
    m_window->installEventFilter(this);

    connect( m_pageView, &QWebEngineView::titleChanged, this, &BrowserWindow::updateWindowTitle );
}

BrowserWindow::~BrowserWindow()
{
    m_pageView->setPage( nullptr );
    m_pageView->deleteLater();
    //delete m_window->layout();
    delete m_window;
//    if( m_addressBar )
//    {
//        delete m_addressBar->layout();
//        delete m_addressBar;
//    }
//    delete m_toolBar->layout();
//    delete m_toolBar;

    qDebug()<<"# DELETE BrowserWindow";
}

bool BrowserWindow::eventFilter(QObject *watched, QEvent *event)
{
    if( watched == m_window && event->type() == QEvent::Close ) emit windowClose();

    return QObject::eventFilter(watched,event);
}

void BrowserWindow::setWindowTitle(const QString &title)
{
    m_window->setWindowTitle( title );
}

QString BrowserWindow::windowTitle() const
{
    return m_window->windowTitle();
}

void BrowserWindow::setAutoUpdateWindowTitle(bool update)
{
    m_autoUpdateTitle = update;
}

bool BrowserWindow::autoUpdateWindowTitle() const
{
    return m_autoUpdateTitle;
}

void BrowserWindow::open()
{
    m_pageView->setPage( m_tab->page() );
    m_window->show();
}

void BrowserWindow::close()
{
    m_window->hide();
    m_pageView->setPage( nullptr );
}

void BrowserWindow::pageNull()
{
    m_pageView->setPage( nullptr );
}

void BrowserWindow::updateWindowTitle(const QString title)
{
    if( m_autoUpdateTitle ) m_window->setWindowTitle( title );
}
