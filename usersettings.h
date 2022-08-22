#ifndef USERSETTINGS_H
#define USERSETTINGS_H

#include <QColor>
#include "DrawingStratigies/drawstrategy.h"

class PenDrawStrategy;

// singleton
class UserSettings{
    static std::unique_ptr<UserSettings> instance;

    UserSettings();
public:
    UserSettings(UserSettings & userSettings) = delete;
    UserSettings &operator=(UserSettings & userSettings) = delete;

    // основыне настройки
    QColor color = Qt::black;
    int penWidth = 5;
    std::unique_ptr<DrawStrategy> drawStrategy;

    static UserSettings *getInstance();
};

#endif // USERSETTINGS_H
