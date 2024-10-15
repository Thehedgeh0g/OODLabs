//
// Created by ilya.lezhnin on 18.09.24.
//

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "./../Draft/Point.h"
#include "./../Draft/Shape.h"


class Triangle : public Shape
{
public:
    Triangle(const Color color, const Point vertex1, const Point vertex2, const Point vertex3): Shape(color),
        m_vertex1(vertex1),
        m_vertex2(vertex2),
        m_vertex3(vertex3)
    {
    }

    ~Triangle() override = default;

    void Draw(ICanvas &canvas) override
    {
        canvas.SetColor(m_color);
        canvas.DrawLine(m_vertex1, m_vertex2);
        canvas.DrawLine(m_vertex2, m_vertex3);
        canvas.DrawLine(m_vertex3, m_vertex1);
    }

    [[nodiscard]] Point GetVertex1() const
    {
        return m_vertex1;
    }

    [[nodiscard]] Point GetVertex2() const
    {
        return m_vertex2;
    }

    [[nodiscard]] Point GetVertex3() const
    {
        return m_vertex3;
    }

private:
    Point m_vertex1;
    Point m_vertex2;
    Point m_vertex3;
};


#endif //TRIANGLE_H
