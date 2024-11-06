//
// Created by thehedgeh0g on 05.11.24.
//

#ifndef CAIROCANVAS_H
#define CAIROCANVAS_H
#include <iostream>
#include <math.h>
#include <sstream>
#include <stdexcept>

#include "ICanvas.h"
#include <cairo/cairo.h>

#include <utility>

class CairoCanvas final : public ICanvas
{
public:
    CairoCanvas(const int width, const int height, std::string output): m_outputPath(std::move(output)), m_width(width),
                                                                        m_height(height)
    {
        m_surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
        m_cairo = cairo_create(m_surface);
        cairo_set_source_rgb(m_cairo, 1.0, 1.0, 1.0);
        cairo_paint(m_cairo);
    };

    ~CairoCanvas()
    {
        cairo_surface_write_to_png(m_surface, m_outputPath.c_str());
        cairo_destroy(m_cairo);
    }

    void SetFillColor(const std::string &color) override
    {
        m_fillColor = ParseColor(color);
    }

    void SetLineColor(const std::string &color) override
    {
        m_lineColor = ParseColor(color);
    }

    void SetLineThickness(const double thickness) override
    {
        m_line_thickness = thickness;
    }

    void DrawLine(const Point start, const Point end) override
    {
        cairo_set_line_width(m_cairo, m_line_thickness);
        cairo_set_source_rgba(m_cairo, m_lineColor.r, m_lineColor.g, m_lineColor.b, m_lineColor.a);
        cairo_move_to(m_cairo, start.x, start.y);
        cairo_line_to(m_cairo, end.x, end.y);
        cairo_stroke(m_cairo);
    }

    void DrawEllipse(Point center, double hx, double hy) override
    {
        cairo_set_line_width(m_cairo, m_line_thickness);
        cairo_save(m_cairo);
        cairo_set_source_rgba(m_cairo, m_lineColor.r, m_lineColor.g, m_lineColor.b, m_lineColor.a);
        cairo_translate(m_cairo, center.x, center.y);
        cairo_scale(m_cairo, hx, hy);
        cairo_arc(m_cairo, 0, 0, 1, 0, 2 * M_PI);
        cairo_restore(m_cairo);
        cairo_stroke(m_cairo);
    }

    void FillEllipse(double x, double y, double width, double height) override
    {
        cairo_set_source_rgba(m_cairo, m_fillColor.r, m_fillColor.g, m_fillColor.b, m_fillColor.a);
        cairo_save(m_cairo);
        cairo_translate(m_cairo, x, y);
        cairo_scale(m_cairo, width / 2.0, height / 2.0); // Преобразуем координаты
        cairo_arc(m_cairo, 0, 0, 1, 0, 2 * M_PI); // Рисуем круг
        cairo_fill(m_cairo);
        cairo_restore(m_cairo);
    }

    void FillPolygon(const std::vector<std::pair<double, double> > &points) override
    {
        cairo_set_source_rgba(m_cairo, m_fillColor.r, m_fillColor.g, m_fillColor.b, m_fillColor.a);
        if (points.empty())
            return;

        cairo_move_to(m_cairo, points[0].first, points[0].second);
        for (const auto &point: points)
        {
            cairo_line_to(m_cairo, point.first, point.second);
        }
        cairo_close_path(m_cairo);
        cairo_fill(m_cairo);
    }

private:
    struct RGBAColor
    {
        uint8_t r, g, b, a;
    };

    static RGBAColor ParseColor(const std::string &color)
    {
        RGBAColor RGBAColor{};

        if (color[0] == '#') {
            std::stringstream ss;
            ss << std::hex << color.substr(1);

            uint32_t intValue;
            ss >> intValue;

            // Извлекаем значения цвета
            RGBAColor.r = (intValue >> 24) & 0xFF;
            RGBAColor.g = (intValue >> 16) & 0xFF;
            RGBAColor.b = (intValue >> 8) & 0xFF;
            RGBAColor.a = intValue & 0xFF;
        } else {
            throw std::invalid_argument("Invalid hex format");
        }

        return RGBAColor;
    }

    cairo_surface_t *m_surface = nullptr;
    cairo_t *m_cairo = nullptr;
    RGBAColor m_fillColor{};
    RGBAColor m_lineColor{};
    double m_line_thickness{};
    std::string m_outputPath;
    int m_width;
    int m_height;
};
#endif //CAIROCANVAS_H
