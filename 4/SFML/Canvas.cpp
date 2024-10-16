//
// Created by flipd on 16.10.2024.
//

#include "Canvas.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"


void Canvas::SaveToFile(const std::string& filename)
{
    stbi_write_png(filename.c_str(), width, height, 4, pixels.data(), width * 4);
}