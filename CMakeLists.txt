cmake_minimum_required(VERSION 3.29)
project(OODLabs)

set(CMAKE_CXX_STANDARD 20)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)

FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.2
)

FetchContent_MakeAvailable(json)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
)

FetchContent_MakeAvailable(fmt)

find_package(PkgConfig REQUIRED)
pkg_check_modules(CAIRO REQUIRED cairo)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(OODLabs3_1 3/3_1/main.cpp
        6/Test/Tests.cpp
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

add_executable(OODLabsTest4_1 4/Test/test.cpp
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
target_link_libraries(OODLabsTest4_1 gtest_main gmock gtest)
enable_testing()
add_test(NAME OODLabsTest4_1 COMMAND OODLabsTest4_1)

target_link_libraries(OODLabs4_1 PRIVATE nlohmann_json::nlohmann_json)
target_compile_features(OODLabs4_1 PRIVATE cxx_std_17)

add_executable(OODLabs5_1 5/main.cpp
        5/Src/Document/IDocument.h
        5/Src/Document/Document.h
        5/Src/DocumentItem/DocumentItem.h
        5/Src/DocumentItem/ConstDocumentItem.h
        5/Src/DocumentItem/IImage.h
        5/Src/DocumentItem/IParagraph.h
        5/Src/DocumentItem/Image.h
        5/Src/DocumentItem/Paragraph.h
        5/Src/History/History.h
        5/Src/Command/ICommand.h
        5/Src/Command/AbstractCommand.h
        5/Src/Command/InsertParagraphCommand.h
        5/Src/Command/InsertImageCommand.h
        5/Src/Command/DeleteCommand.h
        5/Src/Command/SetTitleCommand.h
        5/Src/Command/ResizeImageCommand.h
        5/Src/Command/EditParagraphCommand.h
        5/Src/Command/SaveCommand.h
        5/Src/Client/Client.h
        5/Src/Command/DeleteCommand.cpp
        5/Src/Command/EditParagraphCommand.cpp
        5/Src/Command/InsertImageCommand.cpp
        5/Src/Command/InsertParagraphCommand.cpp
        5/Src/Command/ResizeImageCommand.cpp
        5/Src/Command/SaveCommand.cpp
        5/Src/Command/SetTitleCommand.cpp
        5/Src/Command/MacroCommand.cpp
        5/Src/Command/MacroCommand.h
        5/Src/Command/AbstractCommand.cpp
        5/Src/Document/Document.cpp
        5/Src/Client/Client.cpp
)

add_executable(OODLabsTest5_1 5/Test/Tests.cpp
        5/Src/Document/IDocument.h
        5/Src/Document/Document.h
        5/Src/DocumentItem/DocumentItem.h
        5/Src/DocumentItem/ConstDocumentItem.h
        5/Src/DocumentItem/IImage.h
        5/Src/DocumentItem/IParagraph.h
        5/Src/DocumentItem/Image.h
        5/Src/DocumentItem/Paragraph.h
        5/Src/History/History.h
        5/Src/Command/ICommand.h
        5/Src/Command/AbstractCommand.h
        5/Src/Command/InsertParagraphCommand.h
        5/Src/Command/InsertImageCommand.h
        5/Src/Command/DeleteCommand.h
        5/Src/Command/SetTitleCommand.h
        5/Src/Command/ResizeImageCommand.h
        5/Src/Command/EditParagraphCommand.h
        5/Src/Command/SaveCommand.h
        5/Src/Client/Client.h
        5/Src/Command/DeleteCommand.cpp
        5/Src/Command/EditParagraphCommand.cpp
        5/Src/Command/InsertImageCommand.cpp
        5/Src/Command/InsertParagraphCommand.cpp
        5/Src/Command/ResizeImageCommand.cpp
        5/Src/Command/SaveCommand.cpp
        5/Src/Command/SetTitleCommand.cpp
        5/Src/Command/MacroCommand.cpp
        5/Src/Command/MacroCommand.h
        5/Src/Command/AbstractCommand.cpp
        5/Src/Document/Document.cpp
        5/Src/Client/Client.cpp
)

target_link_libraries(OODLabsTest5_1 gtest_main gmock gtest)
enable_testing()
add_test(NAME OODLabsTest5_1 COMMAND OODLabsTest5_1)

add_executable(OODLabs6_1 6/main.cpp
        6/app/ModernGraphicsCanvasAdapter.h
        6/app/ModernGraphicsCanvasClassAdapter.h
        6/modern_graphics_lib/modern_graphics_lib.h
        6/shape_drawing_lib/shape_drawing_lib.h
        6/graphics_lib/graphics_lib.h
)

add_executable(OODLabsTest6_1 6/Test/Tests.cpp
        6/app/ModernGraphicsCanvasAdapter.h
        6/modern_graphics_lib/modern_graphics_lib.h
        6/shape_drawing_lib/shape_drawing_lib.h
        6/graphics_lib/graphics_lib.h
)

target_link_libraries(OODLabsTest6_1 gtest_main gmock gtest)
enable_testing()
add_test(NAME OODLabsTest6_1 COMMAND OODLabsTest6_1)

add_executable(OODLabs7_1 7/main.cpp
        7/Canvas/ICanvas.h
        7/Style/Style.h
        7/Shape/IShape.h
        7/Shape/Rectangle.h
        7/Shape/Ellipse.h
        7/Shape/Group.h
        7/Slide/Slide.h
        7/Shape/Point.h
        7/Canvas/CairoCanvas.h
        7/Shape/Triangle.h
        7/Canvas/ConsoleCanvas.h
        7/Style/Color.h
        7/Style/IStyle.h
        7/Style/IGroupStyle.h
        7/Style/GroupStyle.h
        7/Shape/Shape.h
        7/Shape/IGroup.h
        7/ShapeFactory/IShapeFactory.h
        7/ShapeFactory/ShapeFactory.h
        7/Client.h
        7/Slide/SlideBuilder.h
        7/Shape/RectD.h
)

target_include_directories(OODLabs7_1 PRIVATE ${CAIRO_INCLUDE_DIRS})
target_link_libraries(OODLabs7_1 PRIVATE ${CAIRO_LIBRARIES})

add_executable(OODLabsTest7_1 7/Test/Test.cpp
        7/Canvas/ICanvas.h
        7/Style/Style.h
        7/Shape/IShape.h
        7/Shape/Rectangle.h
        7/Shape/Ellipse.h
        7/Shape/Group.h
        7/Shape/Triangle.h
        7/ShapeFactory/IShapeFactory.h
        7/ShapeFactory/ShapeFactory.h
        7/Canvas/ConsoleCanvas.h
)

target_link_libraries(OODLabsTest7_1 gtest_main gmock gtest)

add_executable(OODLabs8_2 8/main.cpp
        8/MultiGumBallMachine/IMultiGumballMachine.h
        8/MultiGumBallMachine/State/HasQuarterState.h
        8/MultiGumBallMachine/State/IState.h
        8/MultiGumBallMachine/State/NoQuarterState.h
        8/MultiGumBallMachine/State/SoldOutState.h
        8/MultiGumBallMachine/State/SoldState.h
        8/MultiGumBallMachine/MultiGumballMachine.h
        8/Menu/Commands/ICommand.h
        8/Menu/Commands/InsertCoinCommand.h
        8/Menu/Commands/TurnCrankCommand.h
        8/Menu/Commands/RefillCommand.h
        8/Menu/Commands/ExitCommand.h
        8/Menu/Menu.h
        8/Menu/Commands/EjectCoinsCommand.h
        8/MultiGumBallMachine/Naive/NaiveGumBallMachine.h)
target_link_libraries(OODLabs8_2 fmt::fmt)

add_executable(OODLabsTest8_2 8/Test/Test.cpp
        8/MultiGumBallMachine/IMultiGumballMachine.h
        8/MultiGumBallMachine/State/HasQuarterState.h
        8/MultiGumBallMachine/State/IState.h
        8/MultiGumBallMachine/State/NoQuarterState.h
        8/MultiGumBallMachine/State/SoldOutState.h
        8/MultiGumBallMachine/State/SoldState.h
        8/MultiGumBallMachine/MultiGumballMachine.h)
target_link_libraries(OODLabsTest8_2 gtest_main gmock gtest fmt::fmt)

add_executable(OODLabsTest8_1 8/Test/StateTest.cpp)
target_link_libraries(OODLabsTest8_1 gtest_main gmock gtest fmt::fmt)

add_executable(OODLabsTest8_2_1 8/Test/NaiveTest.cpp
        8/MultiGumBallMachine/Naive/NaiveGumBallMachine.h)
target_link_libraries(OODLabsTest8_2_1 gtest_main gmock gtest fmt::fmt)
