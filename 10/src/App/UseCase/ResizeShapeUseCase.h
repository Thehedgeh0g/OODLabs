//
// Created by flipd on 24.12.2024.
//

#ifndef RESIZESHAPEUSECASE_H
#define RESIZESHAPEUSECASE_H
#include "IUseCase.h"
#include "../DraftFacade.h"
#include "./../AppDataObjects/ShapeSelection.h"
#include "../../History/History.h"
#include "../Commands/UpdateShapeCommand.h"
#include "./../Commands/InsertShapeCommand.h"

namespace App {
    class ResizeShapeUseCase : public IUseCase
    {
    public:
        ResizeShapeUseCase(
            const std::unique_ptr<DraftContainer>& draftContainer,
            const double newWidth,
            const double newHeight
        ) :
            m_newHeight(newHeight),
            m_newWidth(newWidth),
            m_shapeSelection(draftContainer->GetShapeSelection()),
            m_commandStorage(draftContainer->GetHistory())
        {
        }

        ~ResizeShapeUseCase() override = default;

        void Execute() override {
            std::unique_ptr<History::MacroCommand> macroCommand;
            for (auto& shape: m_shapeSelection.GetSelectedShapes()) {
                std::optional<RectD> resizedFrame = shape.second->GetFrame();
                resizedFrame->width += m_newWidth;
                resizedFrame->height += m_newHeight;
                macroCommand->AddCommand(std::make_unique<UpdateShapeCommand>(shape.second, resizedFrame, std::nullopt));
            }
            m_commandStorage.AddAndExecuteCommand(std::move(macroCommand));
        }

    private:
        ShapeSelection& m_shapeSelection;
        History::History& m_commandStorage;
        double m_newWidth;
        double m_newHeight;
    };
}

#endif //RESIZESHAPEUSECASE_H
