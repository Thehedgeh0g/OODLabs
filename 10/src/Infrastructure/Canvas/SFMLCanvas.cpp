//
// Created by flipd on 25.12.2024.
//
#include "SFMLCanvas.h"

#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/VertexArray.hpp"
#include <cmath>

#include "SFML/Graphics/Text.hpp"

void SFMLCanvas::MoveTo(const double x, const double y) {
    m_currentPosition = sf::Vector2f(static_cast<float>(x), static_cast<float>(y));
}

void SFMLCanvas::LineTo(const double x, const double y) {
    sf::VertexArray line(sf::PrimitiveType::Lines, 2);
    line[0].position = m_currentPosition;
    line[1].position = sf::Vector2f(static_cast<float>(x), static_cast<float>(y));
    line[0].color = sf::Color(m_currentColor);
    line[1].color = sf::Color(m_currentColor);
    m_image.draw(line);
    m_currentPosition = sf::Vector2f(static_cast<float>(x), static_cast<float>(y));
}

void SFMLCanvas::DrawEllipse(double cx, double cy, double cr, double ry) {
    sf::CircleShape circle(static_cast<float>(cr));
    circle.setPosition({static_cast<float>(cx - cr), static_cast<float>(cy + cr)});
    circle.setOutlineThickness(1);
    circle.setOutlineColor(m_currentColor);
    circle.setFillColor(sf::Color::Transparent);
    m_image.draw(circle);
}

void SFMLCanvas::DrawText(double top, double left, double fontSize, const std::string &text) {
    MoveTo(left, top);
    SetColor(0x000000FF);
    sf::Font font("arialmt.ttf");
    sf::Text sfmlText(font, text);
    sfmlText.setCharacterSize(static_cast<unsigned int>(round(fontSize)));
    sfmlText.setStyle(sf::Text::Bold);
    sfmlText.setFillColor(m_currentColor);
    sfmlText.setPosition(m_currentPosition);
    m_image.draw(sfmlText);
}

SFMLCanvas::~SFMLCanvas() = default;

void SFMLCanvas::SetColor(const uint32_t color) {
    m_currentColor = sf::Color(color);
}
