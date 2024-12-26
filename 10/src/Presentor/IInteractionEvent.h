//
// Created by flipd on 25.12.2024.
//

#ifndef IINTERACTIONEVENT_H
#define IINTERACTIONEVENT_H
#include <string>

#include "../Common/CommonStructs.h"

namespace Presenter {
    struct EventData {
        ViewInteractionType actionType;
        std::string data;
    };

    class IInteractionEvent {
        public:
            virtual ~IInteractionEvent() = default;
            virtual ViewInteractionType GetInteractionType() = 0;
            virtual EventData GetEventData() = 0;
            virtual void SetEventData(EventData eventData) = 0;
    };
}
#endif //IINTERACTIONEVENT_H
