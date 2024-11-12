//
// Created by flipd on 05.11.2024.
//

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"
#include "./../Canvas/ICanvas.h"
#include "./../Style/Style.h"


namespace shapes
{
class Rectangle : public Shape
{
public:
    Rectangle(
        double width,
        double height,
        double x,
        double y,
        std::unique_ptr<style::IStyle> outlineStyle,
        std::unique_ptr<style::IStyle> fillStyle
    ): Shape(std::move(outlineStyle), std::move(fillStyle)),
       m_x(x),
       m_y(y),
       m_width(width),
       m_height(height)
    {
    }

    void DrawImpl(ICanvas &canvas) const override
    {
        const style::IStyle &outlineStyle = GetOutlineStyle();
        const style::IStyle &fillStyle = GetFillStyle();
        if (fillStyle.IsEnabled().value())
        {
            canvas.SetFillColor(fillStyle.GetColor().value());
            canvas.FillPolygon({
                {m_x, m_y}, {m_x + m_width, m_y}, {m_x + m_width, m_y + m_height}, {m_x, m_y + m_height}
            });
        }
        if (outlineStyle.IsEnabled().value())
        {
            canvas.SetLineColor(outlineStyle.GetColor().value());
            canvas.DrawLine({m_x, m_y}, {m_x + m_width, m_y});
            canvas.DrawLine({m_x + m_width, m_y}, {m_x + m_width, m_y + m_height});
            canvas.DrawLine({m_x + m_width, m_y + m_height}, {m_x, m_y + m_height});
            canvas.DrawLine({m_x, m_y + m_height}, {m_x, m_y});
        }
    }

private:
    double m_x, m_y, m_width, m_height;
};
}
#endif //RECTANGLE_H
