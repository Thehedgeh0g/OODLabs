//
// Created by flipd on 05.11.2024.
//

#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "Shape.h"
#include "./../Canvas/ICanvas.h"
#include "./../Style/LineStyle.h"
#include "./../Style/FillStyle.h"

class Ellipse : public Shape {

public:
    Ellipse(double x, double y, double radiusX, double radiusY)
        : x(x), y(y), radiusX(radiusX), radiusY(radiusY) {}

    void Draw(ICanvas& canvas) const override {
        canvas.SetLineColor(lineStyle.color);
        canvas.SetFillColor(fillStyle.color);
        canvas.SetLineThickness(lineStyle.thickness);
        canvas.FillEllipse(x, y, radiusX * 2, radiusY * 2);
    }

    const LineStyle& GetLineStyle() const override { return lineStyle; }
    void SetLineStyle(const LineStyle& style) override { lineStyle = style; }
    const FillStyle& GetFillStyle() const override { return fillStyle; }
    void SetFillStyle(const FillStyle& style) override { fillStyle = style; }

private:
    LineStyle lineStyle;
    FillStyle fillStyle;
    double x, y, radiusX, radiusY;
};


#endif //ELLIPSE_H
