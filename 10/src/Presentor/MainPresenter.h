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
            std::unique_ptr<App::DraftContainer> &draftContainer,
            std::unique_ptr<view::VWindow> &window,
            const std::unique_ptr<App::SubscriptionContainer> &subscriptionContainer
        ) : m_window(window),
            m_draftContainer(draftContainer),
            m_subscriptionContainer(subscriptionContainer) {
        };

        ~MainPresenter() override = default;

    private:

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

        Point m_pressPoint;
        bool m_isPressed = false;
        std::unique_ptr<view::VWindow> &m_window;
        std::unique_ptr<App::DraftContainer> &m_draftContainer;
        const std::unique_ptr<App::SubscriptionContainer> &m_subscriptionContainer;
    };
}
#endif //MAINPRESENTER_H
