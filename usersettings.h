#ifndef USERSETTINGS_H
#define USERSETTINGS_H

#include <QColor>

// singleton
class UserSettings{
    static std::unique_ptr<UserSettings> instance;

    UserSettings() = default;
public:
    UserSettings(UserSettings & userSettings) = delete;
    UserSettings &operator=(UserSettings & userSettings) = delete;

    QColor color = Qt::black;
    int penWidth = 5;

    static UserSettings *getInstance();
};

#endif // USERSETTINGS_H
