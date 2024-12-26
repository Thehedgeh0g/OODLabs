//
// Created by flipd on 24.12.2024.
//

#ifndef INSERTSHAPECOMMAND_H
#define INSERTSHAPECOMMAND_H
#include <memory>

#include "../../Domain/Draft.h"
#include "../../Domain/Shape.h"
#include "./../../History/AbstractCommand.h"

namespace App {
    class InsertShapeCommand : public History::AbstractCommand {
    public:
        InsertShapeCommand(
            std::unique_ptr<Draft> &draft,
            std::shared_ptr<Shape> &shape
        ): m_draft(draft), m_shape(shape) {
            m_name = "CreateShapeCommand";
        }

        ~InsertShapeCommand() override = default;

    protected:
        void DoExecute() override {
            if (m_draft->FindShapeById(m_shape->GetId()) == nullptr) {
                m_draft->AddShape(std::move(m_shape));
                return;
            }
            throw std::runtime_error("Shape already in draft");
        }

        void DoUnexecute() override {
            if (m_draft->FindShapeById(m_shape->GetId()) != nullptr) {
                m_draft->RemoveShape(m_shape->GetId());
                return;
            }
            throw std::runtime_error("Shape not found in draft");
        }

    private:
        std::unique_ptr<Draft> &m_draft;
        std::shared_ptr<Shape> &m_shape;
    };
}

#endif //INSERTSHAPECOMMAND_H
