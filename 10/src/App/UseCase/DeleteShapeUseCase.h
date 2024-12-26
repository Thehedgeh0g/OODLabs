//
// Created by flipd on 24.12.2024.
//

#ifndef DELETESHAPEUSECASE_H
#define DELETESHAPEUSECASE_H
#include <utility>

#include "IUseCase.h"
#include "./../AppDataObjects/ShapeSelection.h"
#include "../../History/History.h"
#include "../Commands/DeleteShapeCommand.h"

namespace App {
    class DeleteShapeUseCase : public IUseCase
    {
    public:
        explicit DeleteShapeUseCase(
            std::unique_ptr<DraftContainer>& draftContainer
        ) :
            m_shapeSelection(draftContainer->GetShapeSelection()),
            m_pictureDraft(draftContainer),
            m_commandStorage(draftContainer->GetHistory())
        {
        }

        ~DeleteShapeUseCase() override = default;

        void Execute() override {
            auto macroCommand = std::make_unique<History::MacroCommand>();
            for (const auto& shape: m_shapeSelection.GetSelectedShapes()) {
                macroCommand->AddCommand(std::make_unique<DeleteShapeCommand>(m_pictureDraft->GetDraft(), shape.second->GetId()));
            }
            m_commandStorage.AddAndExecuteCommand(std::move(macroCommand));
        }

    private:
        ShapeSelection& m_shapeSelection;
        std::unique_ptr<DraftContainer>& m_pictureDraft;
        History::History& m_commandStorage;
    };
}

#endif //DELETESHAPEUSECASE_H
