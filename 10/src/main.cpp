//
// Created by flipd on 24.12.2024.
//

#include <iostream>
#include <memory>

#include "App/AppDataObjects/SubscriptionContainer.h"
#include "Infrastructure/SFMLCanvas.h"
#include "Infrastructure/SFMLEvent.h"
#include "Presentor/MainPresenter.h"
#include "View/Components/VWindow.h"
#include "SFML/Graphics/RenderWindow.hpp"

int main() {
    auto renderWindow = sf::RenderWindow(sf::VideoMode({800, 600}), "paint");
    std::unique_ptr<view::ICanvas> canvas = std::make_unique<SFMLCanvas>(renderWindow);
    std::unique_ptr<view::VWindow> window = std::make_unique<view::VWindow>(canvas);
    auto draft = std::make_unique<Draft>();
    auto draftContainer = std::make_unique<App::DraftContainer>(draft);
    auto draftFacade = std::make_unique<App::DraftFacade>(draftContainer);
    auto subscriptionContainer = std::make_unique<App::SubscriptionContainer>(draft);
    auto presenter = std::make_unique<Presenter::MainPresenter>(draftFacade, draftContainer, window, subscriptionContainer);


    while (renderWindow.isOpen())
    {
        while (const std::optional event = renderWindow.pollEvent())
        {
                if (!event.has_value())
                {
                    break;
                }

                if (event->is<sf::Event::Closed>())
                {
                    renderWindow.close();
                    break;
                }

                try {
                    presenter->HandleEvent(std::make_unique<SFMLEvent>(*event));
                }
                catch (const std::exception& e) {
                    std::cout << e.what() << std::endl;
                }

            renderWindow.clear(sf::Color::White);
            window->Draw();
            renderWindow.display();
        }
    }
}
