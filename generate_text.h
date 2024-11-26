//TODO: Заменить генератор текста
#ifndef TESTTEXTGENERATOR_GENERATE_TEXT_H
#define TESTTEXTGENERATOR_GENERATE_TEXT_H
#include <string>
#include <curl/curl.h>
#include <json/json.h>
#include <iostream>

// Функция для записи данных ответа
size_t WriteCallback_text(void* contents, size_t size, size_t nmemb, void* userp);

// Функция для отправки запроса на API
std::string getResponseFromHuggingFace(const std::string& prompt);
#endif //TESTTEXTGENERATOR_GENERATE_TEXT_H
