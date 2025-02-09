//
// Created by flipd on 25.12.2024.
//

#ifndef PSHAPE_H
#define PSHAPE_H
#include <memory>
#include <regex>

#include "../App/DraftFacade.h"

namespace view {
    class VWindow;
}

namespace Presenter {
    class PShape{
    public:
        PShape(
            std::unique_ptr<App::DraftFacade> &draftFacade,
            std::unique_ptr<App::DraftContainer> &draftContainer
        ): m_draftFacade(draftFacade), m_draftContainer(draftContainer) {
        };

        void Create(ShapeType shapeType, Point position, double height, double width, uint32_t color) {
            m_draftFacade->InsertNewShape(shapeType, position, height, width, color);
        }

        void Update(UpdateType updateType, Point offset, double height, double width) {
            m_draftFacade->UpdateSelectedShapes(updateType, offset, height, width);
        }

        void Select(const std::string &shapeId) {
            m_draftFacade->SelectShape(shapeId);
        }

        void AddToSelection(const std::string &shapeId) {
            m_draftFacade->SelectShape(shapeId);
        }

        void Delete() {
            m_draftFacade->DeleteSelectedShapes();
        }

    private:
        std::unique_ptr<App::DraftFacade> &m_draftFacade;
        std::unique_ptr<App::DraftContainer> &m_draftContainer;
    };
}
#endif //PSHAPE_H
