//
// Created by flipd on 25.12.2024.
//

#ifndef VWINDOW_H
#define VWINDOW_H
#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "VMenu.h"
#include "VShape.h"
#include "../../Common/CommonStructs.h"
#include "../ShapeStrategies/Circle.h"
#include "../ShapeStrategies/Rectangle.h"
#include "../ShapeStrategies/Triangle.h"

namespace view {
    class VWindow {
    public:
        explicit VWindow(std::unique_ptr<ICanvas> &canvas): m_canvas(canvas) {
        };

        ~VWindow() = default;

        void Draw() {
            m_menu->Draw(m_canvas);
            for (auto &shape: m_shapes) {
                shape.second->Draw(m_canvas);
            }
        }

        void AddShape(const std::string &shapeId, const RectD &frame, uint32_t color, const ShapeType &shapeType) {
            std::unique_ptr<IFigure> newFigure = nullptr;
            switch (shapeType) {
                case ShapeType::Circle: {
                    std::cout << "here1" << std::endl;
                    newFigure = std::make_unique<Circle>(frame);
                    break;
                }
                case ShapeType::Triangle: {
                    std::cout << "here2" << std::endl;
                    newFigure = std::make_unique<Triangle>(frame);
                    break;
                }
                case ShapeType::Rectangle: {
                    std::cout << "here3" << std::endl;
                    newFigure = std::make_unique<Rectangle>(frame);
                    break;
                }
                default: { throw std::invalid_argument("Invalid shape type"); }
            }
            std::cout << "here4" << std::endl;
            auto newShape = std::make_unique<VShape>(shapeId, color, std::move(newFigure));
            m_shapes.insert({shapeId, std::move(newShape)});
        }

        void DeleteShape(const std::string &shapeId) {
            auto it = m_shapes.find(shapeId);
            if (it != m_shapes.end()) {
                m_shapes.erase(it);
            }
        }

        void ModifyShape(const std::string &shapeId, uint32_t color, const RectD &frame) {
            auto it = m_shapes.find(shapeId);
            if (it != m_shapes.end()) {
                it->second->SetColor(color);
                it->second->GetFigure().UpdateFrame(frame);
            }
        }

        std::string DetermineViewComponentByPoint(const Point &point) {
            for (auto &shape: m_shapes) {
                if (shape.second->GetFigure().PointInFrame(point)) {
                    return shape.first;
                }
            }
            return m_menu->FindButtonNameByPoint(point);
        }

    private:
        std::map<std::string, std::unique_ptr<VShape> > m_shapes;
        std::unique_ptr<VMenu> m_menu = std::make_unique<view::VMenu>(800, 100);
        std::unique_ptr<ICanvas> &m_canvas;
    };
}
#endif //VWINDOW_H
