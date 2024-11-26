cmake_minimum_required(VERSION 3.28)
project(Kursach)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static")

set(OpenCV_DIR "C:/Users/HONOR/.vcpkg-clion/buildtrees/opencv3/x64-mingw-dynamic-dbg")
find_package(OpenCV CONFIG REQUIRED)
find_package(CURL REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(jsoncpp CONFIG REQUIRED)

add_executable(Kursach main.cpp
        template.cpp
        custom.cpp
        functions.h
        Meme_Gen.h
        social_media.h
        Exp.cpp
        Exp.h
        image_api.h
        c_image.cpp
        c_image.h
        custom.h
        c_text.cpp
        c_text.h
        overlay.cpp
        overlay.h
        image_api.cpp
        generate_text.cpp
)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(Kursach CURL::libcurl OpenSSL::SSL OpenSSL::Crypto ${OpenCV_LIBS} JsonCpp::JsonCpp)