//
// Created by ilya.lezhnin on 18.09.24.
//

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Point.h"
#include "IShape.h"


class Triangle : public IShape
{
public:
    Triangle(const Point vertex1, const Point vertex2, const Point vertex3):
        m_vertex1(vertex1),
        m_vertex2(vertex2),
        m_vertex3(vertex3)
    {
    }

    const LineStyle& GetLineStyle() const override { return m_lineStyle; }
    void SetLineStyle(const LineStyle& style) override { m_lineStyle = style; }
    const FillStyle& GetFillStyle() const override { return m_fillStyle; }
    void SetFillStyle(const FillStyle& style) override { m_fillStyle = style; }

    ~Triangle() override = default;

    void Draw(ICanvas& canvas) const override
    {
        if (m_lineStyle.isEnabled)
        {
            canvas.SetLineColor(m_lineStyle.color);
            canvas.SetLineThickness(m_lineStyle.thickness);
            canvas.DrawLine(m_vertex1, m_vertex2);
            canvas.DrawLine(m_vertex2, m_vertex3);
            canvas.DrawLine(m_vertex3, m_vertex1);
        }
        if (m_fillStyle.isEnabled)
        {
            canvas.SetFillColor(m_fillStyle.color);
            canvas.FillPolygon({{m_vertex1.x, m_vertex1.y}, {m_vertex2.x, m_vertex2.y}, {m_vertex3.x, m_vertex3.y}});
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
    LineStyle m_lineStyle;
    FillStyle m_fillStyle;
};

#endif //TRIANGLE_H
