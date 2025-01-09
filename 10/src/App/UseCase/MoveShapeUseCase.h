//
// Created by flipd on 24.12.2024.
//

#ifndef MOVESHAPEUSECASE_H
#define MOVESHAPEUSECASE_H
#include "IUseCase.h"
#include "./../AppDataObjects/ShapeSelection.h"
#include "../../History/History.h"
#include "../Commands/UpdateShapeCommand.h"
#include "./../AppDataObjects/DraftContainer.h"

namespace App
{
class MoveShapeUseCase : public IUseCase
{
public:
    MoveShapeUseCase(
            const std::unique_ptr<DraftContainer> &draftContainer,
            const Point &offset
            ) :
        m_offset(offset),
        m_shapeSelection(draftContainer->GetShapeSelection()),
        m_commandStorage(draftContainer->GetHistory())
    {
    }

    ~MoveShapeUseCase() override = default;

    void Execute() override
    {
        auto macroCommand = std::make_unique<History::MacroCommand>();
        macroCommand->SetName("Move");
        for (auto &shape: m_shapeSelection.GetSelectedShapes())
        {
            std::optional<RectD> movedFrame = shape.second->GetFrame();
            movedFrame->point.x -= m_offset.x;
            movedFrame->point.y -= m_offset.y;
            macroCommand->AddCommand(std::make_unique<UpdateShapeCommand>(shape.second, movedFrame, std::nullopt));
        }
        m_commandStorage.AddAndExecuteCommand(std::move(macroCommand));
    }

private:
    ShapeSelection &m_shapeSelection;
    History::History &m_commandStorage;
    Point m_offset;
};
}

#endif //MOVESHAPEUSECASE_H
