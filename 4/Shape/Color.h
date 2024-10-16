//
// Created by thehedgeh0g on 15.10.24.
//

#ifndef COLOR_H
#define COLOR_H
#include <cstdint>
#include <map>
#include <string>

namespace shape
{
    enum class Color : int {
        RED = 0,
        GREEN = 1,
        BLUE = 2,
        PINK = 3,
        YELLOW = 4,
        BLACK = 5
      };

    const std::map<Color, uint32_t> colorsToHEX = {
        {Color::GREEN, 0xFF00FF00FF},
        {Color::RED, 0xFFFF0000FF},
        {Color::BLUE, 0xFF0000FFFF},
        {Color::YELLOW, 0xFFFFFF00FF},
        {Color::PINK, 0xFFFFC0CBFF},
        {Color::BLACK, 0xFF000000FF}
    };

    const std::map<std::string, Color> stringToColor = {
        {"green", Color::GREEN},
        {"red", Color::RED},
        {"blue", Color::BLUE},
        {"yellow", Color::YELLOW},
        {"pink", Color::PINK},
        {"black", Color::BLACK}
    };

    inline uint32_t convertColorToHEX(Color color)
    {
        return colorsToHEX.at(color);
    }

    inline Color convertToColor(const std::string& colorStr)
    {
        return stringToColor.at(colorStr);
    }
}

#endif //COLOR_H
