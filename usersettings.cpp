#include "usersettings.h"

UserSettings *UserSettings::instance = nullptr;

UserSettings *UserSettings::getInstance(){
    if(instance == nullptr){
        instance = new UserSettings();
    }
    return instance;
}


