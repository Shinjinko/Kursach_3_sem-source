#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <windows.h>

#define FILENAME_JOKES "D:\\Proga\\Turovec\\Kursach\\Templates\\Jokes.txt"
#define FILENAME_JOKES_OUTPUT "D:\\Proga\\Turovec\\Kursach\\Templates\\Jokes_output.txt"
#define NUM_PHOTOS 20

using namespace std;

class Meme_Gen {};

template <typename T>
class Template : public Meme_Gen {
public:
    int choice;

    Template() : choice(0) {}

    int getChoice() const { return choice; }
    void setChoice(int choice_there) { this->choice = choice_there; }

    virtual void showTemplate() = 0;

protected:
    vector<T> contents;

    void loadContentFromFile(const string& filename) {
        ifstream file(filename);
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
    explicit T_Text(int choice) : Template() {
        this->choice = choice;
        loadContentFromFile(FILENAME_JOKES);
    }

    void showTemplate() override {
        if (choice > 0 && choice <= contents.size()) {

            string tempFilePath = FILENAME_JOKES_OUTPUT;
            ofstream tempFile(tempFilePath);
            tempFile << contents[choice - 1];
            tempFile.close();

            ShellExecute(nullptr, nullptr, tempFilePath.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
        } else {
            cout << "Неверный выбор.\n";
        }
    }
};

class T_Image : public Template<string> {
public:
    explicit T_Image(int choice) : Template() {
        this->choice = choice;
        for (int i = 1; i <= NUM_PHOTOS; ++i) {
            contents.push_back("D:/Proga/Turovec/Kursach/Templates/" + to_string(i) + ".jpg");
        }
    }

    void showTemplate() override {
        if (choice > 0 && choice <= contents.size()) {


            ShellExecute(0, 0, contents[choice - 1].c_str(), 0, 0, SW_SHOWNORMAL);
        } else {
            cout << "Неверный выбор.\n";
        }
    }
};

int templates() {
    cout << "Text (1-5): ";
    int ch;
    cin >> ch;

    T_Text textTemplate(ch);
    textTemplate.showTemplate();

    cout << "Image (1-20):";
    cin >> ch;

    T_Image imageTemplate(ch);
    imageTemplate.showTemplate();
    return 0;
}
