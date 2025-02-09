//
// Created by flipd on 25.12.2024.
//

#ifndef PDRAFT_H
#define PDRAFT_H
#include <memory>
#include "IPresentor.h"
#include "../App/DraftFacade.h"

namespace view {
    class VWindow;
}

namespace Presenter {
    class PDraft{
    public:
        explicit PDraft(
            std::unique_ptr<App::DraftFacade> &draftFacade
        ): m_draftFacade(draftFacade) {
        };

        void Undo() const {
            m_draftFacade->Undo();
        }

        void Redo() const {
            m_draftFacade->Redo();
        }

    private:
        std::unique_ptr<App::DraftFacade> &m_draftFacade;
    };
}
#endif //PDRAFT_H
