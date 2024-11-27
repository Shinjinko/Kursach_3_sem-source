#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#define byte win_byte_override
#include <windows.h>
#include "Meme_Gen.h"
#include "Exp.h"
namespace fs = std::filesystem;

#define FILENAME_JOKES "D:\\Proga\\Turovec\\Kursach\\Templates\\Jokes.txt"
#define FILENAME_JOKES_OUTPUT "D:\\Proga\\Turovec\\Kursach\\Templates\\Jokes_output.txt"
#define FILENAME_IMAGE_PATH "D:\\Proga\\Turovec\\Kursach\\Templates\\"


using namespace std;

template <typename T>
class Template : public Meme_Gen {
public:
    Template() = default;
    virtual ~Template() = default;

    virtual void showTemplate(int choice) = 0;

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

    void showTemplate(int choice) override
    {

        string tempFilePath = FILENAME_JOKES_OUTPUT;
        ofstream tempFile(tempFilePath);
        if (!tempFile.is_open()) {
            cerr << "Не удалось открыть файл для записи: " << tempFilePath << endl;
            return;
        }

        tempFile << contents[choice - 1];
        tempFile.close();

        ShellExecute(nullptr, "open", tempFilePath.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
    }
};

class T_Image : public Template<string> {
public:
    T_Image() {
        string path = FILENAME_IMAGE_PATH;
        for (const auto& entry : fs::directory_iterator(path))
            if (entry.path().extension() == ".jpg")
                contents.push_back(entry.path().string());
    }

    void showTemplate(int choice) override {

        ShellExecute(nullptr, "open", contents[choice - 1].c_str(), nullptr, nullptr, SW_SHOWNORMAL);
    }
};

void text() {
    T_Text pattern;
    int choice;
    cout << "Выберите текстовый шаблон (1-" << pattern.contents.size() << "): ";
    choice = Out_of_range::out_of_range(pattern.contents.size());
    pattern.showTemplate(choice);
}


void image() {
    T_Image pattern;
    int choice;
    cout << "Выберите изображение (1-" << pattern.contents.size() << "): ";
    choice = Out_of_range::out_of_range(pattern.contents.size());
    cout << "Вывод изображения.\n";
    pattern.showTemplate(choice);
}

void templates() {
    while (true) {
    cout << "\nВведите желаемый тип шаблона: "
            "\n1. Текст;"
            "\n2. Изображение;"
            "\n0. Назад." << endl;

        int choice;
        cin >> choice;
        switch (choice) {
            case 1:
                text();
                break;
            case 2:
                image();
                break;
            case 0:
                return;
            default:
                cout << "Число вне вариантов. Повторите ввод: ";
                break;
        }
    }
}