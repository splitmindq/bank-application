cmake_minimum_required(VERSION 3.26)
project(bank_app C)

set(CMAKE_C_STANDARD 23)
include_directories(pdflib)

# Включаем vcpkg и находим пакет CURL
find_package(CURL REQUIRED)

# Добавляем исполняемый файл и линкуем его с CURL
add_executable(bank_app main.c
        sha256.h
        sha256.c
        functions.h
        functions.c
        bank_structure.h
        password_recovery.c)

# Линкуем с libcurl
target_link_libraries(bank_app PRIVATE CURL::libcurl)
