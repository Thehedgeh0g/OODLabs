//
// Created by flipd on 24.12.2024.
//

#ifndef SHAPESELECTION_H
#define SHAPESELECTION_H
#include <functional>
#include <memory>
#include <vector>
#include <boost/signals2.hpp>
#include "./../../Domain/Shape.h"

class ShapeSelection {
public:
    [[nodiscard]] std::map<std::string, std::shared_ptr<Shape> > GetSelectedShapes() const {
        return m_selectedShapes;
    }


    void SetSelectedShape(const std::shared_ptr<Shape> &shape) {
        m_selectedShapes.insert({shape->GetId(), shape});
    }

    void RemoveSelectedShape(const std::string &shapeId) {
        m_selectedShapes.erase(shapeId);
    }

    bool IsSelectedShape(const std::string &shapeId) const {
        return m_selectedShapes.find(shapeId) != m_selectedShapes.end();
    }

private:
    std::map<std::string, std::shared_ptr<Shape> > m_selectedShapes;
};

#endif //SHAPESELECTION_H
