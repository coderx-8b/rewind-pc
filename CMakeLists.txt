cmake_minimum_required(VERSION 3.15...4.4)

project(rewind VERSION 0.0
                DESCRIPTION "A ibm pc emulator."
                LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(i486 STATIC src/i486/decoder.c src/i486/opcodetables.c)
target_include_directories(i486 PUBLIC include)
target_compile_features(i486 PUBLIC c_std_23)


add_executable(rewind src/main.c)
target_link_libraries(rewind PRIVATE i486)


