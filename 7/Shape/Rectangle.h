//
// Created by flipd on 05.11.2024.
//

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"
#include "./../Canvas/ICanvas.h"
#include "./../Style/LineStyle.h"
#include "./../Style/FillStyle.h"


class Rectangle : public Shape {

public:
    Rectangle(double x, double y, double width, double height)
        : x(x), y(y), width(width), height(height) {}

    void Draw(ICanvas& canvas) const override {
        if (m_fillStyle.isEnabled)
        {
            canvas.SetFillColor(m_fillStyle.color);
            canvas.FillPolygon({{x, y}, {x + width, y}, {x + width, y + height}, {x, y + height}});
        }
        if (m_lineStyle.isEnabled)
        {
            canvas.SetLineColor(m_lineStyle.color);
            canvas.SetLineThickness(m_lineStyle.thickness);
            canvas.DrawLine({x, y}, {x + width, y});
            canvas.DrawLine({x + width, y}, {x + width, y + height});
            canvas.DrawLine({x + width, y + height}, {x, y + height});
            canvas.DrawLine({x, y + height}, {x, y});
        }
    }

    const LineStyle& GetLineStyle() const override { return m_lineStyle; }
    void SetLineStyle(const LineStyle& style) override { m_lineStyle = style; }
    const FillStyle& GetFillStyle() const override { return m_fillStyle; }
    void SetFillStyle(const FillStyle& style) override { m_fillStyle = style; }

private:
    LineStyle m_lineStyle;
    FillStyle m_fillStyle;
    double x, y, width, height;
};
#endif //RECTANGLE_H
