//
// Created by flipd on 25.12.2024.
//

#ifndef PDRAFT_H
#define PDRAFT_H
#include <memory>
#include <sstream>
#include <string>

#include "IPresentor.h"
#include "../App/DraftFacade.h"

namespace view {
    class VWindow;
}

namespace Presenter {
    class PDraft : public IPresentor {
    public:
        explicit PDraft(
            std::unique_ptr<App::DraftFacade>& draftFacade,
            std::unique_ptr<App::DraftContainer>& draftContainer
        ): m_draftFacade(draftFacade), m_draftContainer(draftContainer) {};
        ~PDraft() override = default;

        void HandleEvent(std::unique_ptr<Presenter::IInteractionEvent> event) override {

            std::cout << event->GetEventData().data << std::endl;
            // std::istringstream iss(event->GetEventData().data);
            // std::string eventType;
            // iss >> eventType;
            // if (eventType == "Undo") {
            //     Undo();
            // } else if (eventType == "Redo") {
            //     Redo();
            // } else {
            //     throw std::invalid_argument("Invalid event type");
            // }
        }

    private:
        void Undo() {
            m_draftFacade->Undo();
        }

        void Redo() {
            m_draftFacade->Redo();
        }

        std::unique_ptr<App::DraftFacade> &m_draftFacade;
        std::unique_ptr<App::DraftContainer>& m_draftContainer;
    };
}
#endif //PDRAFT_H
