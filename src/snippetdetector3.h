#ifndef SNIPPETDETECTOR3_H
#define SNIPPETDETECTOR3_H

#include <QString>

#define SB 21 // SNIPPET BEGIN
#define SE 22 // SNIPPET END
#define nC 12
#define tC ( nC + 1 )

class SnippetDetector3
{
    char mTableCols[nC] = { '#', '/', 'B', 'D', 'E', 'G', 'I', 'N', 'P', 'S', 'T', ' ' };
    //                             #   /   B   D   E   G   I   N   P   S   T   _
    int mTableStates[19][tC] = {{  1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }, // #
                                { -1,  2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }, // #/
                                { -1,  3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }, // #//
                                { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4, -1 }, // #//_
                                { -1, -1, -1, -1, -1, -1, -1, -1, -1,  5, -1,  4, -1 }, // #//_S
                                { -1, -1, -1, -1, -1, -1, -1,  6, -1, -1, -1, -1, -1 }, // #//_SN
                                { -1, -1, -1, -1, -1, -1,  7, -1, -1, -1, -1, -1, -1 }, // #//_SNI
                                { -1, -1, -1, -1, -1, -1, -1, -1,  8, -1, -1, -1, -1 }, // #//_SNIP
                                { -1, -1, -1, -1, -1, -1, -1, -1,  9, -1, -1, -1, -1 }, // #//_SNIPP
                                { -1, -1, -1, -1, 10, -1, -1, -1, -1, -1, -1, -1, -1 }, // #//_SNIPPE
                                { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 11, -1, -1 }, // #//_SNIPPET
                                { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 12, -1 }, // #//_SNIPPET_
                                { -1, -1, 13, -1, 17, -1, -1, -1, -1, -1, -1, 12, -1 }, // #//_SNIPPET_{B|E}
                                { -1, -1, -1, -1, 14, -1, -1, -1, -1, -1, -1, -1, -1 }, // #//_SNIPPET_BE
                                { -1, -1, -1, -1, -1, 15, -1, -1, -1, -1, -1, -1, -1 }, // #//_SNIPPET_BEG
                                { -1, -1, -1, -1, -1, -1, 16, -1, -1, -1, -1, -1, -1 }, // #//_SNIPPET_BEGI
                                { -1, -1, -1, -1, -1, -1, -1, SB, -1, -1, -1, -1, -1 }, // #//_SNIPPET_BEGIN
                                { -1, -1, -1, -1, -1, -1, -1, 18, -1, -1, -1, -1, -1 }, // #//_SNIPPET_EN
                                { -1, -1, -1, SE, -1, -1, -1, -1, -1, -1, -1, -1, -1 }};// #//_SNIPPET_END
    QString m_lastError;

public:
    enum Label{ SnippetBegin = SB, SnippetEnd = SE };

    SnippetDetector3();

    int eval(const QString& str);
    QString name() const;

    QString lastError() const;

private:
    QString mBuffer;
    int     mBufferPosition;
    int     mNameStar;
    int     mNameEnd;
    int nextColumn(const char& c) const;
    void consumeSpaces();
    void consumeBreakLine();
    bool existsName(int& start, int& end);
    bool isNameCharValid(const QChar& c);
};

#endif // SNIPPETDETECTOR3_H
