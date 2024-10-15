//
// Created by thehedgeh0g on 15.10.24.
//

#include "Client/Client.h"
#include "Designer/Designer.h"
#include "Painter/Painter.h"
#include "SFML/Canvas.h"

int main()
{
    auto shapeFactory = std::make_unique<ShapeFactory>();
    auto designer = std::make_unique<Designer>(std::move(shapeFactory));
    auto painter = std::make_unique<Painter>();
    auto window = std::make_unique<Window>();
    auto canvas = std::make_unique<Canvas>(std::move(window));
    auto client = Client(std::move(designer), std::move(painter), std::move(canvas));
    client.Run(std::cin, std::cout);
    return 0;
}
