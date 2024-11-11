//
// Created by flipd on 05.11.2024.
//

#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "IShape.h"
#include "Shape.h"
#include "./../Canvas/ICanvas.h"

namespace shapes
{
class Ellipse : public Shape
{
public:
    Ellipse(
        Point center,
        double radiusX,
        double radiusY,
        std::unique_ptr<style::IStyle> outlineStyle,
        std::unique_ptr<style::IStyle> fillStyle
    ): Shape(std::move(outlineStyle), std::move(fillStyle)),
       m_center(center),
       m_radiusX(radiusX),
       m_radiusY(radiusY)
    {
    }

    void DrawImpl(ICanvas &canvas) const override
    {
        const style::IStyle &outlineStyle = GetOutlineStyle();
        const style::IStyle &fillStyle = GetFillStyle();
        if (outlineStyle.IsEnabled())
        {
            canvas.SetLineColor(outlineStyle.GetColor().value());
            canvas.DrawEllipse(m_center, m_radiusX, m_radiusY);
        }
        if (fillStyle.IsEnabled())
        {
            canvas.SetFillColor(fillStyle.GetColor().value());
            canvas.FillEllipse(m_center, m_radiusX * 2, m_radiusY * 2);
        }
    }

private:
    Point m_center;
    double m_radiusX, m_radiusY;
};
}
#endif //ELLIPSE_H
