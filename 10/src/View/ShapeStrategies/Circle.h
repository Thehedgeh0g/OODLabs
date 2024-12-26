//
// Created by flipd on 25.12.2024.
//

#ifndef CIRCLE_H
#define CIRCLE_H
#include "IFigure.h"
#include "./../../Common/CommonStructs.h"

namespace view {
    class Circle : public IFigure {
    public:
        explicit Circle(const RectD &frame): m_frame(frame) {
        };

        ~Circle() override = default;

        void Draw(uint32_t color, std::unique_ptr<view::ICanvas> &canvas) override {
            canvas->SetColor(color);
            canvas->MoveTo(m_frame.point.x + m_frame.width / 2, m_frame.point.y - m_frame.height / 2);
            canvas->DrawEllipse(m_frame.point.x + m_frame.width / 2, m_frame.point.y - m_frame.height / 2,
                                m_frame.width / 2, 0);
        }

        void UpdateFrame(const RectD frame) override {
            m_frame = frame;
        }

        bool PointInFrame(Point point) override {
            return point.x >= m_frame.point.x && point.x <= m_frame.point.x + m_frame.width && point.y >= m_frame.point.
                   y && point.y <= m_frame.point.y + m_frame.height;
        }

        [[nodiscard]] std::string GetTypeAsString() override {
            return "circle";
        }

        [[nodiscard]] std::string GetFigureDataAsString() override {
            return std::to_string(m_frame.point.x + m_frame.width / 2) + " " +
                   std::to_string(m_frame.point.y + m_frame.height / 2) + " " +
                   std::to_string(m_frame.width / 2);
        }

    private:
        RectD m_frame;
    };
}
#endif //CIRCLE_H
