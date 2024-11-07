//
// Created by flipd on 05.11.2024.
//

#ifndef SLIDE_H
#define SLIDE_H
#include <map>
#include <memory>
#include "./../Shape/IShape.h"

class Slide {

public:
    void AddShape(const std::shared_ptr<IShape>& shape) {
        shapes.push_back(shape);
    }

    void Draw(ICanvas& canvas) const {
        for (const auto& shape : shapes) {
            shape->Draw(canvas);
        }
    }
private:
    std::vector<std::shared_ptr<IShape>> shapes;
};

#endif //SLIDE_H
