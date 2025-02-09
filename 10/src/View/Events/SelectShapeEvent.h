//
// Created by flipd on 08.01.2025.
//

#ifndef SELECTSHAPEEVENT_H
#define SELECTSHAPEEVENT_H
#include <string>

namespace View {
    class MoveSelectedEvent {
    public:
        explicit MoveSelectedEvent(std::string shapeId): m_shapeId(std::move(shapeId)) {
        };

        std::string GetShapeId() {
            return m_shapeId;
        }

    private:
        std::string m_shapeId;
    };
}

#endif //SELECTSHAPEEVENT_H
