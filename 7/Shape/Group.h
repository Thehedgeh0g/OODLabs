//
// Created by flipd on 05.11.2024.
//

#ifndef GROUP_H
#define GROUP_H

#include <memory>

#include "Shape.h"
#include "./../Canvas/ICanvas.h"
#include "./../Style/LineStyle.h"
#include "./../Style/FillStyle.h"

class Group : public Shape {

public:
    void AddShape(const std::shared_ptr<Shape>& shape) {
        shapes.push_back(shape);
    }

    void Draw(ICanvas& canvas) const override {
        for (const auto& shape : shapes) {
            shape->Draw(canvas);
        }
    }

    const LineStyle& GetLineStyle() const override {
        // Логика для возврата LineStyle, если одинаков для всех фигур, или undefined
    }

    void SetLineStyle(const LineStyle& style) override {
        for (auto& shape : shapes) {
            shape->SetLineStyle(style);
        }
    }

    const FillStyle& GetFillStyle() const override {
        // Логика для возврата FillStyle, если одинаков для всех фигур, или undefined
    }

    void SetFillStyle(const FillStyle& style) override {
        for (auto& shape : shapes) {
            shape->SetFillStyle(style);
        }
    }


private:
    std::vector<std::shared_ptr<Shape>> shapes;
};

#endif //GROUP_H
