//
// Created by flipd on 08.01.2025.
//

#ifndef DELETEKEYSPRESSEDEVENT_H
#define DELETEKEYSPRESSEDEVENT_H
#include "../../Presentor/IInteractionEvent.h"

class DeleteKeysPressedEvent : public Presenter::IInteractionEvent{
public:
    explicit DeleteKeysPressedEvent() = default;

    ViewInteractionType GetInteractionType() override {
        return m_interactionType;
    }

private:
    ViewInteractionType m_interactionType = ViewInteractionType::DeleteButtonPress;
};

#endif //DELETEKEYSPRESSEDEVENT_H
