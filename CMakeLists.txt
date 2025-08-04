cmake_minimum_required(VERSION 3.28)
project(GameCpp LANGUAGES CXX)

# Set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Set default build type to Release if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# Release-specific optimizations
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
    if(WIN32)
        # Hide console window in release mode on Windows
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -mwindows")
    endif()
endif()

# Fetch SFML
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# Copy resources to build directory
file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# Create executable
add_executable(GameCpp 
    src/main.cpp 
    include/Player.h 
    src/player.cpp 
    include/Bullet.h 
    src/bullet.cpp 
    src/Enemy.cpp 
    include/EnemySpawner.h 
    src/EnemySpawner.cpp 
    include/Math.h 
    src/math.cpp 
    include/HUD.h 
    src/hud.cpp 
    include/Menu.h 
    src/menu.cpp 
    include/GameOver.h 
    src/gameOver.cpp 
    include/GameState.h 
    include/HighScoreManager.h 
    src/highscoreManager.cpp
)

# Set C++ standard
target_compile_features(GameCpp PRIVATE cxx_std_17)

# Link libraries
target_link_libraries(GameCpp PRIVATE SFML::Graphics SFML::Audio)

# Include directories
target_include_directories(GameCpp PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

# Platform-specific settings
if(WIN32)
    # Set executable icon (if you have one)
    # set_target_properties(GameCpp PROPERTIES WIN32_EXECUTABLE TRUE)
    
    # Copy SFML DLLs to output directory in Release mode
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        add_custom_command(TARGET GameCpp POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_FILE:SFML::System>
                $<TARGET_FILE:SFML::Window>
                $<TARGET_FILE:SFML::Graphics>
                $<TARGET_FILE:SFML::Audio>
                $<TARGET_FILE_DIR:GameCpp>
        )
    endif()
endif()

# Install configuration for packaging
install(TARGETS GameCpp
    RUNTIME DESTINATION .
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/resources
    DESTINATION .
)

# Windows-specific DLL installation
if(WIN32)
    install(FILES
        $<TARGET_FILE:SFML::System>
        $<TARGET_FILE:SFML::Window>
        $<TARGET_FILE:SFML::Graphics>
        $<TARGET_FILE:SFML::Audio>
        DESTINATION .
    )
endif()

# CPack configuration for creating distributable packages
set(CPACK_PACKAGE_NAME "GameCpp")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Space Shooter Game")
set(CPACK_PACKAGE_VENDOR "YourName")

if(WIN32)
    set(CPACK_GENERATOR "ZIP;NSIS")
    set(CPACK_NSIS_DISPLAY_NAME "GameCpp - Space Shooter")
    set(CPACK_NSIS_PACKAGE_NAME "GameCpp")
    set(CPACK_NSIS_URL_INFO_ABOUT "")
    set(CPACK_NSIS_CONTACT "your.email@example.com")
elseif(APPLE)
    set(CPACK_GENERATOR "ZIP;DragNDrop")
else()
    set(CPACK_GENERATOR "ZIP;TGZ")
endif()

include(CPack)