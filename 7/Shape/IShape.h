//
// Created by flipd on 05.11.2024.
//

#ifndef SHAPE_H
#define SHAPE_H

#include "./../Canvas/ICanvas.h"
#include "./../Style/LineStyle.h"
#include "./../Style/FillStyle.h"

class IShape {
public:
    virtual void Draw(ICanvas &canvas) const = 0;

    virtual const LineStyle &GetLineStyle() const = 0;

    virtual void SetLineStyle(const LineStyle &style) = 0;

    virtual const FillStyle &GetFillStyle() const = 0;

    virtual void SetFillStyle(const FillStyle &style) = 0;

    virtual ~IShape() = default;
};

#endif //SHAPE_H
