#include "snippetdetector3.h"

SnippetDetector3::SnippetDetector3()
{

}

int SnippetDetector3::eval(const QString &str)
{
    int next_state = 0;
    bool loop_ctl = true;
    int strpos = 0;

    if( str.isEmpty() ) return -1;

    while(loop_ctl)
    {
        int col = nextColumn( str.at( strpos ).toLatin1() );
        next_state = mTableStates[ next_state ][ col ];

        if( next_state < 0 || next_state > 20 ) loop_ctl = false;

        strpos++;
    }

    if( next_state > 20 )
    {
        mBuffer = str.mid(strpos).trimmed();

        if( next_state == SnippetBegin )
        {
            if( str.at(strpos) != ' ' )
            {
                next_state = -1;
                m_lastError = "Snippet begin malformed.";
            }
            else if( mBuffer.isEmpty() )
            {
                next_state = -1;
                m_lastError = "Snippet name missing.";
            }
        }
        else if( next_state == SnippetEnd  )
        {
            if( ! mBuffer.isEmpty() )
            {
                next_state = -1;
                m_lastError = "Snippet end malformed.";
            }
        }
        else
        {
            next_state = -1;
            m_lastError = "SnippetDetector unknown error.";
        }
    }

    return next_state;
}

QString SnippetDetector3::name() const
{
    return mBuffer;
}

int SnippetDetector3::nextColumn(const char &c) const
{
    int col = nC;

    for (int pos=0; pos < nC; ++pos)
    {
        if( c == mTableCols[pos] )
        {
            col = pos;
            pos = nC;
        }
    }

    return col;
}

void SnippetDetector3::consumeSpaces()
{
    while( mBuffer[ mBufferPosition ] == ' ' )
    {
        mBufferPosition++;
    }
}

void SnippetDetector3::consumeBreakLine()
{
    if( mBuffer[ mBufferPosition ] == '\n' ) mBufferPosition++;
}

bool SnippetDetector3::existsName(int &start, int &end)
{
    start = mBufferPosition;

    while( isNameCharValid( mBuffer[ mBufferPosition ] ) )
    {
        mBufferPosition++;
    }

    end = mBufferPosition;

    return ( end - start ) > 0;
}

bool SnippetDetector3::isNameCharValid(const QChar &c)
{
    if( c.isLetterOrNumber() ) return true;

    if( c == '_' ) return true;

    return false;
}

QString SnippetDetector3::lastError() const
{
    return m_lastError;
}
