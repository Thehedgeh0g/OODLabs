cmake_minimum_required(VERSION 3.29)
project(OODLabs)

set(CMAKE_CXX_STANDARD 20)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.2
)

FetchContent_MakeAvailable(json)

add_executable(OODLabs3_1 3/3_1/main.cpp
)

add_executable(OODLabs4_1 4/main.cpp
        4/Shape/Color.h
        4/Shape/Point.h
        4/Draft/ICanvas.h
        4/Shape/Shape.h
        4/Shape/Triangle.h
        4/Shape/Ellipse.h
        4/Shape/Rectangle.h
        4/Shape/RegularPolygon.h
        4/ShapeFactory/IShapeFactory.h
        4/ShapeFactory/ShapeFactory.h
        4/Shape/ShapeNames.h
        4/Draft/PictureDraft.h
        4/Designer/IDesigner.h
        4/Designer/Designer.h
        4/Painter/IPainter.h
        4/Painter/Painter.h
        4/Client/Client.h
        4/Canvas/Canvas.h
        4/Canvas/Canvas.cpp
        4/Config/ConfigProvider.h
)
target_link_libraries(OODLabs4_1 PRIVATE sfml-graphics sfml-window sfml-system)
target_link_libraries(OODLabs4_1 PRIVATE nlohmann_json::nlohmann_json)
target_compile_features(OODLabs4_1 PRIVATE cxx_std_17)
