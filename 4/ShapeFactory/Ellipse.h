//
// Created by ilya.lezhnin on 18.09.24.
//

#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "./../Draft/Point.h"
#include "./../Draft/Shape.h"


class Ellipse : public Shape {
public:
    Ellipse(const Color color, const Point center, const double hx, const double hy): Shape(color), m_center(center), m_hx(hx), m_hy(hy) {
    };

    ~Ellipse() override = default;

    void Draw(ICanvas& canvas) override
    {
        canvas.SetColor(m_color);
        canvas.DrawEllipse(m_center, m_hx, m_hy);
    };

    [[nodiscard]] Point GetCenter() const
    {
        return m_center;
    }

    [[nodiscard]] double GetHorizontalRadius() const
    {
        return m_hx;
    }

    [[nodiscard]] double GetVerticalRadius() const
    {
        return m_hy;
    }

private:
    Point m_center;
    double m_hx;
    double m_hy;
};


#endif //ELLIPSE_H
