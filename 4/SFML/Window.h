//
// Created by thehedgeh0g on 16.10.24.
//

#ifndef WINDOW_H
#define WINDOW_H

class Window
{
public:
    Window() : m_window(sf::VideoMode(1000, 800), "Window")
    {
        m_window.setVerticalSyncEnabled(true);
    }

    void DisplayShapes(const std::vector<std::shared_ptr<sf::Drawable> > &shapes)
    {
        m_window.clear(sf::Color::White);

        for (const auto & shape : shapes)
        {
            m_window.draw(*shape);
        }
        m_window.display();
    }

private:
    sf::RenderWindow m_window;
};

#endif //WINDOW_H
