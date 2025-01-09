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
        explicit Triangle(const RectD &m_frame): m_frame(m_frame) {
        }

        ~Triangle() override = default;

        void Draw(uint32_t color, std::unique_ptr<view::ICanvas> &canvas, bool drawFrame) override {
            canvas->SetColor(color);
            canvas->MoveTo(m_frame.point.x + m_frame.width / 2, m_frame.point.y);
            canvas->LineTo(m_frame.point.x, m_frame.point.y + m_frame.height);
            canvas->LineTo(m_frame.point.x + m_frame.width, m_frame.point.y + m_frame.height);
            canvas->LineTo(m_frame.point.x + m_frame.width / 2, m_frame.point.y);

            if (drawFrame) {
                Point leftTop = {m_frame.point.x, m_frame.point.y};
                Point rightBottom = {m_frame.point.x + m_frame.width, m_frame.point.y + m_frame.height};
                Point rightTop = {rightBottom.x, m_frame.point.y};
                Point leftBottom = {m_frame.point.x, rightBottom.y};

                canvas->SetColor(0xFF00FFFF);

                canvas->MoveTo(rightTop.x, rightTop.y);
                canvas->LineTo(rightTop.x, rightTop.y);
                canvas->LineTo(rightBottom.x, rightBottom.y);
                canvas->LineTo(leftBottom.x, leftBottom.y);
                canvas->LineTo(leftTop.x, leftTop.y);
                canvas->LineTo(rightTop.x, rightTop.y);

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
            Point vertex1 = { m_frame.point.x, m_frame.point.y + m_frame.height };
            Point vertex2 = { m_frame.point.x + m_frame.width / 2, m_frame.point.y };
            Point vertex3 = { m_frame.point.x + m_frame.width, m_frame.point.y + m_frame.height };

            auto sign1 = std::copysign(1, (vertex1.x - point.x) * (vertex2.y - vertex1.y) - (vertex2.x - vertex1.x) * (vertex1.y - point.y));
            auto sign2 = std::copysign(1, (vertex2.x - point.x) * (vertex3.y - vertex2.y) - (vertex3.x - vertex2.x) * (vertex2.y - point.y));
            auto sign3 = std::copysign(1, (vertex3.x - point.x) * (vertex1.y - vertex3.y) - (vertex1.x - vertex3.x) * (vertex3.y - point.y));

            return (sign1 == sign2) && (sign2 == sign3);
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
