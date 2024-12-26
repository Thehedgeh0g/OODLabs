//
// Created by flipd on 25.12.2024.
//

#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "IFigure.h"
#include "./../../Common/CommonStructs.h"

namespace view {
    class Rectangle : public IFigure {
    public:
        explicit Rectangle(const RectD& frame)
            : m_frame(frame) {
        }

        ~Rectangle() override = default;

        void Draw(uint32_t color, std::unique_ptr<view::ICanvas> &canvas) override {
            canvas->MoveTo(m_frame.point.x, m_frame.point.y);
            canvas->SetColor(color);
            canvas->LineTo(m_frame.point.x + m_frame.width, m_frame.point.y);
            canvas->LineTo(m_frame.point.x + m_frame.width, m_frame.point.y +  m_frame.height);
            canvas->LineTo(m_frame.point.x, m_frame.point.y +  m_frame.height);
            canvas->LineTo(m_frame.point.x, m_frame.point.y);
        }

        void UpdateFrame(const RectD frame) override {
            m_frame = frame;
        }

        bool PointInFrame(Point point) override {
            return point.x >= m_frame.point.x && point.x <= m_frame.point.x + m_frame.width && point.y >= m_frame.point.y && point.y <= m_frame.point.y + m_frame.height;
        }

        [[nodiscard]] std::string GetTypeAsString() override {
            return "rectangle";
        }

        [[nodiscard]] std::string GetFigureDataAsString() override {
            return std::to_string(m_frame.point.x).append(" ")
                    .append(std::to_string(m_frame.point.y)).append(" ")
                    .append(std::to_string(m_frame.width)).append(" ")
                    .append(std::to_string(m_frame.height));
        }

    private:
        RectD m_frame;
    };
}
#endif //RECTANGLE_H
