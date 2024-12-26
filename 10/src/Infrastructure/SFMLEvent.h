//
// Created by flipd on 25.12.2024.
//

#ifndef SFMLEVENT_H
#define SFMLEVENT_H
#include "../Common/CommonStructs.h"
#include "../Presentor/IInteractionEvent.h"
#include "SFML/Window/Event.hpp"

class SFMLEvent : public Presenter::IInteractionEvent{
    public:
    explicit SFMLEvent(const sf::Event& event) {
        if (auto mouseEventPressed = event.getIf<sf::Event::MouseButtonPressed>()) {
            m_event.actionType = ViewInteractionType::MouseDown;
            m_event.data = "MousePressed " + std::to_string(mouseEventPressed->position.x) + ' ' + std::to_string(mouseEventPressed->position.y);
            return;
        }
        if (auto mouseEventReleased = event.getIf<sf::Event::MouseButtonReleased>()) {
            m_event.actionType = ViewInteractionType::MouseDown;
            m_event.data = "MouseReleased " + std::to_string(mouseEventReleased->position.x) + ' ' + std::to_string(mouseEventReleased->position.y);
            return;
        }
        if (auto mouseEventMoved = event.getIf<sf::Event::MouseMoved>()) {
            m_event.actionType = ViewInteractionType::MouseDown;
            m_event.data = "MouseMoved " + std::to_string(mouseEventMoved->position.x) + ' ' + std::to_string(mouseEventMoved->position.y);
            return;
        }
        if (auto keyEvent = event.getIf<sf::Event::KeyReleased>()) {
            m_event.actionType = ViewInteractionType::ButtonPress;
            std::cout << "key pressed\n";
            switch (keyEvent->code) {
                case sf::Keyboard::Key::Delete: {
                    m_event.data = "KeyPressed Delete";
                    break;
                }
                case sf::Keyboard::Key::Z: {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RControl))
                    {
                        m_event.data = "KeyPressed Z";
                    }
                    break;
                }
                case sf::Keyboard::Key::Y: {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RControl))
                    {
                        m_event.data = "KeyPressed Y";
                    }
                    break;
                }
                default: break;
            }
            return;
        }
    };
    ~SFMLEvent() override = default;

    ViewInteractionType GetInteractionType() override {
        return m_event.actionType;
    }

    Presenter::EventData GetEventData() override {
        return m_event;
    }

    void SetEventData(const Presenter::EventData eventData) override {
        m_event = eventData;
    }

    ViewInteractionType getViewInteraction();
    private:
        Presenter::EventData m_event;
};

#endif //SFMLEVENT_H
