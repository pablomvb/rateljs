#ifndef JSBROWSER_H
#define JSBROWSER_H

#include <QObject>
#include <QMap>
#include <QJSValue>

class QWidget;
class QJSEngine;
class RatelOptions;

class Ratel : public QObject
{
    Q_OBJECT

    // Crazy and strange analogy
    // Ratel -> Tejon de la miel
    // Agresivo, igual que chrome con la memoria
    // QWebEngine api de chrome

    QJSEngine* m_jsEngine;
    QStringList m_scriptArgs;
    RatelOptions* m_opts;
    QMap<QObject*,QJSValue> m_timerHandlers;

    QWidget* m_editor;

    enum IPCChannelMode {DisableIPC,TCP,Pipe};
    IPCChannelMode mIPCChannelMode;

    enum RequestFilterMode {DisableFilter,BlackList,WhiteList};
    RequestFilterMode mFilterMode;

    int m_appTimeOut;

public:
    explicit Ratel(QObject *parent = nullptr);
    ~Ratel();

    void start();
    void stop();

private:
    void initializeJSEngine();

    void handleTimerShot(QObject* timer);
    QObject* createTimer( bool singleShot, int interval, const QJSValue& handler );
    void destroyTimer( const QJSValue& ref );

signals:
    void exit(int code = 0);

public slots:
    QStringList args() const;
    QObject* setInterval( int interval, const QJSValue& handler );
    void clearInterval( const QJSValue& ref );
    QObject* setTimeout( int interval, const QJSValue& handler );
    void clearTimeout( const QJSValue& ref );
    QString snippet( const QJSValue& ref ) const;
};

#endif // JSBROWSER_H
