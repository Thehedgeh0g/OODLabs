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

add_executable(OODLabs3_1 3/3_1/main.cpp
)

add_executable(OODLabs4_1 4/main.cpp
        4/Draft/Color.h
        4/Draft/Point.h
        4/Draft/ICanvas.h
        4/Draft/Shape.h
        4/ShapeFactory/Triangle.h
        4/ShapeFactory/Ellipse.h
        4/ShapeFactory/Rectangle.h
        4/ShapeFactory/RegularPolygon.h
        4/ShapeFactory/IShapeFactory.h
        4/ShapeFactory/ShapeFactory.h
        4/ShapeFactory/ShapeNames.h
        4/Draft/PictureDraft.h
        4/Designer/IDesigner.h
        4/Designer/Designer.h
        4/Painter/IPainter.h
        4/Painter/Painter.h
        4/Client/Client.h
        4/SFML/Canvas.h
        4/SFML/Canvas.cpp
)
target_link_libraries(OODLabs4_1 PRIVATE sfml-graphics sfml-window sfml-system)
target_compile_features(OODLabs4_1 PRIVATE cxx_std_17)
