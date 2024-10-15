//
// Created by ilya.lezhnin on 18.09.24.
//

#ifndef IFIGURE_H
#define IFIGURE_H

#include "ICanvas.h"

class Shape
{
public:
    virtual ~Shape() = default;

    explicit Shape(Color color) : m_color(color)
    {
    }

    virtual void Draw(ICanvas &canvas) = 0;

    [[nodiscard]] Color GetColor() const { return m_color; }

protected:
    Color m_color;
};

#endif //IFIGURE_H
