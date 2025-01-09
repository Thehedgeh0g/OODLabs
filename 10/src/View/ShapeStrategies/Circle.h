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

        void Draw(uint32_t color, std::unique_ptr<view::ICanvas> &canvas, bool drawFrame) override {
            canvas->SetColor(color);
            canvas->MoveTo(m_frame.point.x + m_frame.width / 2, m_frame.point.y - m_frame.height / 2);
            canvas->DrawEllipse(m_frame.point.x + m_frame.width / 2, m_frame.point.y - m_frame.height / 2,
                                m_frame.width / 2, 0);


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
            Point center = { m_frame.point.x + m_frame.width / 2,
                             m_frame.point.y + m_frame.height / 2 };
            return (pow(point.x - center.x, 2) / pow(m_frame.width / 2, 2) +
                                  pow(point.y - center.y, 2) / pow(m_frame.height / 2, 2)) <= 1;
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
