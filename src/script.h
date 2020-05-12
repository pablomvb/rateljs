#ifndef SCRIPT_H
#define SCRIPT_H

//#include <QString>
#include <QMap>

class Script
{
    QString m_filename;
    QString m_script;
    QMap<QString,QString*> m_snippets;

public:
    Script();
    
    QString filename() const;
    QString string() const;
    QString& snippet(const QString& key) const;
    QStringList keys() const;
};

#endif // SCRIPT_H
