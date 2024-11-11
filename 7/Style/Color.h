//
// Created by thehedgeh0g on 10.11.24.
//

#ifndef COLOR_H
#define COLOR_H
#include <cstdint>

namespace style
{
class Color
{
public:
    uint8_t r, g, b, a;

    bool operator==(const Color &rhs) const
    {
        return (r == rhs.r) && (g == rhs.g) && (b == rhs.b) && (a == rhs.a);
    }

    explicit Color(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0, uint8_t a = 0): r(0), g(0), b(0), a(0)
    {
    }

    explicit Color(const std::string &colorStr)
    {
        uint32_t hexedColor;
        if (colorStr.size() != 9 || colorStr[0] != '#')
        {
            throw std::invalid_argument("Invalid color string");
        }
        std::stringstream ss;
        ss << std::hex << colorStr.substr(1);
        ss >> hexedColor;
        r = static_cast<uint8_t>((hexedColor >> 24) & 0xFF);
        g = static_cast<uint8_t>((hexedColor >> 16) & 0xFF);
        b = static_cast<uint8_t>((hexedColor >> 8) & 0xFF);
        a = static_cast<uint8_t>(hexedColor & 0xFF);
    }
};

inline std::ostream &operator<<(std::ostream &os, const Color &color)
{
    return os << "r: " << color.r << "; g:" << color.g << "; b:" << color.b << "; a:" << color.a;
}
}

#endif //COLOR_H
