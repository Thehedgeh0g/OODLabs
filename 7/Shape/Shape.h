//
// Created by thehedgeh0g on 11.11.24.
//
#ifndef SHAPE_H
#define SHAPE_H
#include "IShape.h"
#include "../Style/Style.h"

namespace shapes
{
class Shape : public IShape
{
public:
    Shape(
        std::unique_ptr<style::IStyle> outlineStyle,
        std::unique_ptr<style::IStyle> fillStyle
    ) : m_outlineStyle(std::move(outlineStyle)),
        m_fillStyle(std::move(fillStyle))
    {
    }

    style::IStyle &GetOutlineStyle() override
    {
        return *m_outlineStyle;
    }

    const style::IStyle &GetOutlineStyle() const override
    {
        return *m_outlineStyle;
    }

    style::IStyle &GetFillStyle() override
    {
        return *m_fillStyle;
    }

    const style::IStyle &GetFillStyle() const override
    {
        return *m_fillStyle;
    }

    void Draw(std::shared_ptr<ICanvas> canvas) override
    {
        DrawImpl(*canvas);
    }

protected:

    virtual void DrawImpl(ICanvas& canvas) const = 0;

private:
    std::unique_ptr<style::IStyle> m_outlineStyle;
    std::unique_ptr<style::IStyle> m_fillStyle;
};
}
#endif //SHAPE_H
