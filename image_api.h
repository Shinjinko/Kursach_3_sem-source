#ifndef IMAGE_API_H
#define IMAGE_API_H
#define GENERATE_JOKES_PHOTO_OUTPUT R"(D:\Proga\Turovec\Kursach\Meme Generator\custom\image)"

#include <vector>

std::string cleanBase64String(const std::string& encoded);

size_t WriteCallback_s(void* contents, size_t size, size_t nmemb, void* userp);

std::vector<unsigned char> base64Decode(const std::string& encoded);

int Image_Api(const std::string &prompt, int last_count);

#endif //IMAGE_API_H
