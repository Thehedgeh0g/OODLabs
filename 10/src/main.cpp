//
// Created by flipd on 24.12.2024.
//

#include <iostream>
#include <memory>

#include "App/AppDataObjects/SubscriptionContainer.h"
#include "Infrastructure/Canvas/SFMLCanvas.h"
#include "Infrastructure/Events/EventFactory.h"
#include "Presentor/MainPresenter.h"
#include "View/Components/VWindow.h"
#include "SFML/Graphics/RenderWindow.hpp"

int main() {
    auto renderWindow = sf::RenderWindow(sf::VideoMode({800, 600}), "paint");
    std::unique_ptr<view::ICanvas> canvas = std::make_unique<SFMLCanvas>(renderWindow);
    auto draft = std::make_unique<Draft>();
    auto draftContainer = std::make_unique<App::DraftContainer>(draft);
    auto draftFacade = std::make_unique<App::DraftFacade>(draftContainer);
    auto subscriptionContainer = std::make_unique<App::SubscriptionContainer>(draft);
    auto draftPresenter = std::make_unique<Presenter::PDraft>(draftFacade);
    auto shapePresenter = std::make_unique<Presenter::PShape>(draftFacade, draftContainer);
    auto menu = std::make_unique<view::VMenu>(800, 100, shapePresenter);
    const auto window = std::make_unique<view::VWindow>(canvas, std::move(menu), std::move(draftPresenter),
                                                        shapePresenter, draftContainer, subscriptionContainer);


    while (renderWindow.isOpen()) {
        while (const std::optional event = renderWindow.pollEvent()) {
            sf::Clock clock;
            if (!event.has_value()) {
                break;
            }

            if (event->is<sf::Event::Closed>()) {
                renderWindow.close();
                break;
            }

            try {
                window->Notify(EventFactory::createEvent(event.value(), clock));
                clock.restart();
            } catch (const std::exception &e) {
                std::cout << e.what() << std::endl;
            }

            renderWindow.clear(sf::Color::White);
            window->Draw();
            renderWindow.display();
        }
    }
}
