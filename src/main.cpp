#include <QApplication>
#include "ratel.h"
#include "common.h"
#include <QTimer>
#include <QDebug>

Ratel* Globals::m_app = nullptr;
QJSEngine* Globals::m_jsengine = nullptr;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Ratel yeah;
    Globals::registerObject(&yeah);
    
    QTimer::singleShot(10,[&yeah]()
    {
        qDebug()<<"# STARTING ... let's go";
        yeah.start();
    });

    QObject::connect(&yeah,&Ratel::exit,[&a,&yeah](int ecode)
    {
        qDebug()<<"# EXITING ... wait";
        yeah.stop();
        a.exit(ecode);
    });

    qDebug()<<"# STARTING ... waiting for event loop";

    return a.exec();
}
