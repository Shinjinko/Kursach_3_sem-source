#ifndef KURSACH_CUSTOM_H
#define KURSACH_CUSTOM_H
#include "Meme_Gen.h"
#include <string>
#include <windows.h>
#include "social_media.h"


class Custom : public Meme_Gen {
protected:
    int meme_type;
    int getMemeType() const;

public:
    virtual ~Custom() = default;

    Custom();

    void setMemeType(int type);

    virtual std::string generate_meme() = 0;

};

void overlay();
#endif //KURSACH_CUSTOM_H
