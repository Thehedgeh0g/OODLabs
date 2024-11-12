//
// Created by ilya.lezhnin on 18.09.24.
//

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Point.h"
#include "IShape.h"

namespace shapes
{
class Triangle : public Shape
{
public:
    Triangle(
        const Point vertex1,
        const Point vertex2,
        const Point vertex3,
        std::unique_ptr<style::IStyle> outlineStyle,
        std::unique_ptr<style::IStyle> fillStyle
    ): Shape(std::move(outlineStyle), std::move(fillStyle)),
        m_vertex1(vertex1),
        m_vertex2(vertex2),
        m_vertex3(vertex3)
    {
    }

    ~Triangle() override = default;

    void DrawImpl(ICanvas &canvas) const override
    {
        const style::IStyle &outlineStyle = GetOutlineStyle();
        const style::IStyle &fillStyle = GetFillStyle();
        if (fillStyle.IsEnabled().value())
        {
            canvas.SetFillColor(fillStyle.GetColor().value());
            canvas.FillPolygon({{m_vertex1.x, m_vertex1.y}, {m_vertex2.x, m_vertex2.y}, {m_vertex3.x, m_vertex3.y}});
        }
        if (outlineStyle.IsEnabled().value())
        {
            canvas.SetLineColor(outlineStyle.GetColor().value());
            canvas.DrawLine(m_vertex1, m_vertex2);
            canvas.DrawLine(m_vertex2, m_vertex3);
            canvas.DrawLine(m_vertex3, m_vertex1);
        }
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
}
#endif //TRIANGLE_H
