#include "Canvas/CairoCanvas.h"
#include "Canvas/ConsoleCanvas.h"
#include "ShapeLoader/ShapeLoader.h"
#include "Slide/Slide.h"

int main() {
    try {
        std::string filename = "./../bin/Input.txt";
        auto shapes = ShapeLoader::loadShapesFromFile(filename);
        ConsoleCanvas consoleCanvas(std::cout);
        CairoCanvas canvas(1080, 720, "./../bin/Output.png");
        Slide slide;

        for (const auto& shape : shapes) {
            slide.AddShape(shape);
        }

        slide.Draw(canvas);

        std::cout << "Фигуры успешно загружены и отображены." << std::endl;
    } catch (const std::exception& ex) {
        std::cerr << "Ошибка: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
