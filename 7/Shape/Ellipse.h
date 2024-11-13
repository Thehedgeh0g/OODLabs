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
        const RectD &frame,
        std::unique_ptr<style::IStyle> outlineStyle,
        std::unique_ptr<style::IStyle> fillStyle
    ): Shape(frame, std::move(outlineStyle), std::move(fillStyle))
    {
    }

    void DrawImpl(ICanvas &canvas) const override
    {
        RectD frame = GetFrame();
        const style::IStyle &outlineStyle = GetOutlineStyle();
        const style::IStyle &fillStyle = GetFillStyle();
        if (outlineStyle.IsEnabled().value())
        {
            canvas.SetLineColor(outlineStyle.GetColor().value());
            canvas.DrawEllipse({frame.left + frame.width / 2, frame.top - frame.height / 2}, frame.width / 2, frame.height/2);
        }
        if (fillStyle.IsEnabled().value())
        {
            canvas.SetFillColor(fillStyle.GetColor().value());
            canvas.FillEllipse({frame.left + frame.width / 2, frame.top - frame.height / 2}, frame.width, frame.height);
        }
    }
};
}
#endif //ELLIPSE_H
