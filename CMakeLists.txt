cmake_minimum_required(VERSION 3.9.2)
project(ExMachina)

if(UNIX AND APPLE)
    set(PLATFORM "osx" )
elseif(UNIX)
    set(PLATFORM "linux")
else()
    set(PLATFORM "win")
endif()

## hide console unless debug build ##
if (NOT CMAKE_BUILD_TYPE STREQUAL  "Debug" AND WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows")
endif()

set(CMAKE_DEBUG_POSTFIX d)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

## set to true to use dlls instead of static libs ##
set(BUILD_SHARED_LIBS false)

## itch.io and gamedata settings ##
set(GAMEDATA_FOLDER "Data")
set(ITCHIO_USER     "")

## files used to build this game
add_executable(
        ${PROJECT_NAME}
        main.cpp
        Source/MyGame.cpp
        Source/MyGame.h
        Source/Clue.cpp
        Source/Clue.h
        Source/Constants.h
        Source/GameObject.cpp
        Source/GameObject.h
        Source/Exit.cpp
        Source/Exit.h
        Source/Item.cpp
        Source/Item.h
        Source/Puzzle.cpp
        Source/Puzzle.h
        Source/Player.cpp
        Source/Player.h
        Source/Room.cpp
        Source/Room.h
        Source/Switch.cpp
        Source/Switch.h)

## library includes
target_include_directories(
        ${PROJECT_NAME}
        SYSTEM
        PRIVATE
        "${CMAKE_SOURCE_DIR}/Libs/ASGE/include"
        "${CMAKE_SOURCE_DIR}/Libs/soloud/include")

## compile language settings
target_compile_features(
        ${PROJECT_NAME}
        PRIVATE
        cxx_std_17)


if ( CMAKE_COMPILER_IS_GNUCC )
    list(APPEND BUILD_FLAGS_FOR_CXX
            "-Wall" "-Wextra" "-Wshadow" "-Wnon-virtual-dtor"
            "-Wold-style-cast" "-Wunused" "-pedantic"
            "-Woverloaded-virtual" "-Wpedantic" "-Wconversion"
            "-Wduplicated-cond" "-Wduplicated-branches" "-Wlogical-op"
            "-Wnull-dereference" "-Wuseless-cast"
            "-Wno-unused-parameter" "-Werror")

    target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<COMPILE_LANGUAGE:CXX>:${BUILD_FLAGS_FOR_CXX}>)

    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0" )
elseif( MSVC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /W4 /WX")
endif()

## build the game libs folder
add_library(ASGE UNKNOWN IMPORTED)
add_subdirectory(Libs)
target_link_libraries(${PROJECT_NAME} ASGE)

## copy the dlls post build
if(BUILD_SHARED_LIBS)
    # copy the game engine dll to bin
    add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different

            "${GameEngineDLL}"
            $<TARGET_FILE_DIR:${PROJECT_NAME}>)

    if(WIN32 AND NOT MSVC)
        # copy the mingw runtime files to bin
        add_custom_command(
                TARGET ${PROJECT_NAME} PRE_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/Libs/mingw64/bin $<TARGET_FILE_DIR:${PROJECT_NAME}>)
    endif()
endif()


## enable static linking against gcc build
if (WIN32 AND NOT BUILD_SHARED_LIBS AND NOT MSVC)
    target_link_libraries(${PROJECT_NAME} -static)
endif()


## build types
set(CMAKE_CONFIGURATION_TYPES Debug;Release)

 # Fetch the soloud project and link to it. We need to FORCE the engine on.
SET(ENABLE_SOUND ON CACHE BOOL "Adds SoLoud to the project" FORCE)
## utility scripts
include(CMake/datpak.cmake)
target_link_libraries(${PROJECT_NAME} soloud)