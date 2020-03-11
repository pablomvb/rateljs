#ifndef BROWSERWINDOW_H
#define BROWSERWINDOW_H

#include <QObject>
#include <QtQml/QJSValue>
class BrowserTab;
class QWebEngineView;
class QWidget;
class QFrame;
class QLineEdit;
class QHBoxLayout;
class QVBoxLayout;

class BrowserWindow : public QObject
{
    Q_OBJECT
    BrowserTab* m_tab;

    QWidget* m_window;
    bool m_autoUpdateTitle;

    QFrame* m_addressBar;
    QLineEdit* m_txtAddress;

    QFrame* m_toolBar;

    QWebEngineView* m_pageView;

    Q_PROPERTY(QString title READ windowTitle WRITE setWindowTitle)
    Q_PROPERTY(bool autoUpdateTitle READ autoUpdateWindowTitle WRITE setAutoUpdateWindowTitle)

public:
    explicit BrowserWindow(BrowserTab *parent = nullptr);
    ~BrowserWindow() override;

    bool eventFilter(QObject *watched, QEvent *event) override;

    void setWindowTitle(const QString& title);
    QString windowTitle() const;

    void setAutoUpdateWindowTitle(bool update);
    bool autoUpdateWindowTitle() const;

signals:
    void windowClose();

public slots:
    void open();
    void close();
    void pageNull();

private:
    void updateWindowTitle(const QString title);
};

#endif // BROWSERWINDOW_H
