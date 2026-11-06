
cmake_minimum_required(VERSION 3.24)

project(Hollow_Core LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# This project uses headers, not implicit C++ module imports.
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

# Automatically discover source files, including subdirectories.
file(GLOB_RECURSE APP_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cxx"
)

# Automatically discover headers for IDE organization.
file(GLOB_RECURSE APP_HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
)

# Create executable using discovered files.
add_executable(app
    ${APP_SOURCES}
    ${APP_HEADERS}
)

target_compile_features(app PRIVATE cxx_std_20)
set_target_properties(app PROPERTIES CXX_EXTENSIONS OFF)

target_include_directories(app PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT app)

# EasierCpp-managed dependency declarations.
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/Dependencies.cmake")

# Keep assets beside the actual Debug/Release executable.
add_custom_command(TARGET app POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:app>/assets"
    VERBATIM
)
