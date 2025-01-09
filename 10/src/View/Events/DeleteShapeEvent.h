//
// Created by flipd on 08.01.2025.
//

#ifndef DELETESHAPEEVENT_H
#define DELETESHAPEEVENT_H
#include <string>
#include <utility>

namespace View {
    class DeleteShapeEvent {
    public:
        explicit DeleteShapeEvent(std::string shapeId): m_shapeId(std::move(shapeId)) {
        };

        std::string GetShapeId() {
            return m_shapeId;
        }

    private:
        std::string m_shapeId;
    };
}

#endif //DELETESHAPEEVENT_H
