//
// Created by flipd on 25.12.2024.
//

#ifndef VSHAPE_H
#define VSHAPE_H
#include <memory>
#include <string>
#include "./../ShapeStrategies/IFigure.h"
#include "./../ICanvas.h"
#include "../../Infrastructure/Events/MouseMovedEvent.h"
#include "../../Presentor/IInteractionEvent.h"


namespace view {
    class VShape {
    public:
        VShape(std::string id, const uint32_t &color, std::unique_ptr<IFigure> figure,
               std::unique_ptr<Presenter::PShape> &presenter)
            : m_id(std::move(id)),
              m_color(color),
              m_figure(std::move(figure)),
              m_presenter(presenter) {
        }


        [[nodiscard]] std::string GetId() const {
            return m_id;
        }

        void SetId(const std::string &id) {
            m_id = id;
        }

        [[nodiscard]] uint32_t GetColor() const {
            return m_color;
        }

        void SetColor(uint32_t color) {
            m_color = color;
        }

        [[nodiscard]] IFigure &GetFigure() {
            return *m_figure;
        }

        void SetFigure(std::unique_ptr<IFigure> figure) {
            this->m_figure = move(figure);
        }

        void SetSelected(bool selected) {
            m_isSelected = selected;
        }

        void Draw(std::unique_ptr<ICanvas> &canvas) const {
            try {
                m_figure->Draw(0x000000FF, canvas, m_isSelected);
            } catch (const std::exception &e) {
                std::cout << e.what() << std::endl;
            }
        }

        void Notify(const std::shared_ptr<Presenter::IInteractionEvent> &event) {
            switch (event->GetInteractionType()) {
                case ViewInteractionType::MouseDown:
                {
                    m_prevEventType = ViewInteractionType::MouseDown;
                    if (const auto mouseDownEvent = std::dynamic_pointer_cast<MouseDownEvent>(event)) {
                        m_clickPosition = mouseDownEvent->GetPosition();
                        if (mouseDownEvent->IsDragging()) {
                            break;
                        }
                    }
                    break;
                }
                case ViewInteractionType::MouseUp: {
                    if (m_prevEventType == ViewInteractionType::MouseMove) {
                        break;
                    }
                    m_prevEventType = ViewInteractionType::MouseUp;
                    const auto mouseUpEvent = std::dynamic_pointer_cast<MouseUpEvent>(event);
                    if (mouseUpEvent->IsCtrlPressed()) {
                        m_presenter->AddToSelection(m_id);
                    }
                    else {
                        m_presenter->Select(m_id);
                    }
                    break;
                }
                case ViewInteractionType::MouseMove: {
                    m_prevEventType = ViewInteractionType::MouseMove;
                    auto mouseMoveEvent = std::dynamic_pointer_cast<MouseMovedEvent>(event);
                    if (!mouseMoveEvent->IsMouseButtonPressed()) {
                        break;
                    }
                    Point offset = {m_clickPosition.x - mouseMoveEvent->GetPosition().x, m_clickPosition.y - mouseMoveEvent->GetPosition().y};
                    m_clickPosition = mouseMoveEvent->GetPosition();
                    // if (m_figure->IsOnEditSquare(m_clickPosition)) {
                    //     m_presenter->Update(UpdateType::Resize, {}, offset.y, offset.x);
                    // }
                    // else if (m_figure->PointInFigure(m_clickPosition)) {
                        m_presenter->Update(UpdateType::Move, offset, 0, 0);
                    // }
                    break;
                }
                case ViewInteractionType::DeleteButtonPress: {
                    m_presenter->Delete();
                    break;
                }
                default: return;
            }
        }

    private:
        std::string m_id;
        uint32_t m_color;
        std::unique_ptr<IFigure> m_figure;
        std::unique_ptr<Presenter::PShape> &m_presenter;
        Point m_clickPosition;
        bool m_isSelected;
        ViewInteractionType m_prevEventType;
    };
}
#endif //VSHAPE_H
