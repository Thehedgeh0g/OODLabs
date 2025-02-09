//
// Created by flipd on 08.01.2025.
//

#ifndef MOUSEUPEVENT_H
#define MOUSEUPEVENT_H
#include "../../Presentor/IInteractionEvent.h"
#include "SFML/Window/Event.hpp"

class MouseUpEvent : public Presenter::IInteractionEvent{
public:
    explicit MouseUpEvent(const sf::Event& event) {
        if (const auto mouseEventReleased = event.getIf<sf::Event::MouseButtonReleased>()) {
            m_position.x = mouseEventReleased->position.x;
            m_position.y = mouseEventReleased->position.y;
            return;
        }
        m_interactionType = ViewInteractionType::Unknown;
        m_isCtrlPressed = isKeyPressed(sf::Keyboard::Key::RControl);
    };

    [[nodiscard]] bool IsCtrlPressed() const {
        return m_isCtrlPressed;
    }

    [[nodiscard]] Point GetPosition() const {
        return m_position;
    }


    ViewInteractionType GetInteractionType() override {
        return m_interactionType;
    }

private:
    ViewInteractionType m_interactionType = ViewInteractionType::MouseUp;
    Point m_position = {};
    bool m_isCtrlPressed = false;
};

#endif //MOUSEUPEVENT_H
