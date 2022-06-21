#include "usersettings.h"
#include "pendrawstrategy.h"

std::unique_ptr<UserSettings> UserSettings::instance = nullptr;

UserSettings::UserSettings() : drawStrategy(std::make_unique<PenDrawStrategy>())
{

}

UserSettings *UserSettings::getInstance(){
    if(instance == nullptr){
        instance = std::unique_ptr<UserSettings>(new UserSettings);
    }
    return instance.get();
}


