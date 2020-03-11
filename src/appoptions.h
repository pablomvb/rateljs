#ifndef RATELSETTINGS_H
#define RATELSETTINGS_H

#include <QMap>
#include <QStringList>

class RatelSettings
{
    QString m_jsFileName;
    QString m_jsFileData;
    QMap<QString,QString*> m_jsSnippets;

    int m_appTimeout;

public:
    RatelSettings();

    QString scriptFile() const;
    QString script() const;
    QString snippet(const QString& key) const;
    QStringList snippetKeyList() const;
    int timeout() const;

};

#endif // RATELSETTINGS_H
