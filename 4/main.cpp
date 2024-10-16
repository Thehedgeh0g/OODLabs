//
// Created by thehedgeh0g on 15.10.24.
//

#include <fstream>

#include "Client/Client.h"
#include "Designer/Designer.h"
#include "Painter/Painter.h"
#include "SFML/Canvas.h"

int main()
{
    std::ifstream in("hello.txt");
    auto shapeFactory = std::make_unique<ShapeFactory>();
    auto designer = std::make_unique<Designer>(std::move(shapeFactory));
    auto painter = std::make_unique<Painter>();
    auto canvas = std::make_unique<Canvas>(1000, 800);
    auto client = Client(std::move(designer), std::move(painter), std::move(canvas));
    client.Run(in, std::cout);
    return 0;
}
