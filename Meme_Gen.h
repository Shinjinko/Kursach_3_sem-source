#ifndef KURSACH_MEME_GEN_H
#define KURSACH_MEME_GEN_H

class Meme_Gen {
protected:
    int type;
public:
    int getType () const { return type; }
    void setType (const int choise) { type = choise; }
};

#endif //kursach_meme_gen_h
