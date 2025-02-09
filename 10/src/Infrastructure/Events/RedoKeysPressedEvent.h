//
// Created by flipd on 08.01.2025.
//

#ifndef REDOKEYSPRESSEDEVENT_H
#define REDOKEYSPRESSEDEVENT_H

#include "../../Presentor/IInteractionEvent.h"

class RedoKeysPressedEvent : public Presenter::IInteractionEvent{
public:
    explicit RedoKeysPressedEvent() = default;

    ViewInteractionType GetInteractionType() override {
        return m_interactionType;
    }

private:
    ViewInteractionType m_interactionType = ViewInteractionType::RedoButtonsPressed;
};

#endif //REDOKEYSPRESSEDEVENT_H
