#include <iostream>
#include <string>
using namespace std;

class Meme_Gen {};

class Custom : public Meme_Gen {
protected:
    int meme_type;
    int getMemeType() const { return meme_type; }

public:
    virtual ~Custom() = default;

    Custom() : meme_type(0) {}

    void setMemeType(int type) { meme_type = type; }

    virtual void generateMeme() = 0;
};

class C_Image : public Custom {
protected:
    string image_URL;
    string local_path;
public:
    string getImageURL() const { return image_URL; }
    void setImageURL(const string& url) { image_URL = url; }

    string getLocalPath() const { return local_path; }
    void setLocalPath(const string& path) { local_path = path; }

    void generateMeme() override {
        cout << "��������� ���� � ������������ �� URL: " << image_URL << " ��� ���������� ����: " << local_path << endl;
    }

    ~C_Image() override = default;
};

class I_Settings : public C_Image {
private:
    string overlay_text;
    string text_color;
    string text_font;
public:
    string getOverlayText() const { return overlay_text; }
    void setOverlayText(const string& text) { overlay_text = text; }

    string getTextColor() const { return text_color; }
    void setTextColor(const string& color) { text_color = color; }

    string getTextFont() const { return text_font; }
    void setTextFont(const string& font) { text_font = font; }

    I_Settings() : text_font(), text_color(), overlay_text() {}

    void applySettings() {
        cout << "��������� ������ '" << overlay_text << "' �� ����������� � ������ ������: " << text_color << " � �������: " << text_font << endl;
    }

    void generateMeme() override {
        applySettings();
        C_Image::generateMeme();
    }
};

class C_Text : public Custom {
protected:
    string meme_text;
public:
    string getMemeText() const { return meme_text; }
    void setMemeText(const string& text) { meme_text = text; }

    void generateMeme() override {
        cout << "��������� ���� � �������: " << meme_text << endl;
    }
};

class T_Settings : public C_Text {
private:
    string text_color;
    string text_font;
    int font_size;
public:
    string getTextColor() const { return text_color; }
    void setTextColor(const string& color) { text_color = color; }

    string getTextFont() const { return text_font; }
    void setTextFont(const string& font) { text_font = font; }

    int getFontSize() const { return font_size; }
    void setFontSize(int size) { font_size = size; }

    T_Settings() : text_color(), text_font(), font_size() {}

    void applySettings() {
        cout << "��������� ������: ���� - " << text_color << ", ����� - " << text_font << ", ������ ������ - " << font_size << endl;
    }

    void generateMeme() override {
        applySettings();
        C_Text::generateMeme();
    }
};

void custom() {
    Custom* meme = nullptr;
    int choice_;

    cout << "�������� ��� ����:\n"
         << "1. �����������\n"
         << "2. �����\n"
         << "��� �����: ";
    cin >> choice_;


    if (choice_ == 1) {

        meme = new I_Settings();
        meme->setMemeType(1);

        string url, path, overlayText, textColor, textFont;
        cout << "������� URL �����������: ";
        cin >> url;
        dynamic_cast<I_Settings*>(meme)->setImageURL(url);

        cout << "������� ��������� ���� � �����������: ";
        cin >> path;
        dynamic_cast<I_Settings*>(meme)->setLocalPath(path);

        cout << "������� ����� ��� ��������� �� �����������: ";
        cin.ignore();
        getline(cin, overlayText);
        dynamic_cast<I_Settings*>(meme)->setOverlayText(overlayText);

        cout << "������� ���� ������: ";
        cin >> textColor;
        dynamic_cast<I_Settings*>(meme)->setTextColor(textColor);

        cout << "������� ����� ������: ";
        cin >> textFont;
        dynamic_cast<I_Settings*>(meme)->setTextFont(textFont);

        meme->generateMeme();
    }
    else if (choice_ == 2) {

        meme = new T_Settings();
        meme->setMemeType(2);

        string text, textColor, textFont;
        int fontSize;

        cout << "������� ����� ����: ";
        cin.ignore();
        getline(cin, text);
        dynamic_cast<T_Settings*>(meme)->setMemeText(text);

        cout << "������� ���� ������: ";
        cin >> textColor;
        dynamic_cast<T_Settings*>(meme)->setTextColor(textColor);

        cout << "������� ����� ������: ";
        cin >> textFont;
        dynamic_cast<T_Settings*>(meme)->setTextFont(textFont);

        cout << "������� ������ ������: ";
        cin >> fontSize;
        dynamic_cast<T_Settings*>(meme)->setFontSize(fontSize);

        meme->generateMeme();
    }
    else {
        cout << "�������� �����. ���������� �����." << endl;
    }


    delete meme;

}