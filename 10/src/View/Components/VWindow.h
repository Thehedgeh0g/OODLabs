//
// Created by flipd on 25.12.2024.
//

#ifndef VWINDOW_H
#define VWINDOW_H
#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "VMenu.h"
#include "VShape.h"
#include "../../Common/CommonStructs.h"
#include "../../Infrastructure/Events/MouseDownEvent.h"
#include "../../Infrastructure/Events/MouseMovedEvent.h"
#include "../../Infrastructure/Events/MouseUpEvent.h"
#include "../../Presentor/IInteractionEvent.h"
#include "../ShapeStrategies/Circle.h"
#include "../ShapeStrategies/Rectangle.h"
#include "../ShapeStrategies/Triangle.h"

namespace view {
    class VWindow {
    public:
        explicit VWindow(
            std::unique_ptr<ICanvas> &canvas,
            std::unique_ptr<VMenu> menu,
            std::unique_ptr<Presenter::PDraft> draftPresenter,
            std::unique_ptr<Presenter::PShape> &shapePresenter,
            std::unique_ptr<App::DraftContainer> &draftContainer,
            const std::unique_ptr<App::SubscriptionContainer> &subscriptionContainer
        ): m_canvas(canvas),
           m_menu(std::move(menu)),
           m_draftPresenter(std::move(draftPresenter)),
           m_draftContainer(draftContainer),
           m_shapePresenter(shapePresenter),
           m_subscriptionContainer(subscriptionContainer) {
            subscriptionContainer->SubscribeOnShapeCreated(
                draftContainer->GetDraft(),
                [this](
                    const RectD &frame,
                    const std::string &id,
                    const uint32_t &color,
                    const ShapeType &shapeType
                ) {
                    this->DoOnShapeCreated(frame, id, color, shapeType);
                }
            );
            subscriptionContainer->SubscribeOnShapeDeleted(
                draftContainer->GetDraft(),
                [this](
                    const std::string &id
                ) {
                    this->DoOnShapeDeleted(id);
                }
            );
            subscriptionContainer->SubscribeOnSelectionChanged(
                draftContainer->GetShapeSelection(), [this](
                    const std::string &id
                ) {
                    this->DoOnSelectionChanged(id);
                }
            );
        };

        ~VWindow() = default;

        void Draw() {
            m_menu->Draw(m_canvas);
            for (auto &shape: m_shapes) {
                shape.second->Draw(m_canvas);
            }
        }

        void AddShape(const std::string &shapeId, const RectD &frame, uint32_t color, const ShapeType &shapeType) {
            std::unique_ptr<IFigure> newFigure = nullptr;
            switch (shapeType) {
                case ShapeType::Circle: {
                    newFigure = std::make_unique<Circle>(frame);
                    break;
                }
                case ShapeType::Triangle: {
                    newFigure = std::make_unique<Triangle>(frame);
                    break;
                }
                case ShapeType::Rectangle: {
                    newFigure = std::make_unique<Rectangle>(frame);
                    break;
                }
                default: { throw std::invalid_argument("Invalid shape type"); }
            }
            auto newShape = std::make_unique<VShape>(shapeId, color, std::move(newFigure), m_shapePresenter);
            m_shapes.insert({shapeId, std::move(newShape)});
        }

        void DeleteShape(const std::string &shapeId) {
            m_draftContainer->GetShapeSelection().RemoveSelectedShape(shapeId);
            auto selectedIt = std::find(m_selectedShapes.begin(), m_selectedShapes.end(), shapeId);
            if (selectedIt != m_selectedShapes.end()) {
                m_selectedShapes.erase(selectedIt);
            }
            auto it = m_shapes.find(shapeId);
            if (it != m_shapes.end()) {
                m_shapes.erase(it);
            }
        }

        void ModifyShape(const std::string &shapeId, uint32_t color, const RectD &frame) {
            auto it = m_shapes.find(shapeId);
            if (it != m_shapes.end()) {
                it->second->SetColor(color);
                it->second->GetFigure().UpdateFrame(frame);
            }
        }

