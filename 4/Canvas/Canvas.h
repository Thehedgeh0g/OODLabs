//
// Created by thehedgeh0g on 16.10.24.
//

#ifndef CANVAS_H
#define CANVAS_H
#include <cmath>

#include <SFML/Graphics.hpp>
#include <utility>

#include "./../Draft/ICanvas.h"

namespace gfx
{
    class Canvas : public draft::ICanvas
    {
    public:
        explicit Canvas(
            const int w,
            const int h,
            std::string outputPath
        ) : m_width(w),
            m_height(h),
            m_currentColor({255, 255, 255, 255}),
            m_outputPath(std::move(outputPath))
        {
            m_pixels.resize(m_width * m_height * 4, 255);
        }

        void SetColor(shape::Color color) override
        {
            m_currentColor = ColorToRGBAColor(color);
        }

        void DrawLine(shape::Point start, shape::Point end) override
        {
            int ix1 = static_cast<int>(std::round(start.x));
            int iy1 = static_cast<int>(std::round(start.y));
            int ix2 = static_cast<int>(std::round(end.x));
            int iy2 = static_cast<int>(std::round(end.y));

            int dx = std::abs(ix2 - ix1), dy = std::abs(iy2 - iy1);
            int sx = (ix1 < ix2) ? 1 : -1;
            int sy = (iy1 < iy2) ? 1 : -1;
            int err = dx - dy;

            while (true)
            {
                PutPixel(ix1, iy1);
                if (ix1 == ix2 && iy1 == iy2)
                    break;
                int e2 = 2 * err;
                if (e2 > -dy)
                {
                    err -= dy;
                    ix1 += sx;
                }
                if (e2 < dx)
                {
                    err += dx;
                    iy1 += sy;
                }
            }
            SaveToFile();
        }

        void DrawEllipse(shape::Point center, double hx, double hy) override
        {
            int segments = 100;
            double angleStep = 2 * M_PI / segments;

            double prevX = center.x + hx;
            double prevY = center.y;

            for (int i = 1; i <= segments; ++i)
            {
                double angle = i * angleStep;
                double newX = center.x + hx * cos(angle);
                double newY = center.y + hy * sin(angle);
                DrawLine({prevX, prevY}, {newX, newY});
                prevX = newX;
                prevY = newY;
            }
        }

    private:
        struct RGBAColor;

        void SaveToFile();

        void PutPixel(int x, int y)
        {
            if (x >= 0 && x < m_width && y >= 0 && y < m_height)
            {
                int index = 4 * (y * m_width + x);
                m_pixels[index] = m_currentColor.r;
                m_pixels[index + 1] = m_currentColor.g;
                m_pixels[index + 2] = m_currentColor.b;
                m_pixels[index + 3] = m_currentColor.a;
            }
        }

        static RGBAColor ColorToRGBAColor(shape::Color color)
        {
            uint32_t hexedColor = convertColorToHEX(color);
            return RGBAColor(
                static_cast<uint8_t>(hexedColor >> 24) & 0xFF,
                static_cast<uint8_t>(hexedColor >> 16) & 0xFF,
                static_cast<uint8_t>(hexedColor >> 8) & 0xFF,
                static_cast<uint8_t>(hexedColor & 0xFF)
            );
        }

        struct RGBAColor
        {
            uint8_t r, g, b, a;
        };

        int m_width, m_height;
        RGBAColor m_currentColor{};
        std::vector<uint8_t> m_pixels;
        std::string m_outputPath;
    };
}
#endif //CANVAS_H
