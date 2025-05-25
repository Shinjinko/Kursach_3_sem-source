#include "vk.h"
#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include "social_media.h"

using json = nlohmann::json;

#define TOKEN "vk1.a.AVtg3pelTIqCerP5TzoUCEjJAPdJGk58IIWRWoU1uSAL0ejWhGIqiXkC3vsBT3FKqvJlgqpdXO5jBkYMH6t8J0MquqqkX_wo7H1EDCAbcbXwxPQGTL3HLm_xu6dTVyfZmRTYGMKLZdO53IKJ6poz7sOeqzqOjRcrHrYhzqXugUmlT2ueLzJ7Uy8zkGiMu6o9_9niEtY1HlheoA8TAjFC3w" // Токен группы
#define API_URL "https://api.vk.com/method/"
#define API_VERSION "5.199"

std::string getFileExtension_vk(const std::string& filePath) {
    return std::filesystem::path(filePath).extension().string();
}


std::string readFileUtf8_vk(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Не удалось открыть файл: " + filePath);
    }

    std::ostringstream contents;
    contents << file.rdbuf();
    return contents.str();
}

// Функция для получения ID пользователей с непрочитанными сообщениями
std::vector<int> getUnreadUserIds() {
    std::vector<int> userIds;

    // Запрос к API VK для получения непрочитанных сообщений
    std::string url = std::string(API_URL) + "messages.getConversations?filter=unread&access_token=" +
                      std::string(TOKEN) + "&v=" + std::string(API_VERSION);

    std::string response = httpRequest(url);

    if (response.empty()) {
        std::cerr << "Ошибка: Пустой ответ от API при запросе непрочитанных сообщений!" << std::endl;
        return userIds;
    }

    try {
        auto jsonResponse = json::parse(response);
        auto items = jsonResponse["response"]["items"];

        // Проходим по всем диалогам и сохраняем user_id
        for (const auto& item : items) {
            if (item.contains("conversation") && item["conversation"].contains("peer")) {
                int userId = item["conversation"]["peer"]["id"].get<int>();
                userIds.push_back(userId);
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Ошибка обработки JSON: " << e.what() << std::endl;
    }

    return userIds;
}


size_t WriteCallback_vk(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t totalSize = size * nmemb;
    std::string* response = static_cast<std::string*>(userp);
    if (response) {
        response->append(static_cast<char*>(contents), totalSize);
    }
    return totalSize;
}

// Универсальная функция для выполнения HTTP-запросов
std::string httpRequest(const std::string& url) {
    CURL* curl = curl_easy_init();
    std::string response;

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback_vk);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "Ошибка HTTP-запроса: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
    }
    return response;
}

