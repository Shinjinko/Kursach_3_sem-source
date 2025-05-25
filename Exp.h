#ifndef KURSACH_EXP_H
#define KURSACH_EXP_H
#include <stdexcept>
#include <setjmp.h>
#include <string>
#include <iostream>
#include <thread>

class Overlay;

class Exp
{
private:
    std::string report;

public:
    Exp() : report("No errors") {};

    virtual ~Exp() = default;
};

class Numbers: public Exp
{
private:
    static jmp_buf jumpBuffer;
public:
    static int check_input();
};

class Out_of_range: public Exp
{
public:
    static int out_of_range(int size);
};

class Check_server_answer: public Exp
{
public:
    static std::string validate_and_resend(const std::string& prompt, int max_attempts = 3);
};

class Overlay_validator: public Exp
{
public:
    static void validate_overlay_data (Overlay& overlay);
};


#endif // KURSACH_EXP_H
