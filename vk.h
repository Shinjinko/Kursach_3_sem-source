#ifndef KURSACH_VK_H
#define KURSACH_VK_H
#include <string>
#include "social_media.h"

std::string httpRequest(const std::string& url);
void sendMessage(int userId, const std::string& message);
void sendPhoto(int userId, const std::string& photoId);
void sendPhotoFromPath(int userId, const std::string& filePath);
std::string uploadPhoto(const std::string& filePath);

class VK : public Social_Media
{
public:
    explicit VK(const std::string &fileName) : Social_Media(fileName) {}

    virtual ~VK();

    void distributing(std::string file_name) override;
};
#endif //KURSACH_VK_H
