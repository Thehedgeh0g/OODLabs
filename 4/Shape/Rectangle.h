//
// Created by ilya.lezhnin on 18.09.24.
//

#ifndef RECTANGE_H
#define RECTANGE_H

#include "Point.h"
#include "Shape.h"


namespace shape
{
    class Rectangle : public Shape
    {
    public:
        Rectangle(Color color, const Point leftTop, const Point rightBottom) :
            Shape(color),
            m_leftTop(leftTop),
            m_rightBottom(rightBottom)
        {
        }

        ~Rectangle() override = default;

        void Draw(draft::ICanvas& canvas) override
        {
            canvas.SetColor(m_color);
            canvas.DrawLine(m_leftTop, {m_rightBottom.x, m_leftTop.y});
            canvas.DrawLine({m_rightBottom.x, m_leftTop.y}, m_rightBottom);
            canvas.DrawLine(m_rightBottom, {m_leftTop.x, m_rightBottom.y});
            canvas.DrawLine({m_leftTop.x, m_rightBottom.y}, m_leftTop);
        }

        [[nodiscard]] Point GetLeftTop() const
        {
            return m_leftTop;
        }

        [[nodiscard]] Point GetRightBottom() const
        {
            return m_rightBottom;
        }

    private:
        Point m_leftTop;
        Point m_rightBottom;
    };
}

#endif //RECTANGE_H
