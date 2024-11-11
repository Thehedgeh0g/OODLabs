//
// Created by flipd on 05.11.2024.
//

#ifndef ISHAPE_H
#define ISHAPE_H

#include "./../Style/Style.h"
#include "./../Canvas/ICanvas.h"

namespace shapes
{
class IShape
{
public:
    virtual const style::IStyle &GetOutlineStyle() const = 0;

    virtual const style::IStyle &GetFillStyle() const = 0;

    virtual style::IStyle &GetOutlineStyle() = 0;

    virtual style::IStyle &GetFillStyle() = 0;

    virtual void Draw(std::shared_ptr<ICanvas> canvas) = 0;

    virtual ~IShape() = default;
};
}
#endif //ISHAPE_H
