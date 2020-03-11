#include "rateloptions.h"
#include <QFile>
#include "snippetdetector3.h"
#include <QDebug>

RatelOptions::RatelOptions() : m_printHelp(false)
{
    m_fileName.clear();
}

bool RatelOptions::readCommandLine(QStringList args)
{
    bool e = false;

    while( ! args.isEmpty() && ! e )
    {
        QString arg = args.takeFirst();

        if( arg.startsWith(QLatin1Char('-')) )
        {
            if( arg == QLatin1String("-h") )
            {
                m_printHelp = true;
            }
            else if( arg == QLatin1String("-t") )
            {
                m_timeout = args.takeFirst().toInt(&e);
                if(e) m_lastError = QLatin1String("Invalid value for Timeout: ");
            }
            else
            {
                m_lastError = QLatin1String("Unknown option: ") + arg;
                e = true;
            }
        }
        else
        {
            if( m_fileName.isEmpty() )
            {
                m_fileName = arg;
            }
            else
            {
                m_lastError = QLatin1String("Many arguments: ") + arg;
                e = true;
            }
        }
    }

    if( e ) return false;

    return readScriptFile( m_fileName );
}

QString RatelOptions::lastError() const
{
    return m_lastError;
}

bool RatelOptions::printHelp() const
{
    return m_printHelp;
}

QString RatelOptions::scriptName() const
{
    return m_fileName;
}

QString RatelOptions::script() const
{
    return this->m_script;
}

QString RatelOptions::snippet(const QString &key) const
{
    return *m_scriptSnippets.value(key,new QString(""));
}

QStringList RatelOptions::snippetList() const
{
    return m_scriptSnippets.keys();
}

int RatelOptions::timeout() const
{
    return m_timeout;
}

bool RatelOptions::readScriptFile(const QString filename)
{
    QFile jsfile(filename);

    if( ! jsfile.exists() )
    {
        m_lastError = QLatin1String("File does not exist: ") + filename;
        return false;
    }

    if( ! jsfile.open( QFile::ReadOnly ) )
    {
        m_lastError = QLatin1String("Can't open file: ") + filename;
        return false;
    }

    int  fileLineNumber = 0;

    bool readingSnippet = false;
    QString* snippetBuffer = nullptr;

    bool cStatus = true;

    SnippetDetector3 eSnippet;

    while( !jsfile.atEnd() && cStatus )
    {
        fileLineNumber++;

        QString bufferLine = jsfile.readLine();

        // detect snippet
        if( bufferLine[0] == QLatin1Char('#') )
        {
            int out = eSnippet.eval(bufferLine);

            if( out == SnippetDetector3::SnippetBegin && !readingSnippet )
            {
                snippetBuffer = new QString;
                snippetBuffer->fill('\n',fileLineNumber);
                m_scriptSnippets.insert( eSnippet.name(), snippetBuffer );
                qDebug()<<"# INFO read snippet, name:"<<eSnippet.name();

                readingSnippet = true;
            }
            else if( out == SnippetDetector3::SnippetEnd && readingSnippet )
            {
                snippetBuffer = nullptr;
                readingSnippet = false;
            }
            else
            {
                m_lastError = QString("%1\nERROR in script line %2 :\n   ").arg(eSnippet.lastError()).arg(fileLineNumber) + bufferLine;
                cStatus = false;
            }

            m_script.append(QLatin1String("\n"));
            continue;
        }

        if( readingSnippet )
        {
            snippetBuffer->append(bufferLine);
            m_script.append(QLatin1String("\n"));
        }
        else m_script.append(bufferLine);
    }

    return cStatus;
}
