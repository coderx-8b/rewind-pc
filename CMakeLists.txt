
cmake_minimum_required(VERSION 3.27...4.4)

project(rewind VERSION 0.0
                DESCRIPTION "A ibm pc emulator."
                LANGUAGES C)

# --- Global Configurations ---
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Define standard GNU installation directories (bin, include, lib, etc.)
include(GNUInstallDirs)


# --- Target: i486 Library ---
add_library(i486 STATIC 
    src/i486/decoder.c 
    src/i486/opcodetables.c
)

# Isolate include directories for local builds vs future installations
target_include_directories(i486 PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_compile_features(i486 PUBLIC c_std_23)


# --- Target: rewind Executable ---
add_executable(rewind src/main.c)
target_compile_features(rewind PRIVATE c_std_23)
target_link_libraries(rewind PRIVATE i486)


# --- Compiler Warnings Configuration ---
# Use Generator Expressions to safely apply standard strict warnings depending on compiler
target_compile_options(i486 PRIVATE
    $<IF:$<C_COMPILER_ID:MSVC>,
        /W4 /WX,                                     # MSVC flags: Level 4 warnings, treat warnings as errors
        -Wall -Wextra -Wpedantic -Wconversion # GCC/Clang flags: All warnings, pedantic, treat as errors
    >
)
target_compile_options(rewind PRIVATE
    $<IF:$<C_COMPILER_ID:MSVC>,
        /W4 /WX,
        -Wall -Wextra -Wpedantic -Wconversion
    >
)


# --- Installation Rules ---
# This rule handles copying both the executable and library binaries safely
install(TARGETS rewind i486
    EXPORT rewind-targets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}  # Moves executable to 'bin/'
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}  # Moves dynamic libraries to 'lib/'
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}  # Moves static libraries to 'lib/'
)

# Copy your public header files into the installation system path
install(DIRECTORY include/ 
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}      # Moves headers to 'include/'
)


