cmake_minimum_required(VERSION 3.28)
project(Kursach)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc")
set(Boost_USE_MULTITHREADED ON)
#set(TGBOT_LIBRARY "C:\\Users\\HONOR\\.vcpkg-clion\\installed\\x64-mingw-static\\lib\\libTgBot.a")

include_directories(C:/Users/HONOR/.vcpkg-clion/installed/x64-mingw-static/include)
include_directories(C:/Users/HONOR/.vcpkg-clion/installed/x64-mingw-dynamic/include)
link_directories(C:/Users/HONOR/.vcpkg-clion/installed/x64-mingw-static/lib)
link_directories(C:/Users/HONOR/.vcpkg-clion/installed/x64-mingw-dynamic/lib)

find_package(OpenCV CONFIG REQUIRED)
find_package(CURL REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(jsoncpp CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)
find_package(Threads REQUIRED)
include_directories(/usr/local/include ${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIR})
if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    add_definitions(-DHAVE_CURL)
endif()

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
        telegram.cpp
        telegram.h
        vk.cpp
        vk.h
        social_media.cpp
        last_action.cpp
        last_action.h
        color_map.cpp
        color_map.h
)

include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(Kursach "C:\\Users\\HONOR\\.vcpkg-clion\\installed\\x64-mingw-static\\lib\\TgBot.lib" CURL::libcurl OpenSSL::SSL OpenSSL::Crypto ${OpenCV_LIBS} JsonCpp::JsonCpp nlohmann_json::nlohmann_json Boost::boost ws2_32 ${OPENSSL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})