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

    ~Group() = default;

    RectD GetFrame() const override
    {
        if (m_shapes.empty())
        {
            throw std::invalid_argument("Group does not have any shapes");
        }

        double left = std::numeric_limits<double>::max();
        double top = std::numeric_limits<double>::max();
        double right = std::numeric_limits<double>::lowest();
        double bottom = std::numeric_limits<double>::lowest();

        for (const auto &pair: m_shapes)
        {
            RectD frame = pair.second->GetFrame();
            left = std::min(left, frame.left);
            top = std::min(top, frame.top);
            right = std::max(right, frame.left + frame.width);
            bottom = std::max(bottom, frame.top + frame.height);
        }

        return {left, top, right - left, bottom - top};
    }

    void SetFrame(const RectD &rect) override
    {
        auto [left, top, width, height] = GetFrame();
        const double scaleX = rect.width / width;
        const double scaleY = rect.height / height;

        for (const auto &pair: m_shapes)
        {
            const RectD shapeFrame = pair.second->GetFrame();
            const double newLeft = rect.left + (shapeFrame.left - left) * scaleX;
            const double newTop = rect.top + (shapeFrame.top - top) * scaleY;
            const double newWidth = shapeFrame.width * scaleX;
            const double newHeight = shapeFrame.height * scaleY;
            pair.second->SetFrame({newLeft, newTop, newWidth, newHeight});
        }
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
        for (auto it = m_shapes.begin(); it != m_shapes.end(); ++it)
        {
            it->second->Draw(canvas);
        }
    }

    size_t GetShapesCount() const override
    {
        return m_shapes.size();
    }

    void InsertShape(std::unique_ptr<IShape> shape, size_t position = std::numeric_limits<size_t>::max()) override
    {
        m_shapes.emplace(position, std::move(shape));
        m_fillStyle->InsertStyle(m_shapes[position]->GetFillStyle(), position);
        m_outlineStyle->InsertStyle(m_shapes[position]->GetOutlineStyle(), position);
    }


    const std::unique_ptr<IShape>& GetShapeAtIndex(size_t index)  override
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
    std::map<size_t, std::unique_ptr<IShape>> m_shapes;
    std::unique_ptr<style::IGroupStyle> m_outlineStyle = std::make_unique<style::GroupStyle>();
    std::unique_ptr<style::IGroupStyle> m_fillStyle = std::make_unique<style::GroupStyle>();
};
}
#endif //GROUP_H
