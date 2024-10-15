//
// Created by thehedgeh0g on 15.10.24.
//

#ifndef ICANVAS_H
#define ICANVAS_H
#include "Color.h"
#include "Point.h"

class ICanvas
{
public:
    virtual ~ICanvas() = default;

    void virtual DrawLine(Point start, Point end) = 0;
    void virtual DrawEllipse(Point center, double hx, double hy)= 0;
    void virtual SetColor(Color color) = 0;
};
#endif //ICANVAS_H