// Функция для загрузки фотографии и получения её ID
std::string uploadPhoto(const std::string& filePath) {
    // Шаг 1: Получаем URL сервера для загрузки
    std::string getUrl = std::string(API_URL) + "photos.getMessagesUploadServer?access_token=" + std::string(TOKEN) + "&v=" + std::string(API_VERSION);
    std::string response = httpRequest( getUrl);

    if (response.empty()) {
        std::cerr << "Ошибка: Пустой ответ от API при запросе upload_url!" << std::endl;
        return "";
    }

    try {
        auto jsonResponse = json::parse(response);
        std::string uploadUrl = jsonResponse["response"]["upload_url"];

        // Шаг 2: Загружаем файл на сервер
        CURL* curl = curl_easy_init();
        std::string serverResponse;

        if (curl) {
            curl_mime* mime = curl_mime_init(curl);
            curl_mimepart* part = curl_mime_addpart(mime);
            curl_mime_name(part, "file");
            curl_mime_filedata(part, filePath.c_str());

            curl_easy_setopt(curl, CURLOPT_URL, uploadUrl.c_str());
            curl_easy_setopt(curl, CURLOPT_MIMEPOST, mime);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback_vk);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &serverResponse);

            CURLcode res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                std::cerr << "Ошибка загрузки файла: " << curl_easy_strerror(res) << std::endl;
                curl_easy_cleanup(curl);
                curl_mime_free(mime);
                return "";
            }

            curl_easy_cleanup(curl);
            curl_mime_free(mime);
        }

        if (serverResponse.empty()) {
            std::cerr << "Ошибка: Пустой ответ после загрузки файла!" << std::endl;
            return "";
        }

        // Шаг 3: Парсим ответ и сохраняем фото
        auto uploadJson = json::parse(serverResponse);
        std::string photo = uploadJson["photo"];
        std::string server = std::to_string(uploadJson["server"].get<int>());
        std::string hash = uploadJson["hash"];

        std::string saveUrl = std::string(API_URL) + "photos.saveMessagesPhoto?photo=" + curl_easy_escape(nullptr, photo.c_str(), 0) +
                              "&server=" + server +
                              "&hash=" + hash +
                              "&access_token=" + std::string(TOKEN) +
                              "&v=" + std::string(API_VERSION);
        std::string saveResponse = httpRequest(saveUrl);

        auto saveJson = json::parse(saveResponse);
        auto photoObj = saveJson["response"][0];
        return std::to_string(photoObj["owner_id"].get<int>()) + "_" + std::to_string(photoObj["id"].get<int>());
    } catch (const std::exception& e) {
        std::cerr << "Ошибка обработки JSON: " << e.what() << std::endl;
        return "";
    }
}

// Универсальная функция для отправки сообщений или фотографий
void sendMessageOrPhoto(int userId, const std::string& message, const std::string& filePath = "") {
    if (!filePath.empty()) {
        // Если указан файл, загружаем фото
        std::string photoId = uploadPhoto(filePath);
        if (!photoId.empty()) {
            // Отправляем фото
            for (int i = 0; i < 1; i++) {
                std::string url = std::string(API_URL) + "messages.send?user_id=" + std::to_string(userId) +
                                  "&attachment=photo" + photoId +
                                  "&random_id=" + std::to_string(rand()) +
                                  "&access_token=" + std::string(TOKEN) + "&v=" + std::string(API_VERSION);
                httpRequest(url);
            }
        } else {
            std::cerr << "Ошибка при загрузке фото. Отправка отменена." << std::endl;
        }
    }
    if (!message.empty()) {
        // Отправляем текст
        for (int i = 0; i < 1; i++) {
            std::string url = std::string(API_URL) + "messages.send?user_id=" + std::to_string(userId) +
                              "&message=" + curl_easy_escape(curl_easy_init(), message.c_str(), 0) +
                              "&random_id=" + std::to_string(rand() + i) + // Уникальный random_id
                              "&access_token=" + std::string(TOKEN) + "&v=" + std::string(API_VERSION);
            httpRequest(url);
        }
    }
}


void VK::distributing(std::string file_name)
{
    VK vk(file_name);
    vk.account_bot = BOT_VK;

    std::cout << "Бот запущен..." << std::endl;

    // Получаем ID пользователей с непрочитанными сообщениями
    std::cout << "Напишите сообщение боту: " << vk.account_bot << std::endl;
    std::vector<int> userIds = getUnreadUserIds();

    while (userIds.empty())
    {
        userIds = getUnreadUserIds();
    }

    try {
        // Определяем расширение файла
        std::string extension = getFileExtension_vk(file_name);

        if (extension == ".txt") {
            std::string message = readFileUtf8_vk(file_name);

            for (int userId : userIds) {
                sendMessageOrPhoto(userId, message); // Отправляем текстовое сообщение
                std::cout << "Текстовое сообщение отправлено! " << std::endl;
            }
        }
        else if (extension == ".jpg" || extension == ".jpeg" || extension == ".png") {
            for (int userId : userIds) {
                sendMessageOrPhoto(userId, "", file_name); // Отправляем фото
                std::cout << "Фото отправлено!" << std::endl;
            }
        }
        else {
            std::cerr << "Ошибка: неподдерживаемый формат файла - " << extension << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
}


VK::~VK() {

}
