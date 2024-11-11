//
// Created by flipd on 05.11.2024.
//

#ifndef ICANVAS_H
#define ICANVAS_H
#include <string>
#include <vector>

#include "../Style/Color.h"
#include "./../Shape/Point.h"

class ICanvas {
public:
    virtual void SetFillColor(const style::Color& color) = 0;
    virtual void SetLineColor(const style::Color& color) = 0;
    virtual void SetLineThickness(double thickness) = 0;
    virtual void DrawLine(shapes::Point start, shapes::Point end) = 0;
    virtual void DrawEllipse(shapes::Point center, double hx, double hy) = 0;
    virtual void FillEllipse(shapes::Point center, double width, double height) = 0;
    virtual void FillPolygon(const std::vector<std::pair<double, double>>& points) = 0;
    virtual ~ICanvas() = default;
};

#endif //ICANVAS_H
