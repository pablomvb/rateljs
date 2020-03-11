#include "console.h"
#include "common.h"
#include <QDebug>

Console::Console(QObject *parent) : QObject(parent)
{
    setObjectName(QLatin1String("console"));
}

Console::~Console()
{
    qDebug()<<"# DELETE Console";
}

void Console::log(const QJSValue &args)
{
    //Utils::evalType(args);
    qInfo().noquote()<<args.toString();
}
