//
// Created by flipd on 08.01.2025.
//

#ifndef MOUSEMOVEDEVENT_H
#define MOUSEMOVEDEVENT_H
#include "../../Presentor/IInteractionEvent.h"
#include "SFML/Window/Event.hpp"

class MouseMovedEvent : public Presenter::IInteractionEvent{
public:
    explicit MouseMovedEvent(const sf::Event& event) {
        if (const auto mouseEventMoved = event.getIf<sf::Event::MouseMoved>()) {
            m_position.x = mouseEventMoved->position.x;
            m_position.y = mouseEventMoved->position.y;
            m_isMouseButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
            return;
        }
        m_interactionType = ViewInteractionType::Unknown;
    };

    ViewInteractionType GetInteractionType() override {
        return m_interactionType;
    }

    [[nodiscard]] bool IsMouseButtonPressed() const {
        return m_isMouseButtonPressed;
    }


    Point GetPosition() {
        return m_position;
    }

private:
    ViewInteractionType m_interactionType = ViewInteractionType::MouseMove;
    Point m_position = {};
    bool m_isMouseButtonPressed = false;
};

#endif //MOUSEMOVEDEVENT_H
