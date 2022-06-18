#ifndef USERSETTINGS_H
#define USERSETTINGS_H

#include <QColor>

// структура
struct UserSettings{
    QColor color = Qt::black;
    int penWidth = 10;
};

#endif // USERSETTINGS_H
