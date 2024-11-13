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
        const RectD &frame,
        std::unique_ptr<style::IStyle> outlineStyle,
        std::unique_ptr<style::IStyle> fillStyle
    ): Shape(frame, std::move(outlineStyle), std::move(fillStyle))
    {
    }

    ~Triangle() override = default;

    void DrawImpl(ICanvas &canvas) const override
    {
        RectD frame = GetFrame();
        Point p1(frame.left + frame.width / 2, frame.top),
                p2(frame.left, frame.top + frame.height),
                p3(frame.left + frame.width, frame.top + frame.height);
        const style::IStyle &outlineStyle = GetOutlineStyle();
        const style::IStyle &fillStyle = GetFillStyle();
        if (fillStyle.IsEnabled().value())
        {
            canvas.SetFillColor(fillStyle.GetColor().value());
            canvas.FillPolygon({p1, p2, p3});
        }
        if (outlineStyle.IsEnabled().value())
        {
            canvas.SetLineColor(outlineStyle.GetColor().value());
            canvas.DrawLine(p1, p2);
            canvas.DrawLine(p2, p3);
            canvas.DrawLine(p3, p1);
        }
    }
};
}
#endif //TRIANGLE_H
