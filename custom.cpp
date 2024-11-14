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

    Custom() : meme_type(0){}

    void setMemeType(int type) { meme_type = type; }

    virtual void generateMeme() = 0;

    virtual void apply_settings() = 0;
};

class C_Image : public Custom {
protected:
    string image_pattern;
public:
    const string &getPattern() const
    {
        return image_pattern;
    }

    void setPattern(const string &line)
    {
        C_Image::image_pattern = line;
    }

protected:
    string local_path_image;
public:

    string getLocalPath() const { return local_path_image; }
    void setLocalPath(const string& path) { local_path_image = path; }

    void generateMeme() override
    {
        //Привязать генератор
    }

    ~C_Image() override = default;
};

class I_Settings : public C_Image {
private:
    string image_background;
    string image_color;
    //smth else
public:
    string getOverlayText() const { return image_background; }
    void setOverlayText(const string& text) { image_background = text; }

    string getTextColor() const { return image_color; }
    void setTextColor(const string& color) { color ; }


    I_Settings() : image_color(), image_background() {}

    void apply_settings() override{
        //Добавить возможность возврата
    }

    void generateMeme() override {
        apply_settings();
        C_Image::generateMeme();
    }
};

class C_Text : public Custom {
protected:
    string text_pattern;
public:
    string getMemeText() const { return text_pattern; }
    void setMemeText(const string& text) { text_pattern = text; }

    void generateMeme() override {
        cout << "Генерация мема с текстом: " << text_pattern << endl;
    }
};

class T_Settings : public C_Text {
private:
    string text_color;
    string text_font;
    string text_background;
    int font_size;
public:
    const string &getTextColor() const { return text_color; }
    void setTextColor(const string& color) { text_color = color; }

    const string &getTextFont() const { return text_font; }
    void setTextFont(const string& font) { text_font = font; }

    int getFontSize() const { return font_size; }
    void setFontSize(int size) { font_size = size; }

    const string &getTextBackground() const { return text_background; }
    void setTextBackground(const string &textBackground) { text_background = textBackground; }

    T_Settings() : text_color(), text_font(), font_size() {}

    void apply_settings() override{
        //Добавить возможность возврата
    }

    void generateMeme() override {
        apply_settings();
        C_Text::generateMeme();
        //привязать
    }
};

class Overlay : public I_Settings, public T_Settings
{
public:

    void do_overlay ();
    //ещё одно ИИ
};

void Overlay::do_overlay()
{
    if(local_path_image == " ")
    {
        //создать текст
    }
    else if (text_pattern == " ")
    {
        // создать изображение
    }

    //вызов функции с наложением
}

void custom() {

//Привязать гугл переводчик

    Custom* meme = nullptr;
    int choice_;

    cout << "Выберите тип мема:\n"
         << "1. Изображение\n"
         << "2. Текст\n"
         << "Ваш выбор: ";
    cin >> choice_;

    delete meme;

}