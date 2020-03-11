#ifndef SNIPPETDETECTOR_H
#define SNIPPETDETECTOR_H

#include <QString>

class SnippetDetector
{
    char m_table_col[11] = { '#', '/', 'B', 'D', 'E', 'G', 'I', 'N', 'P', 'S', 'T' };
    enum tokens { ee = 201, SD_Start = 301, SD_Type = 302, SD_TBegin = 401, SD_TEnd = 402 };
    //                               #         /   B        D   E   G   I          N   P   S        T  ERROR
    int m_table_state[15][12] = { {  1,       ee,  9,      ee, 13, ee, ee,        ee, ee,  3,      ee, ee },   // #|B|E|S
                                  { ee,        2, ee,      ee, ee, ee, ee,        ee, ee, ee,      ee, ee },   // #/
                                  { ee, SD_Start, ee,      ee, ee, ee, ee,        ee, ee, ee,      ee, ee },   // #//
                                  { ee,       ee, ee,      ee, ee, ee, ee,         4, ee, ee,      ee, ee },   // SN
                                  { ee,       ee, ee,      ee, ee, ee,  5,        ee, ee, ee,      ee, ee },   // SNI
                                  { ee,       ee, ee,      ee, ee, ee, ee,        ee,  6, ee,      ee, ee },   // SNIP
                                  { ee,       ee, ee,      ee, ee, ee, ee,        ee,  7, ee,      ee, ee },   // SNIPP
                                  { ee,       ee, ee,      ee,  8, ee, ee,        ee, ee, ee,      ee, ee },   // SNIPPE
                                  { ee,       ee, ee,      ee, ee, ee, ee,        ee, ee, ee, SD_Type, ee },   // SNIPPET
                                  { ee,       ee, ee,      ee, 10, ee, ee,        ee, ee, ee,      ee, ee },   // BE
                                  { ee,       ee, ee,      ee, ee, 11, ee,        ee, ee, ee,      ee, ee },   // BEG
                                  { ee,       ee, ee,      ee, ee, ee, 12,        ee, ee, ee,      ee, ee },   // BEGI
                                  { ee,       ee, ee,      ee, ee, ee, ee, SD_TBegin, ee, ee,      ee, ee },   // BEGIN
                                  { ee,       ee, ee,      ee, ee, ee, ee,        14, ee, ee,      ee, ee },   // EN
                                  { ee,       ee, ee, SD_TEnd, ee, ee, ee,        ee, ee, ee,      ee, ee } }; // END
    QString m_str;
    int m_strpos;
    int m_last_state;

    QString m_snippet_name;

public:
    enum StatementType{ SnippetBegin = 1, SnippetEnd = 2, Other = 0 };

    SnippetDetector()
    {

    }

    void eval(const QString& line)
    {
        m_str = line;
        m_strpos = 0;
        m_last_state = ee;
        m_snippet_name.clear();

        if( nextToken() != SD_Start ) return;
        if( consumeSeparators() < 1 ) return;

        if( nextToken() != SD_Type ) return;
        if( consumeSeparators() < 1 ) return;

        int s = nextToken();

        if( s > 400 )
        {
            if( s == SD_TBegin )
            {
                if( consumeSeparators() < 1 ) return;
                int str_start = m_strpos;
                int str_size = getNameSize();

                if( str_size < 1 ) return;

                m_snippet_name = m_str.mid( str_start, str_size );
            }

            consumeSeparators();
            if( m_strpos < m_str.size() ) return;

            m_last_state = s;
        }
    }

    int lastStringPosition() const
    {
        return static_cast<int>(m_strpos);
    }

    bool isSnippetBegin() const
    {
        return m_last_state == SD_TBegin;
    }

    bool isSnippetEnd() const
    {
        return m_last_state == SD_TEnd;
    }

    bool isError() const
    {
        return m_last_state == ee;
    }

    QString getSnippetName() const // solo con SnippetBegin
    {
        return m_snippet_name ;
    }

private:
    bool ignoreCharacter(const QChar& c)
    {
        if( c == ' ' ) return true;
        if( c == '\n' ) return true;

        return false;
    }

    int columnIndex(const QChar& c)
    {
        for( int idx = 0; idx < 11; ++idx ) if( m_table_col[idx] == c ) return idx;
        return 11;
    }

    int nextToken()
    {
        int state = 0;
        bool c_loop = true;

        while( c_loop )
        {
            if( m_strpos >= m_str.size() )
            {
                c_loop = false;
                continue;
            }

            QChar c = m_str.at( m_strpos );
            m_strpos++;

            state = m_table_state[ state ][ columnIndex( c ) ];

            if( state > 200 ) c_loop = false;
        }

        return state;
    }

    int consumeSeparators()
    {
        if( m_strpos >= m_str.size() ) return 0;

        int c_consumed = 0;
        bool c_loop = true;

        while( c_loop )
        {
            if( m_strpos < m_str.size() )
            {
                QChar c = m_str.at( m_strpos );
                m_strpos++;

                if( ignoreCharacter( c ) ) c_consumed++;
                else c_loop = false;
            }
            else c_loop = false;
        }

        return c_consumed;
    }

    bool ivn_char(const QChar& c)
    {
        if( c.isLetterOrNumber() ) return true;

        if( c == '_' ) return true;

        return false;
    }

    int getNameSize()
    {
        int str_size = 0;

        for( int idx = m_strpos; idx < m_str.size(); ++idx )
        {
            if( ! ivn_char( m_str.at( idx ) ) )
            {
                idx = m_str.size();
                continue;
            }

            str_size++;
        }

        return str_size;
    }
};

#endif // SNIPPETDETECTOR_H
