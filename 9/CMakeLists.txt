cmake_minimum_required(VERSION 3.29)
project(9)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)
include_directories(src)

add_executable(9
        src/CoW.h
        src/Drawer.h
        src/Geom.h
        src/Image.h
        main.cpp
        src/Tile.h
        src/ImageService.h)


add_executable(${PROJECT_NAME}_test Tests/Test.cpp
        src/Image.h
)
target_link_libraries(${PROJECT_NAME}_test gtest_main gmock gtest)
enable_testing()
add_test(NAME ${PROJECT_NAME}_test COMMAND ${PROJECT_NAME}_test)