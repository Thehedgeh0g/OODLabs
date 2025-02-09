//
// Created by flipd on 08.01.2025.
//

#ifndef UNDOKEYSPRESSEDEVENT_H
#define UNDOKEYSPRESSEDEVENT_H
#include "../../Presentor/IInteractionEvent.h"

class UndoKeysPressedEvent : public Presenter::IInteractionEvent{
public:
    explicit UndoKeysPressedEvent() {
        m_interactionType = ViewInteractionType::UndoButtonsPressed;
    };

    ViewInteractionType GetInteractionType() override {
        return m_interactionType;
    }

private:
    ViewInteractionType m_interactionType = ViewInteractionType::UndoButtonsPressed;
};

#endif //UNDOKEYSPRESSEDEVENT_H
