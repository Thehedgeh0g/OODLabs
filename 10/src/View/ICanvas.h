//
// Created by flipd on 25.12.2024.
//

#ifndef ICANVAS_H
#define ICANVAS_H
#include <cstdint>

namespace view {
    class ICanvas {
    public:
        virtual ~ICanvas() = default;

        virtual void SetColor(uint32_t color) = 0;

        virtual void MoveTo(double x, double y) = 0;

        virtual void LineTo(double x, double y) = 0;

        virtual void DrawEllipse(double cx, double cy, double cr, double ry) = 0;

        virtual void DrawText(double top, double left, double fontSize, const std::string &text) = 0;
    };
}
#endif //ICANVAS_H
