cmake_minimum_required(VERSION 3.29)
project(10)

set(CMAKE_CXX_STANDARD 20)
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ./../bin )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY  ./../lib )

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
        sfml
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG master
)
FetchContent_MakeAvailable(sfml)

FetchContent_Declare(
        Boost
        URL https://github.com/boostorg/boost/releases/download/boost-1.84.0/boost-1.84.0.tar.xz
        URL_MD5 893b5203b862eb9bbd08553e24ff146a
        DOWNLOAD_EXTRACT_TIMESTAMP ON
)

set(BOOST_INCLUDE_LIBRARIES filesystem regex signals2)
FetchContent_MakeAvailable(Boost)

add_executable(10
        src/main.cpp
        src/Domain/IdGenerator.h
        src/Common/CommonStructs.h
        src/Domain/Shape.h
        src/Domain/Draft.h
        src/App/DraftFacade.h
        src/App/Commands/UpdateShapeCommand.h
        src/App/AppDataObjects/ShapeSelection.h
        src/App/UseCase/InsertShapeUseCase.h
        src/App/UseCase/IUseCase.h
        src/App/AppDataObjects/DraftContainer.h
        src/Infrastructure/SFMLCanvas.h
        src/Infrastructure/SFMLCanvas.cpp
        src/View/ShapeStrategies/IFigure.h
        src/View/ShapeStrategies/Circle.h
        src/View/ShapeStrategies/Rectangle.h
        src/View/ShapeStrategies/Triangle.h
        src/View/Components/VWindow.h
        src/View/Components/VShape.h
        src/View/ICanvas.h
        src/Presentor/IPresentor.h
        src/Presentor/PDraft.h
        src/Presentor/PShape.h
        src/Presentor/MainPresenter.h
        src/History/AbstractCommand.cpp
        src/History/AbstractCommand.h
        src/History/History.h
        src/History/ICommand.h
        src/History/MacroCommand.cpp
        src/History/MacroCommand.h
        src/Common/IObservable.h
        src/View/Components/VMenu.h
        src/Presentor/IInteractionEvent.h
        src/Infrastructure/SFMLEvent.h
        src/App/AppDataObjects/SubscriptionContainer.h
)

target_link_libraries(10 sfml-graphics sfml-window sfml-system Boost::filesystem Boost::signals2)