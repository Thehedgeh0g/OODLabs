//
// Created by flipd on 24.12.2024.
//

#ifndef UPDATESHAPECOMMAND_H
#define UPDATESHAPECOMMAND_H
#include <memory>
#include <optional>
#include <utility>

#include "../../Domain/Shape.h"
#include "./../../History/AbstractCommand.h"

namespace App {
    class UpdateShapeCommand : public History::AbstractCommand {
        public:
            UpdateShapeCommand(
                std::shared_ptr<Shape> shape,
                const std::optional<RectD> &frame,
                const std::optional<uint32_t> color
            ): m_shape(std::move(shape)), m_newFrame(frame), m_color(color) {
                m_name = "UpdateShapeCommand";
            }

            ~UpdateShapeCommand() override = default;

            bool ReplaceEdit(const ICommand &edit) override{
                if (auto otherUpdateShape = dynamic_cast<const UpdateShapeCommand *>(&edit);
                    otherUpdateShape &&
                    otherUpdateShape->m_newFrame == m_frame &&
                    otherUpdateShape->m_newColor == m_color
                )
                {
                    m_frame = otherUpdateShape->m_newFrame;
                    m_color = otherUpdateShape->m_newColor;
                    return true;
                }
                return false;
            }

        protected:
            void DoExecute() override {
                if (m_newFrame.has_value()) {
                    m_frame = m_shape->GetFrame();
                    m_shape->SetPosition(m_newFrame.value().point);
                    m_shape->SetSize(m_newFrame.value().width, m_newFrame.value().height);
                }
                if (m_newColor.has_value()) {
                    m_shape->SetColor(m_newColor.value());
                    m_color= m_shape->GetColor();
                }
            }

        void DoUnexecute() override {
                if (m_newFrame.has_value()) {
                    m_shape->SetPosition(m_frame.value().point);
                }
                if (m_newColor.has_value()) {
                    m_color= m_shape->GetColor();
                }
            }

        private:
            std::shared_ptr<Shape> m_shape;
            std::optional<RectD> m_newFrame;
            std::optional<uint32_t> m_newColor;
            std::optional<RectD> m_frame;
            std::optional<uint32_t> m_color;


    };
}

#endif //UPDATESHAPECOMMAND_H
