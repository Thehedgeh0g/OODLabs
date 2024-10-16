//
// Created by thehedgeh0g on 16.10.24.
//

#ifndef CANVAS_H
#define CANVAS_H
#include <cmath>

#include <SFML/Graphics.hpp>

#include "./../Draft/Color.h"
#include "./../Draft/ICanvas.h"

class Canvas : public ICanvas {
public:
    explicit Canvas(int w, int h) : width(w), height(h), currentColor({255, 255, 255, 255}) {
        pixels.resize(width * height * 4, 255);
    }

    void SetColor(Color color) override {
        currentColor = GetSFMLColor(color);
    }

    void DrawLine(Point start, Point end) override {
        int ix1 = static_cast<int>(std::round(start.x));
        int iy1 = static_cast<int>(std::round(start.y));
        int ix2 = static_cast<int>(std::round(end.x));
        int iy2 = static_cast<int>(std::round(end.y));

        int dx = std::abs(ix2 - ix1), dy = std::abs(iy2 - iy1);
        int sx = (ix1 < ix2) ? 1 : -1;
        int sy = (iy1 < iy2) ? 1 : -1;
        int err = dx - dy;

        while (true) {
            PutPixel(ix1, iy1);
            if (ix1 == ix2 && iy1 == iy2) break;
            int e2 = 2 * err;
            if (e2 > -dy) {
                err -= dy;
                ix1 += sx;
            }
            if (e2 < dx) {
                err += dx;
                iy1 += sy;
            }
        }
        SaveToFile("C:\\Users\\flipd\\Downloads\\PICTURE_OUTPUT_NAME.png");
    }

    void DrawEllipse(Point center, double hx, double hy) override {
        int segments = 100;
        double angleStep = 2 * M_PI / segments;

        double prevX = center.x + hx;
        double prevY = center.y;

        for (int i = 1; i <= segments; ++i) {
            double angle = i * angleStep;
            double newX = center.x + hx * cos(angle);
            double newY = center.y + hy * sin(angle);
            DrawLine({prevX, prevY}, {newX, newY});
            prevX = newX;
            prevY = newY;
        }
    }

private:
    void SaveToFile(const std::string &filename);

    int width, height;
    sf::Color currentColor{};
    std::vector<uint8_t> pixels;

    static sf::Color GetSFMLColor(const Color color) {
        switch (color) {
            case Color::Black:
                return sf::Color::Black;
            case Color::Red:
                return sf::Color::Red;
            case Color::Green:
                return sf::Color::Green;
            case Color::Blue:
                return sf::Color::Blue;
            case Color::Yellow:
                return sf::Color::Yellow;
            case Color::Pink:
                return {255, 192, 203};
            default:
                return sf::Color::White;
        }
    }

    void PutPixel(int x, int y) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            int index = 4 * (y * width + x);
            pixels[index] = currentColor.r;
            pixels[index + 1] = currentColor.g;
            pixels[index + 2] = currentColor.b;
            pixels[index + 3] = currentColor.a;
        }
    }
};

#endif //CANVAS_H
