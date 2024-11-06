//
// Created by thehedgeh0g on 06.11.24.
//

#ifndef CONSOLECANVAS_H
#define CONSOLECANVAS_H
#include <iostream>
#include <string>
#include <vector>
#include "./../Shape/Point.h"
#include "./ICanvas.h"

class ConsoleCanvas : public ICanvas {
public:
    ConsoleCanvas(std::ostream& stream): m_outStream(stream) {};

    void SetFillColor(const std::string& color) override {
        m_outStream << "Setting fill color to: " << color << std::endl;
    }

    void SetLineColor(const std::string& color) override {
        m_outStream << "Setting line color to: " << color << std::endl;
    }

    void SetLineThickness(double thickness) override {
        m_outStream << "Setting line thickness to: " << thickness << std::endl;
    }

    void DrawLine(Point start, Point end) override {
        m_outStream << "Drawing line from (" << start.x << ", " << start.y << ") to ("
                  << end.x << ", " << end.y << ")" << std::endl;
    }

    void DrawEllipse(Point center, double hx, double hy) override {
        m_outStream << "Drawing ellipse with center (" << center.x << ", " << center.y
                  << "), horizontal radius " << hx << " and vertical radius " << hy << std::endl;
    }

    void FillEllipse(double x, double y, double width, double height) override {
        m_outStream << "Filling ellipse at (" << x << ", " << y << ") with width " << width
                  << " and height " << height << std::endl;
    }

    void FillPolygon(const std::vector<std::pair<double, double>>& points) override {
        m_outStream << "Filling polygon with points: ";
        for (const auto& point : points) {
            m_outStream << "(" << point.first << ", " << point.second << ") ";
        }
        m_outStream << std::endl;
    }

private:
    std::ostream& m_outStream;
};
#endif //CONSOLECANVAS_H
