#ifndef USERSETTINGS_H
#define USERSETTINGS_H

#include <QColor>

//// структура
//struct UserSettings{
//    QColor color = Qt::black;
//    int penWidth = 10;
//};

// singleton
class UserSettings{
    static UserSettings *instance;

    UserSettings() = default;
public:
    UserSettings(UserSettings & userSettings) = delete;
    UserSettings &operator=(UserSettings & userSettings) = delete;

    QColor color = Qt::black;
    int penWidth = 10;

    static UserSettings *getInstance();
};

#endif // USERSETTINGS_H
