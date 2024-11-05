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
        canvas.SetLineColor(lineStyle.color);
        canvas.SetFillColor(fillStyle.color);
        canvas.SetLineThickness(lineStyle.thickness);
        canvas.FillPolygon({{x, y}, {x + width, y}, {x + width, y + height}, {x, y + height}});
    }

    const LineStyle& GetLineStyle() const override { return lineStyle; }
    void SetLineStyle(const LineStyle& style) override { lineStyle = style; }
    const FillStyle& GetFillStyle() const override { return fillStyle; }
    void SetFillStyle(const FillStyle& style) override { fillStyle = style; }

private:
    LineStyle lineStyle;
    FillStyle fillStyle;
    double x, y, width, height;
};
#endif //RECTANGLE_H
