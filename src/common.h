#ifndef COMMON_H
#define COMMON_H

#include <QJSValue>
class Ratel;
class QJSEngine;
class QObject;

class Globals
{
    static Ratel* m_app;
    static QJSEngine* m_jsengine;

    Globals();

public:
    static void registerObject(QObject* ref);
    static Ratel* RatelJS();
    static QJSEngine* JSEngine();
};

class Utils
{
    explicit Utils();

public:
    //friend class GlobalObject;
    static bool evalError(const QJSValue& output);
    static void evalType(const QJSValue& value);
    static void exitError(const QString &obj, const QString &method, const QString &msg);
    static void setIndestructibleQObject( QObject* object );
};

#endif // COMMON_H
