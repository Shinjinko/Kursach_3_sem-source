#ifndef KURSACH_OVERLAY_H
#define KURSACH_OVERLAY_H
#include "c_image.h"
#include "c_text.h"

class Overlay : public I_Settings, public T_Settings
{
public:
    Overlay() : I_Settings(), T_Settings(), local_path_image(""), text_pattern("")
    {}

    void generate_meme() override {}

    void apply_settings() override {}

    void do_overlay ();

    ~Overlay() override = default;
};
#endif //KURSACH_OVERLAY_H
