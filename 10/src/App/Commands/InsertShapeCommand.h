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
        const ShapeType m_type,
        const RectD& m_frame,
        const uint32_t m_color
        ): m_draft(draft), m_type(m_type), m_frame(m_frame), m_color(m_color) {
            m_name = "CreateShapeCommand";
        }

        ~InsertShapeCommand() override = default;

    protected:
        void DoExecute() override {
            auto shape = std::make_shared<Shape>(
                m_type,
                m_frame,
                m_color
            );
            m_shapeId = shape->GetId();
            if (m_draft->FindShapeById(shape->GetId()) == nullptr) {
                m_draft->AddShape(shape);
                return;
            }
            throw std::runtime_error("Shape already in draft");
        }

        void DoUnexecute() override {
            if (m_draft->FindShapeById(m_shapeId) != nullptr) {
                m_draft->RemoveShape(m_shapeId);
                return;
            }
            throw std::runtime_error("Shape not found in draft");
        }

    private:
        std::unique_ptr<Draft> &m_draft;
        std::string m_shapeId;
        ShapeType m_type;
        RectD m_frame;
        uint32_t m_color;
    };
}

#endif //INSERTSHAPECOMMAND_H
