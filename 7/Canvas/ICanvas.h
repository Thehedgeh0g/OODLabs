//
// Created by flipd on 05.11.2024.
//

#ifndef ICANVAS_H
#define ICANVAS_H
#include <string>
#include <vector>
#include "./../Shape/Point.h"

class ICanvas {
public:
    virtual void SetFillColor(const std::string& color) = 0;
    virtual void SetLineColor(const std::string& color) = 0;
    virtual void SetLineThickness(double thickness) = 0;
    virtual void DrawLine(Point start, Point end) = 0;
    virtual void DrawEllipse(Point center, double hx, double hy) = 0;
    virtual void FillEllipse(double x, double y, double width, double height) = 0;
    virtual void FillPolygon(const std::vector<std::pair<double, double>>& points) = 0;
    virtual ~ICanvas() = default;
};

#endif //ICANVAS_H
