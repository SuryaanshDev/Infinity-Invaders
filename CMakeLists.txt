cmake_minimum_required(VERSION 3.28)
project(GameCpp LANGUAGES CXX)

# Set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Set default build type to Release if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# Platform-specific compiler flags
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    if(MSVC)
        # Visual Studio compiler
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
    else()
        # GCC/Clang
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
    endif()
    
    if(WIN32 AND NOT MSVC)
        # Hide console window in release mode on Windows (MinGW)
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

# Platform-specific compile definitions
if(WIN32)
    target_compile_definitions(GameCpp PRIVATE SFML_STATIC)
endif()

# Link libraries
target_link_libraries(GameCpp PRIVATE SFML::Graphics SFML::Audio)

# Include directories
target_include_directories(GameCpp PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

# Platform-specific settings
if(WIN32)
    # Windows-specific settings
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        set_target_properties(GameCpp PROPERTIES WIN32_EXECUTABLE TRUE)
        
        # Copy SFML DLLs to output directory
        add_custom_command(TARGET GameCpp POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_FILE:SFML::System>
                $<TARGET_FILE:SFML::Window>
                $<TARGET_FILE:SFML::Graphics>
                $<TARGET_FILE:SFML::Audio>
                $<TARGET_FILE_DIR:GameCpp>
        )
    endif()
    
elseif(APPLE)
    # macOS-specific settings
    set_target_properties(GameCpp PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/Info.plist
    )
    
    # Find and link required frameworks
    find_library(COCOA_LIBRARY Cocoa)
    find_library(IOKIT_LIBRARY IOKit)
    find_library(COREVIDEO_LIBRARY CoreVideo)
    find_library(OPENGL_LIBRARY OpenGL)
    
    target_link_libraries(GameCpp PRIVATE 
        ${COCOA_LIBRARY}
        ${IOKIT_LIBRARY}
        ${COREVIDEO_LIBRARY}
        ${OPENGL_LIBRARY}
    )
    
elseif(UNIX)
    # Linux-specific settings
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
    
    # Link X11 and other required libraries
    find_package(X11 REQUIRED)
    target_link_libraries(GameCpp PRIVATE ${X11_LIBRARIES})
    
    # Set RPATH for shared libraries
    set_target_properties(GameCpp PROPERTIES
        INSTALL_RPATH_USE_LINK_PATH TRUE
        INSTALL_RPATH "\$ORIGIN"
    )
endif()

# Install configuration for packaging
install(TARGETS GameCpp
    BUNDLE DESTINATION .    # For macOS bundles
    RUNTIME DESTINATION .   # For Windows executables and Linux binaries
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/resources
    DESTINATION .
)

# Platform-specific installations
if(WIN32)
    # Windows DLL installation
    install(FILES
        $<TARGET_FILE:SFML::System>
        $<TARGET_FILE:SFML::Window>
        $<TARGET_FILE:SFML::Graphics>
        $<TARGET_FILE:SFML::Audio>
        DESTINATION .
    )
elseif(APPLE)
    # macOS bundle resources
    install(DIRECTORY ${CMAKE_SOURCE_DIR}/resources
        DESTINATION GameCpp.app/Contents/Resources
    )
endif()

# CPack configuration for creating distributable packages
set(CPACK_PACKAGE_NAME "GameCpp")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Space Shooter Game")
set(CPACK_PACKAGE_VENDOR "Senpai")
set(CPACK_PACKAGE_CONTACT "surya94191@gmail.com")

if(WIN32)
    set(CPACK_GENERATOR "ZIP;NSIS")
    set(CPACK_NSIS_DISPLAY_NAME "GameCpp - Space Shooter")
    set(CPACK_NSIS_PACKAGE_NAME "GameCpp")
    set(CPACK_NSIS_URL_INFO_ABOUT "")
    set(CPACK_NSIS_CONTACT "surya94191@gmail.com")
    set(CPACK_NSIS_MODIFY_PATH ON)
elseif(APPLE)
    set(CPACK_GENERATOR "ZIP;DragNDrop")
    set(CPACK_DMG_FORMAT "UDZO")
    set(CPACK_DMG_VOLUME_NAME "GameCpp")
    set(CPACK_BUNDLE_NAME "GameCpp")
else()
    # Linux
    set(CPACK_GENERATOR "ZIP;TGZ;DEB")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "surya94191@gmail.com")
    set(CPACK_DEBIAN_PACKAGE_DEPENDS "libsfml-dev")
    set(CPACK_DEBIAN_PACKAGE_SECTION "games")
endif()

include(CPack)