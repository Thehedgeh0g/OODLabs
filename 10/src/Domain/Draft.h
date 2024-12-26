//
// Created by flipd on 24.12.2024.
//

#ifndef DRAFT_H
#define DRAFT_H
#include <vector>
#include <memory>
#include <algorithm>
#include <map>

#include "Shape.h"

class Draft {
public:
    void AddShape(const std::shared_ptr<Shape>& shape) {
        std::string newId = shape->GetId();
        m_shapes.insert({newId, shape});
        m_shapeCreated(shape->GetFrame(), shape->GetId(), shape->GetColor(), shape->GetType());
    }

    void RemoveShape(const std::string& id) {
        auto shape = m_shapes.find(id);
        if (shape != m_shapes.end()) {
            m_shapes.erase(shape);
        }
    }

    std::shared_ptr<Shape> FindShapeById(const std::string& id) {
        auto shape = m_shapes.find(id);
        if (shape != m_shapes.end()) {
            return shape->second;
        }
        return nullptr;
    }

    [[nodiscard]] const std::map<std::string, std::shared_ptr<Shape>>& GetShapes() const {
        return m_shapes;
    }

    boost::signals2::connection DoOnShapeCreated(
        const std::function<void(
            const RectD & ,
            const std::string &,
            const uint32_t &,
            const ShapeType &
        )> &handler)
    {
        return m_shapeCreated.connect(handler);
    }

    boost::signals2::connection DoOnShapeDeleted(
        const std::function<void(
            const std::string &
        )> &handler)
    {
        return m_shapeDeleted.connect(handler);
    }

private:
    std::map<std::string, std::shared_ptr<Shape>> m_shapes;
    boost::signals2::signal<void(const RectD &, const std::string &, const uint32_t &, const ShapeType &)> m_shapeCreated;
    boost::signals2::signal<void(const std::string &)> m_shapeDeleted;
};
#endif //DRAFT_H
