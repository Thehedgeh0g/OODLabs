//
// Created by flipd on 08.01.2025.
//

#ifndef MOUSEDOWNEVENT_H
#define MOUSEDOWNEVENT_H
#include "../../Presentor/IInteractionEvent.h"
#include "SFML/Window/Event.hpp"

class MouseDownEvent : public Presenter::IInteractionEvent{
public:
    explicit MouseDownEvent(const sf::Event& event, const sf::Clock& clock): m_eventStartTime(clock) {
        if (const auto mouseEventPressed = event.getIf<sf::Event::MouseButtonPressed>()) {
            m_position.x = mouseEventPressed->position.x;
            m_position.y = mouseEventPressed->position.y;
            m_isCtrlPressed = isKeyPressed(sf::Keyboard::Key::RControl);
            return;
        }
        m_interactionType = ViewInteractionType::Unknown;
    };

    ViewInteractionType GetInteractionType() override {
        return m_interactionType;
    }

    [[nodiscard]] bool IsCtrlPressed() const {
        return m_isCtrlPressed;
    }

    bool IsDragging() const {
        return sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && m_eventStartTime.getElapsedTime().asMilliseconds() >= 5;
    }

    Point GetPosition() {
        return m_position;
    }

private:
    ViewInteractionType m_interactionType = ViewInteractionType::MouseDown;
    Point m_position = {};
    bool m_isCtrlPressed = false;
    sf::Clock m_eventStartTime;
};

#endif //MOUSEDOWNEVENT_H
