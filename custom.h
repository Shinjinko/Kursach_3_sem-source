#ifndef KURSACH_CUSTOM_H
#define KURSACH_CUSTOM_H
#include "Meme_Gen.h"
#include <string>

using namespace std;

class Custom : public Meme_Gen {
protected:
    int meme_type;
    int getMemeType() const;

public:
    virtual ~Custom() = default;

    Custom();

    void setMemeType(int type);

    virtual void generate_meme() = 0;

    virtual void apply_settings() = 0;
};

string c_image();
string c_text();
void overlay();
#endif //KURSACH_CUSTOM_H
