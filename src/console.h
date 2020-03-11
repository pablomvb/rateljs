#ifndef JSCONSOLE_H
#define JSCONSOLE_H

#include <QObject>
#include <QJSValue>

class Console : public QObject
{
    Q_OBJECT
public:
    explicit Console(QObject *parent = nullptr);
    ~Console();

signals:


public slots:
    void log(const QJSValue& args);
};

#endif // JSCONSOLE_H
