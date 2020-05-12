#ifndef OPTIONS_H
#define OPTIONS_H

#include <QMap>
#include <QStringList>

class Options
{
    int m_timeout;

public:
    Options();

    int timeout() const;
};

#endif // OPTIONS_H
