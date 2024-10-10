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
            "���� � ���� � ��� ������ ���� � �������.",
            "���� ������� �������� �������� �� ������, �� �� � ���� �����, ���� ������� �� ��������."
    };

public:
    T_Text() : Template(0) {}

    void showTemplate() override {
        if (choice > 0 && choice <= 2) {
            cout << "�� ������� �����: " << jokes[choice - 1] << endl;
        } else {
            cout << "�������� �����.\n";
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
            cout << "��������� �����������: " << images[choice - 1] << endl;
        } else {
            cout << "�������� �����.\n";
        }
    }
};

int templates() {
    T_Text textTemplate;
    T_Image imageTemplate;

    cout << "\n�������� ���� �� ������������ ��������:\n"
            "1. ������;\n" // ���� � ���� � ��� ������ ���� � �������.
            "2. �����;\n"; // ���� ������� �������� �������� �� ������, �� �� � ���� �����, ���� ������� �� ��������.

    int choice_;
    cout << "��� ����� (1 ��� 2): ";
    cin >> choice_;

    textTemplate.setChoice(choice_);
    textTemplate.showTemplate();

    imageTemplate.setChoice(choice_);
    imageTemplate.showTemplate();
    

    return 0;
}
