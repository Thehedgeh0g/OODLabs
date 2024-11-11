//
// Created by flipd on 05.11.2024.
//

#ifndef GROUP_H
#define GROUP_H

#include <memory>

#include "IGroup.h"
#include "IShape.h"
#include "./../Canvas/ICanvas.h"
#include "./../Style/IGroupStyle.h"
#include "./../Style/GroupStyle.h"

namespace shapes
{
class Group : public IShape, public IGroup
{
public:
    inline static const std::string typeStart = "group";
    inline static const std::string typeEnd = "endgroup";

    Group() = default;

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
        for (size_t i = 0; i < GetShapesCount(); ++i)
        {
            auto shape = GetShapeAtIndex(i);
            if (shape)
            {
                shape->Draw(canvas);
            }
        }
    }

    size_t GetShapesCount() const override
    {
        return m_shapes.size();
    }

    void InsertShape(const std::shared_ptr<IShape> &shape,
                     size_t position = std::numeric_limits<size_t>::max()) override
    {
        m_shapes.insert({position, shape});
        m_fillStyle->InsertStyle(shape->GetFillStyle(), position);
        m_outlineStyle->InsertStyle(shape->GetOutlineStyle(), position);
    }

    std::shared_ptr<IShape> GetShapeAtIndex(size_t index) const override
    {
        return m_shapes.at(index);
    }

    void RemoveShapeAtIndex(size_t index) override
    {
        auto it = m_shapes.find(index);
        if (it != m_shapes.end())
        {
            m_shapes.erase(it);
            m_fillStyle->RemoveStyleAtIndex(index);
            m_outlineStyle->RemoveStyleAtIndex(index);
        }
    }

private:
    std::unordered_map<size_t, std::shared_ptr<IShape> > m_shapes;
    std::unique_ptr<style::IGroupStyle> m_outlineStyle = std::make_unique<style::GroupStyle>();
    std::unique_ptr<style::IGroupStyle> m_fillStyle = std::make_unique<style::GroupStyle>();
};
}
#endif //GROUP_H
