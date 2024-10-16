//
// Created by thehedgeh0g on 15.10.24.
//

#ifndef ICANVAS_H
#define ICANVAS_H
#include "./../Shape/Color.h"
#include "./../Shape/Point.h"

namespace draft
{
    class ICanvas
    {
    public:
        virtual ~ICanvas() = default;

        void virtual DrawLine(shape::Point start, shape::Point end) = 0;
        void virtual DrawEllipse(shape::Point center, double hx, double hy) = 0;
        void virtual SetColor(shape::Color color) = 0;
    };
}
#endif //ICANVAS_H
