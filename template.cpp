#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <windows.h>
#include <regex>
#include <algorithm>
#include "Meme_Gen.h"
#include "Exp.h"
#include "social_media.h"
#include "last_action.h"

#define FILENAME_JOKES R"(D:\Proga\Turovec\Kursach\Meme Generator\templates\text\jokes.txt)"
#define FILENAME_JOKES_OUTPUT R"(D:\Proga\Turovec\Kursach\Meme Generator\templates\text\jokes_output.txt)"
#define FILENAME_IMAGE_PATH R"(D:\Proga\Turovec\Kursach\Meme Generator\templates\photo)"

using namespace std;
namespace fs = std::filesystem;

template <typename T>
class Template : public Meme_Gen {
public:
    Template() = default;
    virtual ~Template() = default;

    virtual std::string showTemplate(int choice) = 0;

    vector<T> contents;
protected:

    void loadContentFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Не удалось открыть файл: " << filename << endl;
            return;
        }

        string line;
        T contentItem;

        while (getline(file, line)) {
            if (line == "---") {
                contents.push_back(contentItem);
                contentItem.clear();
            } else {
                contentItem += line + "\n";
            }
        }
        if (!contentItem.empty()) {
            contents.push_back(contentItem);
        }
        file.close();
    }
};

class T_Text : public Template<string> {
public:
    T_Text() {
        loadContentFromFile(FILENAME_JOKES);
    }

    std::string showTemplate(int choice) override
    {

        string tempFilePath = FILENAME_JOKES_OUTPUT;
        ofstream tempFile(tempFilePath);
        if (!tempFile.is_open()) {
            cerr << "Не удалось открыть файл для записи: " << tempFilePath << endl;
            return "";
        }

        tempFile << contents[choice - 1];
        tempFile.close();

        ShellExecute(nullptr, "open", tempFilePath.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
        return FILENAME_JOKES_OUTPUT;
    }
};

class T_Image : public Template<string> {
public:
    T_Image() {
        string path = FILENAME_IMAGE_PATH;
        for (const auto& entry : fs::directory_iterator(path))
            if (entry.path().extension() == ".jpg")
                contents.push_back(entry.path().string());
        std::sort(contents.begin(), contents.end(), [](const std::string& a, const std::string& b) {
            std::smatch match_a, match_b;
            std::regex number_regex(R"((\d+))");
            std::regex_search(a, match_a, number_regex);
            std::regex_search(b, match_b, number_regex);

            int num_a = match_a.empty() ? 0 : std::stoi(match_a[1]);
            int num_b = match_b.empty() ? 0 : std::stoi(match_b[1]);

            return num_a < num_b;
        });
    }

    std::string showTemplate(int choice) override {

        ShellExecute(nullptr, "open", contents[choice - 1].c_str(), nullptr, nullptr, SW_SHOWNORMAL);
        return contents[choice - 1].c_str();
    }
};

void text() {
    T_Text pattern;
    Social_Media media ("");

    int choice;
    cout << "Выберите текстовый шаблон (1-" << pattern.contents.size() << "): ";
    choice = Out_of_range::out_of_range(pattern.contents.size());

    media.local_path = pattern.showTemplate(choice);
    if(media.local_path != "")
    {
        media.distributing(media.local_path);
    }
}

void image() {
    T_Image pattern;
    Social_Media media ("");

    int choice;
    cout << "Выберите изображение (1-" << pattern.contents.size() << "): ";
    choice = Out_of_range::out_of_range(pattern.contents.size());

    media.local_path = pattern.showTemplate(choice);
    if(media.local_path != "")
    {
        media.distributing(media.local_path);
    }
}

void local()
{
    while (true) {
        cout << "Тип выводимого локального мема:\n"
                "1. Изображение;\n"
                "2. Текст;\n"
                "0. Назад.\n";

        switch (Numbers::check_input()) {
            case 1:
                image();
                break;
            case 2:
                text();
                break;
            case 0:
                return;
            default:
                cout << "Неверное число. Повторите попытку: ";
                break;
        }
    }
}

void generated()
{
    Social_Media media("");
    GeneratedItem gen;
    auto img = gen.loadHistory(HISTORY_FILE_IMAGES);
    auto text = gen.loadHistory(HISTORY_FILE_TEXTS);

    while (true) {
        cout << "Тип выводимого ранее сгенерированного мема:\n"
                "1. Изображение;\n"
                "2. Текст;\n"
                "0. Назад.\n";

        switch (Numbers::check_input()) {
            case 1:
                media.local_path = showHistory(img, HISTORY_FILE_IMAGES);
                if (media.local_path != "") media.distributing(media.local_path);
                break;
            case 2:
                media.local_path = showHistory(text, HISTORY_FILE_TEXTS);
                if (media.local_path != "") media.distributing(media.local_path);
                break;
            case 0:
                return;
            default:
                cout << "Неверное число. Повторите попытку: ";
                break;
        }
    }
}

void templates()
{
    while (true) {
    cout << "\nВведите желаемый тип шаблона: "
            "\n1. Локальный;"
            "\n2. Ранее сгенерированный;"
            "\n0. Назад." << endl;

        switch (Numbers::check_input()) {
            case 1:
                local();
                break;
            case 2:
                generated();
                break;
            case 0:
                return;
            default:
                cout << "Число вне вариантов. Повторите ввод: ";
                break;
        }
    }
}