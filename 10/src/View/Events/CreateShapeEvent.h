//
// Created by flipd on 08.01.2025.
//

#ifndef CREATESHAPEEVENT_H
#define CREATESHAPEEVENT_H
#include "../../Common/CommonStructs.h"

namespace View {
    class CreateShapeEvent {
    public:
        CreateShapeEvent(ShapeType shapeType, double x, double y, double width, double height):
            m_shapeType(shapeType),
            m_position({x, y}),
            m_width(width),
            m_height(height)
        {
        };

        ShapeType GetType() {
            return m_shapeType;
        }

        Point GetPosition() {
            return m_position;
        }

        double GetWidth() {
            return m_width;
        }

        double GetHeight() {
            return m_height;
        }

    private:
        ShapeType m_shapeType;
        Point m_position;
        double m_width;
        double m_height;
    };
}

#endif //CREATESHAPEEVENT_H
