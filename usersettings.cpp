#include "usersettings.h"

std::unique_ptr<UserSettings> UserSettings::instance = nullptr;

UserSettings *UserSettings::getInstance(){
    if(instance == nullptr){
        instance = std::unique_ptr<UserSettings>(new UserSettings);
    }
    return instance.get();
}


