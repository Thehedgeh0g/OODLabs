//
// Created by flipd on 24.12.2024.
//

#ifndef DRAFTFACADE_H
#define DRAFTFACADE_H
#include "../History/History.h"
#include "../Domain/Draft.h"
#include "AppDataObjects/DraftContainer.h"
#include "UseCase/DeleteShapeUseCase.h"
#include "UseCase/InsertShapeUseCase.h"
#include "UseCase/MoveShapeUseCase.h"
#include "UseCase/ResizeShapeUseCase.h"

namespace App {
    class DraftFacade {
    public:
        explicit DraftFacade(std::unique_ptr<DraftContainer> &draftContainer): m_draftContainer(draftContainer) {
        };

        void InsertNewShape(ShapeType shapeType, Point position, double height, double width, uint32_t color) {
            RectD frame = {position.x, position.y, width, height};
            ShapeDTO shapeData = {std::nullopt, shapeType, frame, color};
            auto useCase = InsertShapeUseCase(m_draftContainer, shapeData);
            useCase.Execute();
        }

        void DeleteSelectedShapes() {
            auto useCase = DeleteShapeUseCase(m_draftContainer);
            useCase.Execute();
        }

        void SelectShape(const std::string &shapeId) {
            const auto &shape = m_draftContainer->GetDraft()->FindShapeById(shapeId);
            if (!shape) {
                return;
            }

            if (!m_draftContainer->GetShapeSelection().IsSelectedShape(shapeId)) {
                m_draftContainer->GetShapeSelection().ClearSelectedShapes();
                m_draftContainer->GetShapeSelection().SetSelectedShape(shape);
            } else {
                m_draftContainer->GetShapeSelection().RemoveSelectedShape(shapeId);
            }
        }

        void AddShapeToSelection(const std::string &shapeId) {
            const auto &shape = m_draftContainer->GetDraft()->FindShapeById(shapeId);
            if (!shape) {
                return;
            }
            if (!m_draftContainer->GetShapeSelection().IsSelectedShape(shapeId)) {
                m_draftContainer->GetShapeSelection().SetSelectedShape(shape);
            } else {
                m_draftContainer->GetShapeSelection().RemoveSelectedShape(shapeId);
            }
        }

        void UpdateSelectedShapes(UpdateType updateType, Point offset, double height, double width) {
            if (updateType == UpdateType::Move) {
                auto useCase = MoveShapeUseCase(m_draftContainer, offset);
                useCase.Execute();
                return;
            }
            auto useCase = ResizeShapeUseCase(m_draftContainer, width, height);
            useCase.Execute();
        }

        void Undo() {
            m_draftContainer->GetHistory().Undo();
        }

        void Redo() {
            m_draftContainer->GetHistory().Redo();
        }

    private:
        std::unique_ptr<DraftContainer> &m_draftContainer;
    };
}

#endif //DRAFTFACADE_H
