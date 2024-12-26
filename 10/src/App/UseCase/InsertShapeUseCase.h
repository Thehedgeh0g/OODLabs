//
// Created by flipd on 24.12.2024.
//

#ifndef INSERTSHAPEUSECASE_H
#define INSERTSHAPEUSECASE_H
#include <utility>

#include "IUseCase.h"
#include "./../AppDataObjects/ShapeSelection.h"
#include "../../History/History.h"
#include "./../Commands/InsertShapeCommand.h"

namespace App {
    class InsertShapeUseCase : public IUseCase
    {
    public:
        InsertShapeUseCase(
            std::unique_ptr<DraftContainer>& draftContainer,
            ShapeDTO shapeData
        ) :
            m_shapeData(std::move(shapeData)),
            m_pictureDraft(draftContainer),
            m_shapeSelection(draftContainer->GetShapeSelection()),
            m_commandStorage(draftContainer->GetHistory())
        {
        }

        ~InsertShapeUseCase() override = default;

        void Execute() override
        {
            if (!m_shapeData.color.has_value() || !m_shapeData.type.has_value() || !m_shapeData.frame.has_value()) {
                throw std::invalid_argument("Invalid shape data got while creating");
            }
            auto shape = std::make_shared<Shape>(
                m_shapeData.type.value(),
                m_shapeData.frame.value(),
                m_shapeData.color.value()
            );
            auto insertCommand = std::make_unique<InsertShapeCommand>(m_pictureDraft->GetDraft(), shape);
            m_commandStorage.AddAndExecuteCommand(std::move(insertCommand));
        }

    private:
        ShapeSelection& m_shapeSelection;
        std::unique_ptr<DraftContainer>& m_pictureDraft;
        History::History& m_commandStorage;
        ShapeDTO m_shapeData;
    };
}

#endif //INSERTSHAPEUSECASE_H
