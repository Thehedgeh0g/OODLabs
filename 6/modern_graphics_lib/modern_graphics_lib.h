//
// Created by thehedgeh0g on 30.10.24.
//

#ifndef MODERN_GRAPHICS_LIB_H
#define MODERN_GRAPHICS_LIB_H
#include <ostream>
#include <boost/format.hpp>

namespace modern_graphics_lib
{
    class CPoint
    {
    public:
        CPoint(int x, int y) : x(x), y(y)
        {
        }

        int x;
        int y;
    };

    class CRGBAColor
    {
    public:
        CRGBAColor(float r, float g, float b, float a): r(r), g(g), b(b), a(a)
        {
        }

        float r, g, b, a;
    };

    class CModernGraphicsRenderer
    {
    public:
        CModernGraphicsRenderer(std::ostream &strm) : m_out(strm)
        {
        }

        ~CModernGraphicsRenderer()
        {
            if (m_drawing)
            {
                EndDraw();
            }
        }

        void BeginDraw()
        {
            if (m_drawing)
            {
                throw std::logic_error("Drawing has already begun");
            }
            m_out << "<draw>\n" << std::endl;
            m_drawing = true;
        }

        void DrawLine(const CPoint &start, const CPoint &end, const CRGBAColor &color)
        {
            if (!m_drawing)
            {
                throw std::logic_error("DrawLine is allowed between BeginDraw()/EndDraw() only");
            }
            m_out << boost::format("  <line fromX=\"%1%\" fromY=\"%2%\" toX=\"%3%\" toY=\"%4%\"/>\n") % start.x % start.
                    y % end.x % end.y << std::endl;
            m_out << boost::format("  <color r=\"%1%\" g=\"%2%\" b=\"%3%\" a=\"%4%\"/>\n") % color.r % color.g % color.b
                    % color.a << std::endl;
        }

        void EndDraw()
        {
            if (!m_drawing)
            {
                throw std::logic_error("Drawing has not been started");
            }
            m_out << "</draw>" << std::endl;
            m_drawing = false;
        }

    private:
        std::ostream &m_out;
        bool m_drawing = false;
    };
}
#endif //MODERN_GRAPHICS_LIB_H
