//
// Created by flipd on 08.01.2025.
//

#ifndef ADDSHAPETOSELECTEVENT_H
#define ADDSHAPETOSELECTEVENT_H
#include <string>

namespace View {
    class AddSelectShapeEvent {
    public:
        explicit AddSelectShapeEvent(std::string shapeId): m_shapeId(std::move(shapeId)) {
        };

        std::string GetShapeId() {
            return m_shapeId;
        }

    private:
        std::string m_shapeId;
    };
}
#endif //ADDSHAPETOSELECTEVENT_H
