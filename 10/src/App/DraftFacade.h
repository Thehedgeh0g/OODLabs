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

        void InsertNewShape(const std::string &data) {
            std::istringstream iss(data);
            std::string shapeTypeStr;
            ShapeType shapeType;
            double x, y, width, height;
            uint32_t color;
            iss >> shapeTypeStr >> x >> y >> width >> height >> color;
            if (shapeTypeStr == "Rectangle") {
                shapeType = ShapeType::Rectangle;
            } else if (shapeTypeStr == "Circle") {
                shapeType = ShapeType::Circle;
            } else if (shapeTypeStr == "Triangle") {
                shapeType = ShapeType::Triangle;
            } else {
                throw std::invalid_argument("Invalid shapeType");
            }
            RectD frame = {x, y, width, height};
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
                m_draftContainer->GetShapeSelection().SetSelectedShape(shape);
            } else {
                m_draftContainer->GetShapeSelection().RemoveSelectedShape(shapeId);
            }
        }

        void UpdateSelectedShapes(const std::string &data) {
            std::istringstream iss(data);
            std::string updateTypeStr;
            UpdateType updateType;
            iss >> updateTypeStr;
            if (updateTypeStr == "Move") {
                updateType = UpdateType::Move;
            } else if (updateTypeStr == "Resize") {
                updateType = UpdateType::Resize;
            } else {
                throw std::invalid_argument("Invalid move type");
            }
            double offsetX = 0, offsetY = 0;
            iss >> offsetX >> offsetY;
            if (updateType == UpdateType::Move) {
                auto useCase = MoveShapeUseCase(m_draftContainer, {offsetX, offsetY});
                useCase.Execute();
                return;
            }
            double widthOffset = 0, heightOffset = 0;
            iss >> widthOffset >> heightOffset;
            auto useCase = ResizeShapeUseCase(m_draftContainer, widthOffset, heightOffset);
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
