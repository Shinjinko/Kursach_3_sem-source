cmake_minimum_required(VERSION 3.28)
project(Kursach)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(Kursach main.cpp
        image.cpp
        text.cpp
        template.cpp
        custom.cpp
        functions.h
        Meme_Gen.h
        Social_Media_TG.h
        Exp.cpp
        Exp.h
)
