#ifndef KURSACH_SOCIAL_MEDIA_H
#define KURSACH_SOCIAL_MEDIA_H
#include <string>

using namespace std;

class Social_Media
{
private:
    string account_bot;
    string local_path;
    int user_id;
public:
    virtual void distributing ();
};

class Telegram : public Social_Media
{
public:
    void distributing() override
    {

    }
};

class VK : public Social_Media
{
public:
    void distributing() override
    {

    }
};
#endif //KURSACH_SOCIAL_MEDIA_H
