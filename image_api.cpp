#include <string>
#include <iostream>
#include "include/curl/include/curl/curl.h"
#include <fstream>
#include <vector>
#include <C:\Users\HONOR\.vcpkg-clion\installed\x64-mingw-dynamic\include\openssl\evp.h>
#include <algorithm>
#include "image_api.h"
using namespace std;

std::string cleanBase64String(const std::string& encoded)
{
    std::string cleanStr = encoded;

    cleanStr.erase(std::remove(cleanStr.begin(), cleanStr.end(), '\"'), cleanStr.end());
    cleanStr.erase(std::remove(cleanStr.begin(), cleanStr.end(), '\n'), cleanStr.end());
    cleanStr.erase(std::remove(cleanStr.begin(), cleanStr.end(), '\r'), cleanStr.end());

    return cleanStr;
}

size_t WriteCallback_s(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::vector<unsigned char> base64Decode(const std::string& encoded) {
    BIO* bio = BIO_new_mem_buf(encoded.data(), encoded.size());
    BIO* b64 = BIO_new(BIO_f_base64());
    bio = BIO_push(b64, bio);
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);

    std::vector<unsigned char> decoded(encoded.size());
    int decodedLength = BIO_read(bio, decoded.data(), encoded.size());
    decoded.resize(decodedLength);

    BIO_free_all(bio);
    return decoded;
}

int Image_Api(const std::string& prompt) {
    CURL* hnd = curl_easy_init();
    std::string readBuffer;

    if (hnd) {
        curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "POST");
        curl_easy_setopt(hnd, CURLOPT_URL, "https://imageai-generator.p.rapidapi.com/image");

        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "x-rapidapi-key: b2bc373376msh0d28ad3340a00fep1a18e6jsn1b945e6b7866");
        headers = curl_slist_append(headers, "x-rapidapi-host: imageai-generator.p.rapidapi.com");
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);

        // Формируем тело POST-запроса
        std::string postData = "{\"negative_prompt\":\"white\",\"prompt\":\"" + prompt +
                               "\",\"width\":512,\"height\":512,\"hr_scale\":2}";

        curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, postData.c_str());

        // Добавляем callback для записи ответа
        curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, WriteCallback_s);
        curl_easy_setopt(hnd, CURLOPT_WRITEDATA, &readBuffer);

        CURLcode ret = curl_easy_perform(hnd);
        if (ret != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(ret) << std::endl;
        } else {
            // Очищаем строку Base64 от кавычек и ненужных символов
            std::string cleanBase64 = cleanBase64String(readBuffer);

            // Сохраняем очищенную Base64 строку в файл
            std::ofstream base64File("base64_output.txt");
            if (base64File.is_open()) {
                base64File << cleanBase64; // Записываем строку без кавычек
                base64File.close();
                std::cout << "Cleaned Base64 string saved as base64_output.txt" << std::endl;
            }

            // Декодируем очищенную Base64 строку
            std::vector<unsigned char> imageData = base64Decode(cleanBase64);

            // Сохраняем изображение в файл в формате JPEG
            std::ofstream imageFile(GENERATE_JOKES_PHOTO_OUTPUT, std::ios::binary); // Сохраняем как JPEG
            imageFile.write(reinterpret_cast<const char*>(imageData.data()), imageData.size());
            imageFile.close();

            std::cout << "Изображение сохранено!\n" << std::endl;
        }

        curl_easy_cleanup(hnd);
    }

    return 0;
}