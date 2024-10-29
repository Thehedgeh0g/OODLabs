//
// Created by thehedgeh0g on 30.10.24.
//

#ifndef SHAPE_DRAWING_LIB_H
#define SHAPE_DRAWING_LIB_H
#include "../graphics_lib/graphics_lib.h"
using namespace graphics_lib;

namespace shape_drawing_lib
{
    struct Point
    {
        int x;
        int y;
    };

    class ICanvasDrawable
    {
    public:
        virtual void Draw(ICanvas &canvas) const = 0;

        virtual ~ICanvasDrawable() = default;
    };

    class CTriangle : public ICanvasDrawable
    {
    public:
        CTriangle(const Point &p1, const Point &p2, const Point &p3, uint32_t color = 0x000000) : m_p1(p1), m_p2(p2),
            m_p3(p3), m_color(color)
        {
        }

        void Draw(ICanvas &canvas) const override
        {
            canvas.SetColor(m_color);
            canvas.MoveTo(m_p1.x, m_p1.y);
            canvas.LineTo(m_p2.x, m_p2.y);
            canvas.LineTo(m_p3.x, m_p3.y);
            canvas.LineTo(m_p1.x, m_p1.y);
        }

    private:
        Point m_p1, m_p2, m_p3;
        uint32_t m_color{};
    };


    class CRectangle : public ICanvasDrawable
    {
    public:
        CRectangle(const Point &leftTop, int width, int height, uint32_t color = 0x000000) : m_leftTop(leftTop),
            m_width(width), m_height(height), m_color(color)
        {
        }

        void Draw(ICanvas &canvas) const override
        {
            canvas.SetColor(m_color);

            canvas.MoveTo(m_leftTop.x, m_leftTop.y);
            canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y);

            canvas.LineTo(m_leftTop.x, m_leftTop.y - m_height);

            canvas.MoveTo(m_leftTop.x + m_width, m_leftTop.y - m_height);
            canvas.LineTo(m_leftTop.x, m_leftTop.y - m_height);

            canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y);
        }

    private:
        Point m_leftTop;
        int m_width, m_height;
        uint32_t m_color{};
    };

    class CCanvasPainter
    {
    public:
        CCanvasPainter(ICanvas &canvas) : m_canvas(canvas)
        {
        }

        void Draw(const ICanvasDrawable &drawable)
        {
            drawable.Draw(m_canvas);
        }

    private:
        ICanvas &m_canvas;
    };
}
#endif //SHAPE_DRAWING_LIB_H
