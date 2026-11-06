# EasierCpp-managed pinned dependencies.

# BEGIN EasierCpp library github-raysan5-raylib-02566453880e06bec97f5b8160fa6fe1e98397ca
if(POLICY CMP0168)
    cmake_policy(SET CMP0168 NEW)
endif()

# Pinned verified probe: raysan5/raylib 02566453880e06bec97f5b8160fa6fe1e98397ca
include(FetchContent)
FetchContent_Declare(cpplivelab_02566453880e
    URL https://codeload.github.com/raysan5/raylib/zip/02566453880e06bec97f5b8160fa6fe1e98397ca
    URL_HASH SHA256=999b52a128673948c6607d8cb841e34cc7ab7f13964ef2988dfce4fa7676b14b
    DOWNLOAD_EXTRACT_TIMESTAMP FALSE
)
FetchContent_MakeAvailable(cpplivelab_02566453880e)
target_link_libraries(app PRIVATE raylib_static)
# END EasierCpp library github-raysan5-raylib-02566453880e06bec97f5b8160fa6fe1e98397ca
