//
// Created by flipd on 05.11.2024.
//

#ifndef GROUP_H
#define GROUP_H

#include <memory>

#include "IShape.h"
#include "./../Canvas/ICanvas.h"
#include "./../Style/LineStyle.h"
#include "./../Style/FillStyle.h"

class Group : public IShape {

public:
    void AddShape(const std::shared_ptr<IShape>& shape) {
        shapes.push_back(shape);
    }

    void Draw(ICanvas& canvas) const override {
        for (const auto& shape : shapes) {
            shape->Draw(canvas);
        }
    }



    const LineStyle& GetLineStyle() const override {
        if (shapes.empty()) {
            throw std::runtime_error("No shapes in group");
        }
        const LineStyle* commonStyle = nullptr;
        for (const auto& shape : shapes) {
            const LineStyle& style = shape->GetLineStyle();
            if (!commonStyle) {
                commonStyle = &style;
            } else if (commonStyle != &style) {
                return LineStyle();
            }
        }
        return *commonStyle;
    }

    void SetLineStyle(const LineStyle& style) override {
        for (auto& shape : shapes) {
            shape->SetLineStyle(style);
        }
    }

    const FillStyle& GetFillStyle() const override {
        if (shapes.empty()) {
            throw std::runtime_error("No shapes in group");
        }
        const FillStyle* commonStyle = nullptr;
        for (const auto& shape : shapes) {
            const FillStyle& style = shape->GetFillStyle();
            if (!commonStyle) {
                commonStyle = &style;
            } else if (commonStyle != &style) {
                return FillStyle();
            }
        }
        return *commonStyle;
    }

    void SetFillStyle(const FillStyle& style) override {
        for (auto& shape : shapes) {
            shape->SetFillStyle(style);
        }
    }


private:
    std::vector<std::shared_ptr<IShape>> shapes;
};

#endif //GROUP_H
