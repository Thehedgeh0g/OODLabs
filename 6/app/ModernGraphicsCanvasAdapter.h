//
// Created by thehedgeh0g on 30.10.24.
//

#ifndef MODERNGRAPHICSCANVASADAPTER_H
#define MODERNGRAPHICSCANVASADAPTER_H

#include "./../graphics_lib/graphics_lib.h"
#include "./../modern_graphics_lib/modern_graphics_lib.h"

using namespace graphics_lib;
using namespace modern_graphics_lib;

namespace app
{
    class ModernGraphicsCanvasAdapter : public ICanvas
    {
    public:
        explicit ModernGraphicsCanvasAdapter(CModernGraphicsRenderer &modernRenderer) : m_renderer(modernRenderer),
            m_start(0, 0),
            m_color(0, 0, 0, 0)
        {
        }

        void SetColor(uint32_t rgbColor) override
        {
            float a = ((rgbColor >> 24) & 0xFF) / 255.0f; // Альфа-канал
            float r = ((rgbColor >> 16) & 0xFF) / 255.0f; // Красный
            float g = ((rgbColor >> 8) & 0xFF) / 255.0f; // Зеленый
            float b = (rgbColor & 0xFF) / 255.0f; // Синий

            m_color = {r, g, b, a};
        }

        void MoveTo(int x, int y) override
        {
            m_start = {x, y};
        }

        void LineTo(int x, int y) override
        {
            const CPoint end(x, y);

            m_renderer.DrawLine(m_start, end, m_color);

            m_start = end;
        }

    private:
        CRGBAColor m_color;
        CPoint m_start;
        CModernGraphicsRenderer &m_renderer;
    };
} // app

#endif //MODERNGRAPHICSCANVASADAPTER_H
