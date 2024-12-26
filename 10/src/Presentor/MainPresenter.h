//
// Created by flipd on 25.12.2024.
//

#ifndef MAINPRESENTER_H
#define MAINPRESENTER_H
#include <memory>
#include <utility>

#include "IPresentor.h"
#include "PDraft.h"
#include "PShape.h"
#include "../View/Components/VWindow.h"

namespace Presenter {
    class MainPresenter : IPresentor {
    public:
        MainPresenter(
            std::unique_ptr<App::DraftFacade> &draftFacade,
            std::unique_ptr<App::DraftContainer> &draftContainer,
            std::unique_ptr<view::VWindow> &window,
            const std::unique_ptr<App::SubscriptionContainer> &subscriptionContainer
        ) : m_pDraft(draftFacade, draftContainer),
            m_pShape(draftFacade, draftContainer),
            m_window(window),
            m_draftContainer(draftContainer),
            m_subscriptionContainer(subscriptionContainer) {
            subscriptionContainer->SubscribeOnShapeCreated(
                draftContainer->GetDraft(),
                [this](
            const RectD &frame,
            const std::string &id,
            const uint32_t &color,
            const ShapeType &shapeType
            )
                {
                    this->DoOnShapeCreated(frame, id, color, shapeType);
                }
            );
            subscriptionContainer->SubscribeOnShapeDeleted(
                draftContainer->GetDraft(),
                [this](
            const std::string &id
            )
                {
                    this->DoOnShapeDeleted(id);
                }
            );
        };

        ~MainPresenter() override = default;

        void HandleEvent(std::unique_ptr<Presenter::IInteractionEvent> event) override {
            std::istringstream iss(event->GetEventData().data);
            std::string action;
            iss >> action;
            if (action == "MousePressed") {
                Press(iss, event, action);
            }
            if (action == "MouseMoved" && m_isPressed) {
                Drag(iss, event);
            }
            if (action == "MouseReleased") {
                m_isPressed = false;
            }
            if (action == "KeyPressed Delete") {
                m_pShape.HandleEvent(std::move(event));
            }
            if ((action == "KeyPressed Z") && (action == "KeyPressed Y")) {
                m_pDraft.HandleEvent(std::move(event));
            }
        }

    private:
        void Drag(std::istringstream &iss, std::unique_ptr<IInteractionEvent> &event) {
            Point releasePoint{};
            iss >> releasePoint.x >> releasePoint.y;
            std::string shapeId = m_window->DetermineViewComponentByPoint(m_pressPoint);
            EventData concreteEventData = event->GetEventData();
            concreteEventData.data += (" " + std::to_string(m_pressPoint.x) + " " + std::to_string(m_pressPoint.y) + " "
                                       +
                                       shapeId);
            m_pressPoint = releasePoint;
            event->SetEventData(concreteEventData);
            m_pShape.HandleEvent(std::move(event));
        }

        void Press(std::istringstream &iss, std::unique_ptr<IInteractionEvent> &event, const std::string &action) {
            m_isPressed = true;
            iss >> m_pressPoint.x >> m_pressPoint.y;
            const std::string target = m_window->DetermineViewComponentByPoint(m_pressPoint);
            EventData concreteEventData = event->GetEventData();
            concreteEventData.data = action + " " + target;
            event->SetEventData(concreteEventData);
            m_pShape.HandleEvent(std::move(event));
        }

        void DoOnShapeChanged(const RectD &frame, const std::string &id) {
            m_window->ModifyShape(id, 0x000000FF, frame);
        }

        void DoOnShapeCreated(const RectD &frame,
                              const std::string &id,
                              const uint32_t &color,
                              const ShapeType &shapeType
        ) {
            m_window->AddShape(id, frame, color, shapeType);
            try {
                m_subscriptionContainer->SubscribeOnShape(
                    m_draftContainer->GetDraft(),
                    id,
                    [this](
                        const RectD &frame,
                        const std::string &id
                    )
                    {
                        this->DoOnShapeChanged(frame, id);
                    }
                );
            } catch (const std::exception &e) {
                std::cout << e.what() << std::endl;
            }
        }

        void DoOnShapeDeleted(const std::string &id) {
            m_window->DeleteShape(id);
        }

        PDraft m_pDraft;
        PShape m_pShape;
        Point m_pressPoint;
        bool m_isPressed = false;
        std::unique_ptr<view::VWindow> &m_window;
        std::unique_ptr<App::DraftContainer> &m_draftContainer;
        const std::unique_ptr<App::SubscriptionContainer> &m_subscriptionContainer;
    };
}
#endif //MAINPRESENTER_H
