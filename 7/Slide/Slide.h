//
// Created by flipd on 05.11.2024.
//

#ifndef SLIDE_H
#define SLIDE_H
#include <map>
#include <memory>

#include "../Shape/Group.h"
#include "./../Shape/IShape.h"

class Slide {

public:
    void AddShape(std::unique_ptr<shapes::IShape> shape) {
        m_shapes.push_back(std::move(shape));
    }

    void AddShapes(std::vector<std::unique_ptr<shapes::Group>> group) {
        for (auto& shape : group)
        {
            m_shapes.push_back(std::move(shape));
        }
    }

    void Draw(const std::shared_ptr<ICanvas>& canvas) const {
        for (const auto& shape : m_shapes) {
            shape->Draw(canvas);
        }
    }

    ~Slide()
    {
        m_shapes.clear();
    }
private:
    std::vector<std::unique_ptr<shapes::IShape>> m_shapes;
};

#endif //SLIDE_H
