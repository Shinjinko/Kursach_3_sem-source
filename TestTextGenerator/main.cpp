#include <iostream>
#include <string>
#include <curl/curl.h>
#include <json/json.h>

// Функция для записи данных ответа
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Функция для отправки запроса на Hugging Face API
std::string getResponseFromHuggingFace(const std::string& prompt) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    // Ваш токен доступа Hugging Face (замените "YOUR_HUGGINGFACE_TOKEN" на реальный токен)
    std::string token = "Bearer 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";

    // Инициализация curl
    curl = curl_easy_init();
    if (curl) {
        // Установка URL для DialoGPT-medium модели
        std::string url = "https://api-inference.huggingface.co/models/microsoft/DialoGPT-medium";
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // Установка заголовков, включая токен доступа
        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, ("Authorization: " + token).c_str());
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Создаем jsonData как объект JSON
        Json::Value jsonData(Json::objectValue);
        jsonData["inputs"] = prompt;

        Json::StreamWriterBuilder writer;
        std::string jsonString = Json::writeString(writer, jsonData);

        // Установка тела запроса
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonString.c_str());

        // Установка функции обратного вызова для записи данных в readBuffer
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // Выполнение запроса
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "Request error: " << curl_easy_strerror(res) << std::endl;
            curl_easy_cleanup(curl);
            curl_slist_free_all(headers);
            return "";
        }

        // Очистка
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }

    // Логируем ответ от API
    std::cout << "Answer from API: " << readBuffer << std::endl;

    // Парсинг JSON-ответа
    Json::Value jsonResponse;
    Json::CharReaderBuilder readerBuilder;
    std::string errors;
    std::istringstream stream(readBuffer);
    if (!Json::parseFromStream(readerBuilder, stream, &jsonResponse, &errors)) {
        std::cerr << "JSON parsing error: " << errors << std::endl;
        return "";
    }

    // Проверка, является ли jsonResponse массивом
    if (jsonResponse.isArray() && !jsonResponse.empty()) {
        // Извлечение первого элемента массива
        const Json::Value& firstElement = jsonResponse[0];
        if (firstElement.isMember("generated_text") && !firstElement["generated_text"].isNull()) {
            return firstElement["generated_text"].asString();
        } else {
            std::cerr << "Error: The 'generated_text' field is missing in the first element." << std::endl;
            return "Error: An empty response from the model.";
        }
    } else {
        std::cerr << "Error: The response is not an array or is empty." << std::endl;
        return "Error: An empty response from the model.";
    }
}

int main() {

    std::string prompt = "Helen";

    std::string response = getResponseFromHuggingFace(prompt);

    std::cout << "Answer: " << response << std::endl;

    return 0;
}
