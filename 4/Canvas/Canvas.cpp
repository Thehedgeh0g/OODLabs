//
// Created by flipd on 16.10.2024.
//

#include "Canvas.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

namespace gfx
{
    void Canvas::SaveToFile()
    {
        stbi_write_png(m_outputPath.c_str(), m_width, m_height, 4, m_pixels.data(), m_width * 4);
    }
}


