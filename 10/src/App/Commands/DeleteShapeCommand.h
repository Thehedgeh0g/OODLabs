//
// Created by flipd on 24.12.2024.
//

#ifndef DELETESHAPECOMMAND_H
#define DELETESHAPECOMMAND_H
#include <memory>
#include <utility>

#include "../../Domain/Shape.h"
#include "../../Domain/Draft.h"
#include "./../../History/AbstractCommand.h"

namespace App {
    class DeleteShapeCommand : public History::AbstractCommand {
        public:
            DeleteShapeCommand(
                std::unique_ptr<Draft>& draft,
                std::string shapeId
            ): m_draft(draft), m_shapeId(std::move(shapeId)) {
                m_name = "DeleteShapeCommand";
            }

            ~DeleteShapeCommand() override = default;

        protected:
            void DoExecute() override {
                if(m_draft->FindShapeById(m_shapeId) != nullptr) {
                    m_shape = std::make_shared<Shape>(*(m_draft->FindShapeById(m_shapeId)));
                    m_draft->RemoveShape(m_shapeId);
                    return;
                }
                throw std::runtime_error("Shape not found in draft");
            }

            void DoUnexecute() override {
                if(m_draft->FindShapeById(m_shapeId) == nullptr) {
                    m_draft->AddShape(std::move(m_shape));
                    return;
                }
                throw std::runtime_error("Shape already in draft");
            }

        private:
            std::unique_ptr<Draft>& m_draft;
            std::shared_ptr<Shape> m_shape;
            std::string m_shapeId;
    };
}

#endif //DELETESHAPECOMMAND_H
