#include "telegram.h"
#include <tgbot/tgbot.h>
#include <iostream>
#include <unordered_map>
#include "social_media.h"
#include <fstream>
#include <sstream>
#include <filesystem>

std::unordered_map<int64_t, bool> userVerification;
std::atomic<bool> botRunning = true;

Telegram::~Telegram() {

}

std::string getFileExtension(const std::string& filePath) {
    return std::filesystem::path(filePath).extension().string();
}


std::string readFileUtf8(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Не удалось открыть файл: " + filePath);
    }

    std::ostringstream contents;
    contents << file.rdbuf();
    return contents.str();
}

void startBot(const std::string& filePath) {
    TgBot::Bot bot("7882695478:AAFJm_qKetWaFgb4E0rkMf2HRQ-ocESm8T4");

    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id,
                                 "Добро пожаловать! Вы хотите подтвердить, что это ваш аккаунт?");
        userVerification[message->chat->id] = false;
        bot.getApi().sendMessage(message->chat->id,
                                 "Пожалуйста, ответьте 'Да' или 'Нет'.");
    });

    bot.getEvents().onAnyMessage([&bot, &filePath](TgBot::Message::Ptr msg) {
        int64_t chatId = msg->chat->id;

        if (userVerification.find(chatId) != userVerification.end() && !userVerification[chatId]) {
            if (msg->text == "Да") {
                userVerification[chatId] = true;
                bot.getApi().sendMessage(chatId, "Подтверждено! Отправляю файл...");

                // Определяем тип файла
                std::string fileExtension = getFileExtension(filePath);

                try {
                    if (fileExtension == ".jpg" || fileExtension == ".jpeg") {
                        // Отправляем как фото
                        bot.getApi().sendPhoto(chatId, TgBot::InputFile::fromFile(filePath, "photo.jpg"));

                    } else if (fileExtension == ".txt") {
                        // Читаем текст и отправляем как сообщение
                        std::string fileContents = readFileUtf8(filePath);
                        bot.getApi().sendMessage(chatId, fileContents);
                    } else {
                        // Отправляем файл как документ
                        bot.getApi().sendDocument(chatId, TgBot::InputFile::fromFile(filePath, "application/octet-stream"));
                    }
                } catch (std::exception& e) {
                    bot.getApi().sendMessage(chatId, "Ошибка при отправке файла: " + std::string(e.what()));
                }
                bot.getApi().sendMessage(chatId, "Работа завершена. До свидания!");
                botRunning = false;

            } else if (msg->text == "Нет") {
                bot.getApi().sendMessage(chatId, "Начнем сначала. Нажмите /start.");
            } else {
                bot.getApi().sendMessage(chatId, "Ответьте 'Да' или 'Нет'.");
            }
        }
    });

    try {
        std::cout << "Бот запущен!" << std::endl;
        std::cout << "Напишите сообщение боту: " << BOT_TG << std::endl;
        TgBot::TgLongPoll longPoll(bot);
        while (botRunning) { // Цикл работает, пока botRunning == true
            longPoll.start();
        }
    } catch (std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
}

void Telegram::distributing(std::string file_name)
{
    Telegram tg (file_name);
    tg.account_bot = BOT_TG;
    botRunning = true;
    startBot(tg.local_path);
}