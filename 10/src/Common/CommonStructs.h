//
// Created by flipd on 24.12.2024.
//

#ifndef COMMONSTRUCTS_H
#define COMMONSTRUCTS_H
#include <optional>

enum class ShapeType { Circle, Rectangle, Triangle };
enum class UpdateType { Move, Resize };
enum class ViewInteractionType { MouseDown, MouseUp, ButtonPress };

struct Point {
    double x, y;
    bool operator == (const Point &other) const {
        return x == other.x && y == other.y;
    }
};

struct RectD {
    double width{}, height{};
    Point point{};
    RectD() = default;
    RectD(const double x, const double y, const double width, const double height): width(width), height(height), point(x, y) {}
    RectD(const RectD& other) {
        width = other.width;
        height = other.height;
        point = other.point;
    }

    bool operator == (const RectD &other) const {
        return point == other.point && width == other.width && height == other.height;
    }

    bool operator != (const RectD &other) const {
        return !(other == *this);
    }
};

struct ShapeDTO {
    std::optional<std::string> id;
    std::optional<ShapeType> type;
    std::optional<RectD> frame;
    std::optional<uint32_t> color;
};

#endif //COMMONSTRUCTS_H
