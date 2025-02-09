//
// Created by flipd on 24.12.2024.
//

#ifndef SHAPESELECTION_H
#define SHAPESELECTION_H
#include <functional>
#include <memory>
#include "./../../Domain/Shape.h"

class ShapeSelection {
public:
    [[nodiscard]] std::map<std::string, std::shared_ptr<Shape> > GetSelectedShapes() const {
        return m_selectedShapes;
    }

    void SetSelectedShape(const std::shared_ptr<Shape> &shape) {
        m_selectionAdded(shape->GetId());
        m_selectedShapes.insert({shape->GetId(), shape});
    }

    void RemoveSelectedShape(const std::string &shapeId) {
        m_selectionAdded(shapeId);
        m_selectedShapes.erase(shapeId);
    }

    void ClearSelectedShapes() {
        for (const auto &pair : m_selectedShapes) {
            m_selectionAdded(pair.first);
        }
        m_selectedShapes.clear();
    }

    bool IsSelectedShape(const std::string &shapeId) const {
        return m_selectedShapes.find(shapeId) != m_selectedShapes.end();
    }

    boost::signals2::scoped_connection DoOnSelectionChanged(const std::function<void(const std::string&)> &handler) {
        return m_selectionAdded.connect(handler);
    }

private:
    std::map<std::string, std::shared_ptr<Shape> > m_selectedShapes;
    boost::signals2::signal<void(const std::string&)> m_selectionAdded;
};

#endif //SHAPESELECTION_H
