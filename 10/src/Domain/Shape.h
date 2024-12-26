//
// Created by flipd on 24.12.2024.
//

#ifndef SHAPE_H
#define SHAPE_H
#include <string>
#include <boost/signals2/signal.hpp>

#include "./../Common/CommonStructs.h"
#include "./IdGenerator.h"

class Shape {
private:
    std::string m_id;
    ShapeType m_type;
    RectD m_frame;
    uint32_t m_color;

public:
    Shape(
        const ShapeType type,
        const RectD &frame,
        const uint32_t color
    ):  m_id(IdGenerator::GenerateId()),
        m_type(type),
        m_frame(frame),
        m_color(color)
    {
    }

    Shape(const Shape &other) {
        m_id = other.m_id;
        m_type = other.m_type;
        m_frame = other.m_frame;
        m_color = other.m_color;
    }

    [[nodiscard]] const std::string &GetId() const { return m_id; }
    [[nodiscard]] ShapeType GetType() const { return m_type; }

    void SetPosition(const Point point) {
        m_frame.point = point;
        m_frameChanged(m_frame, m_id);
    }

    void GetPosition(Point &point) const {
        point = m_frame.point;
    }

    [[nodiscard]] RectD GetFrame() const { return m_frame; }

    void SetSize(const double width, const double height) {
        m_frame.width = width;
        m_frame.height = height;
        m_frameChanged(m_frame, m_id);
    }

    void GetSize(double &width, double &height) const {
        width = m_frame.width;
        height = m_frame.height;
    }

    void SetColor(uint32_t color) { m_color = color; }
    [[nodiscard]] uint32_t GetColor() const { return m_color; }

    bool operator ==(const Shape &other) const {
        return m_id == other.m_id;
    }

    bool operator !=(const Shape &other) const {
        return m_id != other.m_id;
    }

    boost::signals2::connection DoOnShapeChanged(const std::function<void(const RectD &, const std::string&)> &handler) {
        return m_frameChanged.connect(handler);
    }

private:
    boost::signals2::signal<void(const RectD &, const std::string&)> m_frameChanged;
};

#endif //SHAPE_H
