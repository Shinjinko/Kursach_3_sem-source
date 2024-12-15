#include "vk.h"
#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "social_media.h"

using json = nlohmann::json;

const std::string TOKEN = "vk1.a.xxz38-GHx8f36ZrPM7prAR0jNu_RG_HPpxyT6vrLIQigrM-5Q_2kD9buezi0BgoRYsfxuxV5nItsosC3bOoaOE40i3EBIKrOocAKEOv7oeWM2SbRd1LRyETveRcDzHQwGCIcf9ouGeORqMQLJqsRUVSTw2AGr_pY14J7bP6JUYbKLQPVGp0Te8DcoksJaz_FgYI_q3B0E5T4VE0sFuZYyA"; // Токен группы
const std::string API_URL = "https://api.vk.com/method/";
const std::string API_VERSION = "5.199";

std::string uploadPhoto(const std::string& filePath) {
    // 1. Получаем URL сервера для загрузки
    std::string getUrl = API_URL + "photos.getMessagesUploadServer?access_token=" + TOKEN + "&v=" + API_VERSION;
    std::string response = httpRequest(getUrl);

    if (response.empty()) {
        std::cerr << "Ошибка: Пустой ответ от API VK при получении upload_url!" << std::endl;
        return "";
    }

    auto jsonResponse = json::parse(response);
    if (!jsonResponse.contains("response") || !jsonResponse["response"].contains("upload_url")) {
        std::cerr << "Ошибка API VK: Неполный ответ для upload_url: " << response << std::endl;
        return "";
    }
    std::string uploadUrl = jsonResponse["response"]["upload_url"];

    // 2. Загружаем файл на сервер
    CURL* curl;
    CURLcode res;
    curl_mime* mime;
    curl_mimepart* part;
    std::string serverResponse;

    curl = curl_easy_init();
    if (curl) {
        mime = curl_mime_init(curl);
        part = curl_mime_addpart(mime);
        curl_mime_name(part, "file");
        curl_mime_filedata(part, filePath.c_str());

        curl_easy_setopt(curl, CURLOPT_URL, uploadUrl.c_str());
        curl_easy_setopt(curl, CURLOPT_MIMEPOST, mime);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, [](void* contents, size_t size, size_t nmemb, void* userp) {
            ((std::string*)userp)->append((char*)contents, size * nmemb);
            return size * nmemb;
        });
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &serverResponse);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "Ошибка загрузки файла: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
        curl_mime_free(mime);
    }

    if (serverResponse.empty()) {
        std::cerr << "Ошибка: Пустой ответ после загрузки файла!" << std::endl;
        return "";
    }

    auto uploadJson = json::parse(serverResponse);
    if (!uploadJson.contains("photo") || !uploadJson.contains("server") || !uploadJson.contains("hash")) {
        std::cerr << "Ошибка API VK после загрузки файла: " << serverResponse << std::endl;
        return "";
    }
    std::string photo = uploadJson["photo"];
    std::string server = std::to_string(uploadJson["server"].get<int>());
    std::string hash = uploadJson["hash"];

    // 3. Сохраняем фото
    std::string saveUrl = API_URL + "photos.saveMessagesPhoto?photo=" + curl_easy_escape(nullptr, photo.c_str(), 0) +
                          "&server=" + server +
                          "&hash=" + hash +
                          "&access_token=" + TOKEN +
                          "&v=" + API_VERSION;
    std::string saveResponse = httpRequest(saveUrl);

    if (saveResponse.empty()) {
        std::cerr << "Ошибка: Пустой ответ при сохранении фото!" << std::endl;
        return "";
    }

    auto saveJson = json::parse(saveResponse);
    if (!saveJson.contains("response") || saveJson["response"].empty()) {
        std::cerr << "Ошибка API VK при сохранении фото: " << saveResponse << std::endl;
        return "";
    }

    auto photoObj = saveJson["response"][0];
    return std::to_string(photoObj["owner_id"].get<int>()) + "_" + std::to_string(photoObj["id"].get<int>());
}


// Пример вызова для отправки фото
void sendPhotoFromPath(int userId, const std::string& filePath) {
    std::string photoId = uploadPhoto(filePath); // Загрузка фото
    sendPhoto(userId, photoId); // Отправка фото
}

// Функция для выполнения HTTP-запросов
std::string httpRequest(const std::string& url) {
    CURL* curl;
//    CURLcode res;
    std::string response;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, [](void* contents, size_t size, size_t nmemb, void* userp) {
            ((std::string*)userp)->append((char*)contents, size * nmemb);
            return size * nmemb;
        });
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
//        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return response;
}

void sendMessage(int userId, const std::string& message) {
    std::string url = API_URL + "messages.send?user_id=" + std::to_string(userId) +
                      "&message=" + curl_easy_escape(nullptr, message.c_str(), 0) +
                      "&access_token=" + TOKEN + "&v=" + API_VERSION;
    httpRequest(url);
}

void sendPhoto(int userId, const std::string& photoId) {
    std::string url = API_URL + "messages.send?user_id=" + std::to_string(userId) +
                      "&attachment=photo" + photoId +
                      "&access_token=" + TOKEN + "&v=" + API_VERSION;
    httpRequest(url);
}

void VK::distributing(std::string file_name)
{
    VK vk(file_name);
    vk.account_bot = BOT_VK;
    int userId = 273847885;
    std::string message = "Это тестовое сообщение!";

    std::cout << "Бот запущен..." << std::endl;

    sendMessage(userId, message);

    std::string filePath = R"(D:\\Proga\\Turovec\\Kursach\\Meme Generator\\templates\\photo\\2.jpg)";
    sendPhotoFromPath(userId, filePath);
}

VK::~VK() {

}
