#include <string>
#include <curl/curl.h>
#include <json/json.h>
#include <iostream>

// Функция для записи данных ответа API
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Функция для отправки запроса на Qwen API
std::string getResponseFromHuggingFace(const std::string& user_message) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    // Ваш токен авторизации
    std::string token = "Bearer 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";

    // URL API
    std::string url = "https://api-inference.huggingface.co/models/Qwen/QwQ-32B-Preview/v1/chat/completions";

    curl = curl_easy_init();
    if (curl) {
        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, ("Authorization: " + token).c_str());
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Создание JSON тела запроса
        Json::Value jsonData;
        jsonData["model"] = "Qwen/QwQ-32B-Preview";
        jsonData["max_tokens"] = 500;
        jsonData["stream"] = false;

        // Формирование сообщения в формате Qwen API
        Json::Value message(Json::objectValue);
        message["role"] = "user";
        message["content"] = user_message + ". Short answer without your comments, in 1-2 sentences.";
        jsonData["messages"].append(message);

        Json::StreamWriterBuilder writer;
        std::string jsonString = Json::writeString(writer, jsonData);

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonString.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // Выполнение запроса
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "Request error: " << curl_easy_strerror(res) << std::endl;
            curl_easy_cleanup(curl);
            curl_slist_free_all(headers);
            return "Error: Failed to perform request.";
        }

        // Освобождение ресурсов
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    } else {
        return "Error: Failed to initialize CURL.";
    }

    // Парсинг JSON ответа
    Json::Value jsonResponse;
    Json::CharReaderBuilder readerBuilder;
    std::string errors;
    std::istringstream stream(readBuffer);

    if (!Json::parseFromStream(readerBuilder, stream, &jsonResponse, &errors)) {
        std::cerr << "JSON parsing error: " << errors << std::endl;
        return "Error: Failed to parse JSON.";
    }

    // Проверка поля "choices" -> "message" -> "content"
    if (jsonResponse.isMember("choices") && jsonResponse["choices"].isArray() &&
        !jsonResponse["choices"].empty() &&
        jsonResponse["choices"][0].isMember("message") &&
        jsonResponse["choices"][0]["message"].isMember("content")) {

        return jsonResponse["choices"][0]["message"]["content"].asString();
    } else {
        std::cerr << "Error: Missing expected fields in API response." << std::endl;
        return "Error: Missing fields in response.";
    }
}