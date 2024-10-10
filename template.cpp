#include <iostream>
#include <string>

using namespace std;

class Meme_Gen {};

class Template : public Meme_Gen {
public:
    int choice;

    int getChoice() const {
        return choice;
    }

    void setChoice(int choice) {
        this->choice = choice;
    }

    virtual void showTemplate() = 0;

protected:
    explicit Template(int choice) : choice(choice) {}
};

class T_Text : public Template {
private:
    string jokes[2] = {
            "Смех и грех — это измена мужу с клоуном.",
            "Если человек отвечает вопросом на вопрос, то он — либо еврей, либо студент на экзамене."
    };

public:
    T_Text() : Template(0) {}

    void showTemplate() override {
        if (choice > 0 && choice <= 2) {
            cout << "Вы выбрали шутку: " << jokes[choice - 1] << endl;
        } else {
            cout << "Неверный выбор.\n";
        }
    }
};

class T_Image : public T_Text {
private:
    string images[2] = {
            "C:/images/clowns.jpg",
            "C:/images/jews.jpg"
    };

public:
    T_Image() : T_Text() {}

    void showTemplate() override {
        if (choice > 0 && choice <= 2) {
            cout << "Открываем изображение: " << images[choice - 1] << endl;
        } else {
            cout << "Неверный выбор.\n";
        }
    }
};

int templates() {
    T_Text textTemplate;
    T_Image imageTemplate;

    cout << "\nВыберите один из предлагаемых шаблонов:\n"
            "1. Клоуны;\n" // Смех и грех — это измена мужу с клоуном.
            "2. Евреи;\n"; // Если человек отвечает вопросом на вопрос, то он — либо еврей, либо студент на экзамене.

    int choice_;
    cout << "Ваш выбор (1 или 2): ";
    cin >> choice_;

    textTemplate.setChoice(choice_);
    textTemplate.showTemplate();

    imageTemplate.setChoice(choice_);
    imageTemplate.showTemplate();
    

    return 0;
}