        void Notify(const std::shared_ptr<Presenter::IInteractionEvent> &event) {
            if (event == nullptr) {
                return;
            }
            switch (event->GetInteractionType()) {
                case ViewInteractionType::MouseDown: {
                    auto concreteEvent = std::dynamic_pointer_cast<MouseDownEvent>(event);
                    std::string shapeId = DetermineViewComponentByPoint(concreteEvent->GetPosition());
                    auto it = m_shapes.find(shapeId);
                    if (it != m_shapes.end()) {
                        it->second->Notify(event);
                        break;
                    }
                    m_menu->Notify(event);
                    break;
                }
                case ViewInteractionType::DeleteButtonPress:{
                    for (auto &shapeId: m_selectedShapes) {
                        if (auto it = m_shapes.find(shapeId); it != m_shapes.end()) {
                            it->second->Notify(event);
                        }
                    }
                    break;
                }
                case ViewInteractionType::MouseMove: {
                    for (auto &shapeId: m_selectedShapes) {
                        if (auto it = m_shapes.find(shapeId); it != m_shapes.end()) {
                            auto concreteEvent = std::dynamic_pointer_cast<MouseMovedEvent>(event);
                            it->second->Notify(concreteEvent);
                        }
                    }
                    break;
                }
                case ViewInteractionType::MouseUp: {
                    auto concreteEvent = std::dynamic_pointer_cast<MouseUpEvent>(event);
                    std::string shapeId = DetermineViewComponentByPoint(concreteEvent->GetPosition());
                    auto it = m_shapes.find(shapeId);
                    if (it != m_shapes.end()) {
                        it->second->Notify(event);
                        break;
                    }
                    break;
                }
                case ViewInteractionType::UndoButtonsPressed: {
                    m_draftPresenter->Undo();
                    break;
                }
                case ViewInteractionType::RedoButtonsPressed: {
                    m_draftPresenter->Redo();
                    break;
                }
                default:
                    return;
            }
        }

    private:
        [[nodiscard]] std::string DetermineViewComponentByPoint(const Point &point) const {
            for (auto &shape: m_shapes) {
                if (shape.second->GetFigure().IsPointInFrame(point)) {
                    return shape.first;
                }
            }
            return "";
        }

        void DoOnShapeCreated(const RectD &frame,
                              const std::string &id,
                              const uint32_t &color,
                              const ShapeType &shapeType
        ) {
            AddShape(id, frame, color, shapeType);
            try {
                m_subscriptionContainer->SubscribeOnShape(
                    m_draftContainer->GetDraft(),
                    id,
                    [this](
                const RectD &frame,
                const std::string &id
            ) {
                        this->DoOnShapeChanged(frame, id);
                    }
                );
            } catch (const std::exception &e) {
                std::cout << e.what() << std::endl;
            }
        }

        void DoOnShapeChanged(const RectD &frame, const std::string &id) {
            ModifyShape(id, 0x000000FF, frame);
        }

        void DoOnShapeDeleted(const std::string &id) {
            DeleteShape(id);
        }

        void DoOnSelectionChanged(const std::string &id) {
            auto it = std::find(m_selectedShapes.begin(), m_selectedShapes.end(), id);
            if (it == m_selectedShapes.end() && !m_draftContainer->GetShapeSelection().IsSelectedShape(id)) {
                m_selectedShapes.push_back(id);
                m_shapes.find(id)->second->SetSelected(true);
            } else {
                m_shapes.find(id)->second->SetSelected(false);
                m_selectedShapes.erase(it);
            }
        }

        std::map<std::string, std::unique_ptr<VShape> > m_shapes;
        std::vector<std::string> m_selectedShapes;
        std::unique_ptr<VMenu> m_menu;
        std::unique_ptr<ICanvas> &m_canvas;
        std::unique_ptr<Presenter::PDraft> m_draftPresenter;
        std::unique_ptr<Presenter::PShape> &m_shapePresenter;
        std::unique_ptr<App::DraftContainer> &m_draftContainer;
        const std::unique_ptr<App::SubscriptionContainer> &m_subscriptionContainer;
        std::vector<std::shared_ptr<Presenter::PShape> > m_shapeViewPresenters;
    };
}
#endif //VWINDOW_H
