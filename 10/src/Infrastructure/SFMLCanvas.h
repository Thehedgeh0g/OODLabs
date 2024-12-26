//
// Created by flipd on 25.12.2024.
//

#ifndef SFMLCANVAS_H
#define SFMLCANVAS_H
#include "SFML/Graphics/RenderWindow.hpp"
#include "../View/ICanvas.h"

class SFMLCanvas : public view::ICanvas {
public:
    explicit SFMLCanvas(sf::RenderTarget& image)
        : m_image(image)
    {}

    ~SFMLCanvas() override;

    void SetColor(uint32_t color) override;

    void MoveTo(double x, double y) override;

    void LineTo(double x, double y) override;

    void DrawEllipse(double cx, double cy, double cr, double ry) override;

    void DrawText(double top, double left, double fontSize, const std::string &text) override;

private:
    sf::RenderTarget& m_image;
    mutable sf::Color m_currentColor;
    mutable sf::Vector2f m_currentPosition;
};
#endif //SFMLCANVAS_H
