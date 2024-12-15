#ifndef KURSACH_TELEGRAM_H
#define KURSACH_TELEGRAM_H
#include <string>
#include "social_media.h"

void startBot(const std::string& photoPath, const std::string& message);

class Telegram : public Social_Media
{
public:
    explicit Telegram(const std::string &fileName) : Social_Media(fileName) {}

    virtual ~Telegram();

    void distributing(std::string file_name) override;
};

std::string readFileUtf8(const std::string& filePath);
std::string getFileExtension(const std::string& filePath);
#endif //KURSACH_TELEGRAM_H
