//
// Created by thehedgeh0g on 16.10.24.
//

#ifndef CANVAS_H
#define CANVAS_H
#include <memory>

#include <SFML/Graphics.hpp>

#include "./../Draft/Color.h"
#include "./../Draft/ICanvas.h"
#include "./Window.h"

class Canvas : public ICanvas
{
public:
    explicit Canvas(
        std::unique_ptr<Window>&& window
    ) :
        m_window(std::move(window))
    {
    }

    ~Canvas() override = default;

    void SetColor(const Color color) override
    {
        m_currentColor = sf::Color(GetSFMLColor(color));
    }

    void DrawLine(const Point start, const Point end) override
    {
        sf::VertexArray line(sf::Lines, 2);
        line[0].color = m_currentColor;
        line[1].color = m_currentColor;

        line[0].position = sf::Vector2f(static_cast<float>(start.x), static_cast<float>(start.y));
        line[1].position = sf::Vector2f(static_cast<float>(end.x), static_cast<float>(end.y));

        m_shapes.push_back(std::make_shared<sf::VertexArray>(line));
        m_window->DisplayShapes(m_shapes);
    }

    void DrawEllipse(const Point center, const double hx, const double hy) override
    {
        sf::CircleShape ellipse;
        ellipse.setPosition(static_cast<float>(center.x), static_cast<float>(center.y));
        ellipse.setScale(static_cast<float>(hx), static_cast<float>(hy));
        ellipse.setOutlineThickness(1);
        ellipse.setOutlineColor(m_currentColor);
        ellipse.setFillColor(sf::Color::Transparent);
        m_shapes.push_back(std::make_shared<sf::CircleShape>(ellipse));
        m_window->DisplayShapes(m_shapes);
    }

private:
    static sf::Color GetSFMLColor(const Color color)
    {
        switch (color)
        {
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
                return {255,192,203};
            default:
                return sf::Color::White;
        }
    }

    std::unique_ptr<Window> m_window;
	std::vector<std::shared_ptr<sf::Drawable>> m_shapes;
    mutable sf::Color m_currentColor;
    mutable sf::Vector2f m_currentPosition;
};

#endif //CANVAS_H
