//
// Created by thehedgeh0g on 15.10.24.
//

#include <fstream>

#include "Client/Client.h"
#include "Designer/Designer.h"
#include "Painter/Painter.h"
#include "Canvas/Canvas.h"
#include "Config/ConfigProvider.h"

int main()
{
    auto configProvider = ConfigProvider("./../Data/Config.json");
    std::ifstream in(configProvider.getInputPath());
    auto shapeFactory = std::make_unique<Factory::ShapeFactory>();
    auto designer = std::make_unique<Designer::Designer>(std::move(shapeFactory));
    auto painter = std::make_unique<Painter::Painter>();
    auto canvas = std::make_unique<gfx::Canvas>(1000, 800, configProvider.getOutputPath());
    auto client = Client(std::move(designer), std::move(painter), std::move(canvas));
    client.Run(in, std::cout);
    return 0;
}
