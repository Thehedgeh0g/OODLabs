//
// Created by thehedgeh0g on 30.10.24.
//

#ifndef MODERNGRAPHICSCANVASCLASSADAPTER_H
#define MODERNGRAPHICSCANVASCLASSADAPTER_H
#include "./../modern_graphics_lib/modern_graphics_lib.h"
#include "./../graphics_lib/graphics_lib.h"
using namespace modern_graphics_lib;
using namespace graphics_lib;

namespace app
{
    class ModernGraphicsCanvasClassAdapter : public ICanvas,
                                             public CModernGraphicsRenderer
    {
    public:
        explicit ModernGraphicsCanvasClassAdapter(std::ostream &strm) : CModernGraphicsRenderer(strm),
                                                                        m_start(0, 0),
                                                                        m_color(0, 0, 0, 0)
        {
        }

        void SetColor(uint32_t rgbColor) override
        {
            float a = ((rgbColor >> 24) & 0xFF) / 255.0f;
            float r = ((rgbColor >> 16) & 0xFF) / 255.0f;
            float g = ((rgbColor >> 8) & 0xFF) / 255.0f;
            float b = (rgbColor & 0xFF) / 255.0f;

            m_color = {r, g, b, a};
        }

        void MoveTo(int x, int y) override
        {
            m_start = {x, y};
        }

        void LineTo(int x, int y) override
        {
            CPoint end(x, y);

            DrawLine(m_start, end, m_color);

            m_start = end;
        }

    private:
        CRGBAColor m_color;
        CPoint m_start;
    };
}

#endif //MODERNGRAPHICSCANVASCLASSADAPTER_H
