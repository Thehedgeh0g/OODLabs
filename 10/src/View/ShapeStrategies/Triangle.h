//
// Created by flipd on 25.12.2024.
//

#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "IFigure.h"
#include "./../../Common/CommonStructs.h"

namespace view {
    class Triangle : public IFigure {
    public:
        explicit Triangle(const RectD &frame): m_frame(frame) {
        }

        ~Triangle() override = default;

        void Draw(uint32_t color, std::unique_ptr<view::ICanvas> &canvas) override {
            canvas->SetColor(color);
            canvas->MoveTo(m_frame.point.x + m_frame.width / 2, m_frame.point.y);
            canvas->LineTo(m_frame.point.x, m_frame.point.y + m_frame.height);
            canvas->LineTo(m_frame.point.x + m_frame.width, m_frame.point.y + m_frame.height);
            canvas->LineTo(m_frame.point.x + m_frame.width / 2, m_frame.point.y);
        }

        void UpdateFrame(const RectD frame) override {
            m_frame = frame;
        }

        bool PointInFrame(Point point) override {
            return point.x >= m_frame.point.x && point.x <= m_frame.point.x + m_frame.width && point.y >= m_frame.point.
                   y && point.y <= m_frame.point.y + m_frame.height;
        }

        [[nodiscard]] std::string GetTypeAsString() override {
            return "triangle";
        }

        [[nodiscard]] std::string GetFigureDataAsString() override {
            return std::to_string(m_frame.point.x + m_frame.width / 2).append(" ")
                    .append(std::to_string(m_frame.point.y)).append(" ")
                    .append(std::to_string(m_frame.point.x)).append(" ")
                    .append(std::to_string(m_frame.point.y - m_frame.height)).append(" ")
                    .append(std::to_string(m_frame.point.x + m_frame.width)).append(" ")
                    .append(std::to_string(m_frame.point.y - m_frame.height));
        }

    private:
        RectD m_frame;
    };
}
#endif //TRIANGLE_H
