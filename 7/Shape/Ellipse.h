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
        if (m_lineStyle.isEnabled)
        {
            canvas.SetLineColor(m_lineStyle.color);
            canvas.SetLineThickness(m_lineStyle.thickness);
            canvas.DrawEllipse({x, y}, radiusX, radiusY);
        }
        if (m_fillStyle.isEnabled)
        {
            canvas.SetFillColor(m_fillStyle.color);
            canvas.FillEllipse(x, y, radiusX * 2, radiusY * 2);
        }
    }

    const LineStyle& GetLineStyle() const override { return m_lineStyle; }
    void SetLineStyle(const LineStyle& style) override { m_lineStyle = style; }
    const FillStyle& GetFillStyle() const override { return m_fillStyle; }
    void SetFillStyle(const FillStyle& style) override { m_fillStyle = style; }

private:
    LineStyle m_lineStyle;
    FillStyle m_fillStyle;
    double x, y, radiusX, radiusY;
};


#endif //ELLIPSE_H
