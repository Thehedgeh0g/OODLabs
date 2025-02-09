//
// Created by flipd on 08.01.2025.
//

#ifndef MOVESELECTEDEVENT_H
#define MOVESELECTEDEVENT_H
#include <string>

#include "../../Common/CommonStructs.h"

namespace View {
    class ResizeSelectedEvent {
    public:
        explicit ResizeSelectedEvent(std::string shapeId, double xOffset, double yOffset): m_shapeId(std::move(shapeId)), m_offset({xOffset, yOffset})
        {
        };

        std::string GetShapeId() {
            return m_shapeId;
        }
        Point GetOffset() {
            return m_offset;
        }

    private:
        std::string m_shapeId;
        Point m_offset;
    };
}
#endif //MOVESELECTEDEVENT_H
