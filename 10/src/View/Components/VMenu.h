//
// Created by flipd on 25.12.2024.
//

#ifndef VMENU_H
#define VMENU_H
#include <string>
#include <vector>

#include "./../../Common/CommonStructs.h"
#include "./../ICanvas.h"
#include "../../Infrastructure/Events/MouseDownEvent.h"
#include "../../Presentor/IInteractionEvent.h"

namespace view {
    class VMenu {
    public:
        VMenu(double width, double height, std::unique_ptr<Presenter::PShape> &presenter)
            : m_width(width),
              m_height(height),
              m_presenter(presenter) {
            m_buttons = {
                "Triangle",
                "Rectangle",
                "Circle",
            };
        }

        void Draw(std::unique_ptr<ICanvas> &canvas) {
            auto width = m_width / m_buttons.size();

            for (int i = 0; i < m_buttons.size(); i++) {
                ShowButton(
                    canvas,
                    {
                        width * i,
                        0,
                        width,
                        m_height
                    },
                    m_buttons[i]);
            }
        }

        [[nodiscard]] double GetWidth() const {
            return m_width;
        }

        [[nodiscard]] size_t GetCountButtons() const {
            return m_buttons.size();
        }

        void Notify(std::shared_ptr<Presenter::IInteractionEvent> event) {
            if (event->GetInteractionType() == ViewInteractionType::MouseDown) {
                auto mouseDownEvent = std::dynamic_pointer_cast<MouseDownEvent>(event);
                std::string button = FindButtonNameByPoint(mouseDownEvent->GetPosition());
                ShapeType shapeType;
                if (button == "Triangle") {
                    shapeType = ShapeType::Triangle;
                } else if (button == "Rectangle") {
                    shapeType = ShapeType::Rectangle;
                } else if (button == "Circle") {
                    shapeType = ShapeType::Circle;
                } else {
                    return;
                }
                m_presenter->Create(shapeType, {200, 200}, 100, 100, 0x000000FF);
            }
        }

    private:
        [[nodiscard]] std::string FindButtonNameByPoint(const Point point) const {
            std::string result;
            if (point.y < m_height) {
                int i = 1;

                while (point.x > (m_width / 3) * i) {
                    i++;
                }
                result = i <= m_buttons.size() ? m_buttons[i - 1] : result;
            }
            return result;
        }

        static void ShowButton(std::unique_ptr<ICanvas> &canvas, const RectD &frame, const std::string &name) {
            Point leftTop = {frame.point.x, frame.point.y};
            Point rightBottom = {frame.point.x + frame.width, frame.point.y + frame.height};
            Point rightTop = {rightBottom.x, frame.point.y};
            Point leftBottom = {frame.point.x, rightBottom.y};
            canvas->SetColor(0x000000FF);
            canvas->MoveTo(leftTop.x, leftTop.y);
            canvas->LineTo(rightTop.x, rightTop.y);
            canvas->LineTo(rightBottom.x, rightBottom.y);
            canvas->LineTo(leftBottom.x, leftBottom.y);
            canvas->LineTo(leftTop.x, leftTop.y);

            canvas->DrawText(leftTop.y, leftTop.x + 15, 16, name);
        }

        static constexpr int DEFAULT_BUTTON_OFFSET = 10;

        std::vector<std::string> m_buttons;
        double m_width;
        double m_height;
        std::unique_ptr<Presenter::PShape> &m_presenter;
    };
}
#endif //VMENU_H
