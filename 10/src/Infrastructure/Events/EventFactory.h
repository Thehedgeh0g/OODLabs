//
// Created by flipd on 08.01.2025.
//

#ifndef EVENTFACTORY_H
#define EVENTFACTORY_H
#include <memory>

#include "DeleteKeysPressedEvent.h"
#include "MouseDownEvent.h"
#include "MouseMovedEvent.h"
#include "MouseUpEvent.h"
#include "RedoKeysPressedEvent.h"
#include "UndoKeysPressedEvent.h"
#include "SFML/Window/Event.hpp"
#include "../../Presentor/IInteractionEvent.h"

class EventFactory {
public:
    static std::shared_ptr<Presenter::IInteractionEvent> createEvent(const sf::Event &event, const sf::Clock& eventStartTime) {
        if (const auto keyDown = event.getIf<sf::Event::KeyPressed>()) {
            if (
                true
            ) {
                if (
                    keyDown->code == sf::Keyboard::Key::Y
                ) {
                    return std::make_shared<RedoKeysPressedEvent>();
                }
                if (
                    keyDown->code == sf::Keyboard::Key::Z
                ) {
                    return std::make_shared<UndoKeysPressedEvent>();
                }
            }
            if (keyDown->code == sf::Keyboard::Key::Delete) {
                return std::make_shared<DeleteKeysPressedEvent>();
            }
        }
        if (event.is<sf::Event::MouseButtonReleased>()) {
            return std::make_shared<MouseUpEvent>(event);
        }
        if (event.is<sf::Event::MouseButtonPressed>()) {
            return std::make_shared<MouseDownEvent>(event, eventStartTime);
        }
        if (event.is<sf::Event::MouseMoved>()) {
            return std::make_shared<MouseMovedEvent>(event);
        }
        return nullptr;
    }
};
#endif //EVENTFACTORY_H
