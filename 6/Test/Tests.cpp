//
// Created by thehedgeh0g on 30.10.24.
//
#include <sstream>
#include <vector>
#include <gtest/gtest.h>

#include "../app/ModernGraphicsCanvasClassAdapter.h"
#include "../shape_drawing_lib/shape_drawing_lib.h"
#include "./../app/ModernGraphicsCanvasAdapter.h"
#include "./../graphics_lib/graphics_lib.h"
#include "./../modern_graphics_lib/modern_graphics_lib.h"

using namespace graphics_lib;
using namespace shape_drawing_lib;
using namespace modern_graphics_lib;

CRGBAColor ConvertColorHEXToRGBAColor(uint32_t rgbColor)
{
    float a = ((rgbColor >> 24) & 0xFF) / 255.0f;
    float r = ((rgbColor >> 16) & 0xFF) / 255.0f;
    float g = ((rgbColor >> 8) & 0xFF) / 255.0f;
    float b = (rgbColor & 0xFF) / 255.0f;

    CRGBAColor color = {r, g, b, a};
    return color;
}

std::string DrawWithoutAdapter(const std::vector<CPoint> &points, uint32_t color)
{
    std::stringstream strm;
    CModernGraphicsRenderer renderer(strm);
    auto rgbaColor = ConvertColorHEXToRGBAColor(color);

    const auto first = points.begin();
    renderer.BeginDraw();

    for (auto it = first; it != points.end(); ++it)
    {
        if (it + 1 != points.end())
        {
            renderer.DrawLine(*it, *(it + 1), rgbaColor);
        }
        else
        {
            renderer.DrawLine(*it, *first, rgbaColor);
        }
    }

    renderer.EndDraw();

    return strm.str();
}

void DrawWithAdapter(CModernGraphicsRenderer &renderer, ICanvas &adapter, const std::vector<CPoint> &points,
                     uint32_t color)
{
    adapter.SetColor(color);
    renderer.BeginDraw();

    auto first = points.begin();
    adapter.MoveTo((*first).x, (*first).y);

    for (auto it = first + 1; it != points.end(); ++it)
    {
        adapter.LineTo((*it).x, (*it).y);
    }

    adapter.LineTo((*first).x, (*first).y);
    renderer.EndDraw();
}

std::string DrawWithObjectAdapter(const std::vector<CPoint> &points, uint32_t color)
{
    std::stringstream strm;
    CModernGraphicsRenderer renderer(strm);
    app::ModernGraphicsCanvasAdapter adapter(renderer);

    DrawWithAdapter(renderer, adapter, points, color);

    return strm.str();
}

std::string DrawShapeWithClassAdapter(const std::vector<CPoint> &points, uint32_t color)
{
    std::stringstream strm;
    app::ModernGraphicsCanvasClassAdapter adapter(strm);

    DrawWithAdapter(adapter, adapter, points, color);

    return strm.str();
}

TEST(ObjectAdapterTest, InterfaceImplementation)
{
    std::stringstream strm;
    CModernGraphicsRenderer renderer(strm);
    app::ModernGraphicsCanvasAdapter adapter(renderer);

    ICanvas *canvas = (&adapter);
    ASSERT_NE(canvas, nullptr);
}

TEST(ObjectAdapterTest, DrawWithObjectAdapter)
{
    auto triangle =
            {
                CPoint(10, 15),
                CPoint(100, 200),
                CPoint(150, 250),
            };

    uint32_t color = 0xFF5733FF;

    const auto originalShape = DrawWithoutAdapter(triangle, color);
    const auto withAdapterShape = DrawWithObjectAdapter(triangle, color);

    EXPECT_EQ(originalShape, withAdapterShape);
}

TEST(ClassAdapterTest, DrawWithClassAdapter)
{
    auto triangle =
    {
        CPoint(10, 15),
        CPoint(100, 200),
        CPoint(150, 250),
    };

    uint32_t color = 0xFF5733FF;

    const auto originalShape = DrawWithoutAdapter(triangle, color);
    const auto withAdapterShape = DrawShapeWithClassAdapter(triangle, color);

    EXPECT_EQ(originalShape, withAdapterShape);
}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
