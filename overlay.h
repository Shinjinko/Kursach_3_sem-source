#ifndef KURSACH_OVERLAY_H
#define KURSACH_OVERLAY_H
#include "c_image.h"
#include "c_text.h"
#include "Exp.h"

class Overlay : public I_Settings, public T_Settings
{
public:
    Overlay()
    {
        local_path_image = "";
        text_pattern = "";
    }

    void generate_meme() override {}

    void apply_settings() override {}

    void do_overlay (const Overlay& overlay);

    ~Overlay() override = default;
};
#endif //KURSACH_OVERLAY_H