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
        const RectD &frame,
        std::unique_ptr<style::IStyle> outlineStyle,
        std::unique_ptr<style::IStyle> fillStyle
    ): Shape(frame, std::move(outlineStyle), std::move(fillStyle))
    {
    }

    void DrawImpl(ICanvas &canvas) const override
    {
        RectD frame = GetFrame().value();
        const style::IStyle &outlineStyle = GetOutlineStyle();
        const style::IStyle &fillStyle = GetFillStyle();
        if (fillStyle.IsEnabled().value())
        {
            canvas.SetFillColor(fillStyle.GetColor().value());
            canvas.FillPolygon({
                {frame.left, frame.top},
                {frame.left + frame.width, frame.top},
                {frame.left + frame.width, frame.top + frame.height},
                {frame.left, frame.top + frame.height},
            });
        }
        if (outlineStyle.IsEnabled().value())
        {
            canvas.SetLineColor(outlineStyle.GetColor().value());
            canvas.DrawLine({frame.left, frame.top}, {frame.left + frame.width, frame.top});
            canvas.DrawLine({frame.left + frame.width, frame.top}, {frame.left + frame.width, frame.top + frame.height});
            canvas.DrawLine({frame.left + frame.width, frame.top + frame.height}, {frame.left, frame.top + frame.height});
            canvas.DrawLine({frame.left, frame.top + frame.height}, {frame.left, frame.top});
        }
    }

private:
    double m_x, m_y, m_width, m_height;
};
}
#endif //RECTANGLE_H
