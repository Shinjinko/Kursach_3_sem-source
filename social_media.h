#ifndef SOCIAL_MEDIA_H
#define SOCIAL_MEDIA_H
#include <string>
#include <iostream>
#include "Exp.h"

#define BOT_TG "https://t.me/mgen_429_bot"
#define BOT_VK "https://vk.com/mgen_429_bot"

class Social_Media
{
protected:
    std::string account_bot;
public:
    std::string local_path;

    Social_Media(const std::string file_name) : local_path(file_name) {}

    virtual void distributing (std::string file_name);
};
#endif //SOCIAL_MEDIA_H