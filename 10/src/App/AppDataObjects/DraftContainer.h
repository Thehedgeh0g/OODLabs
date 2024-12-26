//
// Created by flipd on 24.12.2024.
//

#ifndef APPDRAFTCONTAINER_H
#define APPDRAFTCONTAINER_H
#include "ShapeSelection.h"
#include "../../History/History.h"
#include "../../Domain/Draft.h"

namespace App {
    class DraftContainer {
        public:
            explicit DraftContainer(std::unique_ptr<Draft>& draft): m_draft(draft)
            {
            }

            History::History& GetHistory() {
                return m_history;
            }

            std::unique_ptr<Draft>& GetDraft() {
                return m_draft;
            }

            ShapeSelection& GetShapeSelection() {
                return m_selection;
            }

        private:
            History::History m_history;
            ShapeSelection m_selection;
            std::unique_ptr<Draft>& m_draft;
    };
}
#endif //APPDRAFTCONTAINER_H
