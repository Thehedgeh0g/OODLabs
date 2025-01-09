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

        void Draw(uint32_t color, std::unique_ptr<view::ICanvas> &canvas, bool drawFrame) override {
            canvas->MoveTo(m_frame.point.x, m_frame.point.y);
            canvas->SetColor(color);
            canvas->LineTo(m_frame.point.x + m_frame.width, m_frame.point.y);
            canvas->LineTo(m_frame.point.x + m_frame.width, m_frame.point.y +  m_frame.height);
            canvas->LineTo(m_frame.point.x, m_frame.point.y +  m_frame.height);
            canvas->LineTo(m_frame.point.x, m_frame.point.y);

            if (drawFrame) {
                Point rightBottom = {m_frame.point.x + m_frame.width, m_frame.point.y + m_frame.height};

                canvas->SetColor(0xFF00FFFF);

                DrawCorner(canvas, {rightBottom.x - EDIT_SQUARE_SIZE, rightBottom.y - EDIT_SQUARE_SIZE});
            }
        }

        static void DrawCorner(std::unique_ptr<view::ICanvas> &canvas, const Point &leftTop) {
            Point rightTop = {leftTop.x + EDIT_SQUARE_SIZE, leftTop.y};
            Point rightBottom = {leftTop.x + EDIT_SQUARE_SIZE, leftTop.y + EDIT_SQUARE_SIZE};
            Point leftBottom = {leftTop.x, leftTop.y + EDIT_SQUARE_SIZE};

            canvas->SetColor(0xFF00FFFF);

            std::vector<Point> points{leftTop, rightTop, rightBottom, leftBottom};
            canvas->MoveTo(rightTop.x, rightTop.y);

            canvas->LineTo(rightTop.x, rightTop.y);
            canvas->LineTo(rightBottom.x, rightBottom.y);
            canvas->LineTo(leftBottom.x, leftBottom.y);
            canvas->LineTo(leftTop.x, leftTop.y);
            canvas->LineTo(rightTop.x, rightTop.y);
        }

        void UpdateFrame(const RectD frame) override {
            m_frame = frame;
        }

        bool PointInFigure(Point point) override {
            return point.x >= m_frame.point.x && point.x <= m_frame.point.x + m_frame.width && point.y >= m_frame.point.y && point.y <= m_frame.point.y + m_frame.height;
        }

        bool IsPointInFrame(Point point) override {
            return point.x >= m_frame.point.x && point.x <= m_frame.point.x + m_frame.width && point.y >= m_frame.point.
                   y && point.y <= m_frame.point.y + m_frame.height;
        }

        bool IsOnEditSquare(Point point) override {
            Point rightBottom = {m_frame.point.x + m_frame.width, m_frame.point.y + m_frame.height};

            return point.x <= rightBottom.x && point.y <= rightBottom.y &&
                                   point.x >= rightBottom.x - EDIT_SQUARE_SIZE && point.y >= rightBottom.y - EDIT_SQUARE_SIZE;
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
