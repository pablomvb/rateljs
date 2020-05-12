#include "script.h"

Script::Script()
{
    
}

QString Script::filename() const
{
    return m_filename;
}

QString Script::string() const
{
    return m_script;
}

QString &Script::snippet(const QString &key) const
{
    return *m_snippets.value( key, new QString );
}

QStringList Script::keys() const
{
    return m_snippets.keys();
}
