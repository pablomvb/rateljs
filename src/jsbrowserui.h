#ifndef JSBROWSERUI_H
#define JSBROWSERUI_H

#include <QMainWindow>
class QWebEngineView;
class QWebEnginePage;

namespace Ui {
class JsBrowserUi;
}

class JsBrowserUi : public QMainWindow
{
    Q_OBJECT

public:
    explicit JsBrowserUi(QWidget *parent = nullptr);
    ~JsBrowserUi();

private:
    Ui::JsBrowserUi *ui;
    bool m_isRun = false;
    QWebEnginePage* m_page = nullptr;
    QWebEngineView* m_pageView = nullptr;

    void setRunStatus(bool isRun);
    void run();
    void stop();

    void handler_loadStart();
    void handler_loadProgess(int nProgess);
    void handler_loadEnd(bool isEnd);
};

#endif // JSBROWSERUI_H
