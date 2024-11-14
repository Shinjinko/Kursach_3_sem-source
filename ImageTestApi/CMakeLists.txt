cmake_minimum_required(VERSION 3.28)
project(TestApi)

set(CMAKE_CXX_STANDARD 17)

# Находим библиотеки CURL и OpenSSL
find_package(CURL REQUIRED)
find_package(OpenSSL REQUIRED)

# Создаём исполняемый файл (цель 'TestApi')
add_executable(TestApi ImageTestApi.cpp)

# Линкуем исполняемый файл с библиотеками CURL и OpenSSL
target_link_libraries(TestApi CURL::libcurl OpenSSL::SSL OpenSSL::Crypto)
