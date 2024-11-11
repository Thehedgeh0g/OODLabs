#include <fstream>

#include "Client.h"
#include "Canvas/CairoCanvas.h"
#include "Canvas/ConsoleCanvas.h"
#include "ShapeFactory/ShapeFactory.h"
#include "Slide/Slide.h"

int main()
{
    try
    {
        std::string filename = "./../bin/Input.txt";
        auto consoleCanvas = std::make_shared<ConsoleCanvas>(std::cout);
        auto canvas = std::make_shared<CairoCanvas>(1080, 720, "./../bin/Output.png");
        Slide slide;
        shapeFactory::ShapeFactory factory;
        SlideService slideService{factory};
        Client client(slideService);
        std::ifstream in(filename);
        client.HandleCommands(in, canvas);

        std::cout << "Фигуры успешно загружены и отображены." << std::endl;
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Ошибка: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
