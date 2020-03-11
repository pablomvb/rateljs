#ifndef RATELOPTIONS_H
#define RATELOPTIONS_H

#include <QMap>
#include <QStringList>

class RatelOptions
{
    QString m_fileName;
    QString m_script;
    QMap<QString,QString*> m_scriptSnippets;
    int m_timeout;

    bool m_printHelp;

    QString m_lastError;

public:
    RatelOptions();

    bool readCommandLine(QStringList args);

    QString lastError() const;

    bool printHelp() const;

    QString scriptName() const;
    QString script() const;
    QString snippet(const QString& key) const;
    QStringList snippetList() const;
    int timeout() const;

private:
    bool readScriptFile(const QString filename);

};

#endif // RATELOPTIONS_H
