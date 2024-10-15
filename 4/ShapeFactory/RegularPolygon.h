//
// Created by ilya.lezhnin on 18.09.24.
//

#ifndef REGULARPOLYGON_H
#define REGULARPOLYGON_H

#include <utility>
#include <vector>

#include "./../Draft/Point.h"
#include "./../Draft/Shape.h"


class RegularPolygon : public Shape
{
public:
    RegularPolygon(const Color color, std::vector<Point> vertices) :
        Shape(color),
        m_vertices(std::move(vertices))
    {
    }

    ~RegularPolygon() override = default;

    void Draw(ICanvas& canvas) override
    {
        canvas.SetColor(m_color);
        Point currentPoint{};
        Point nextPoint{};
        for (int i = 0; i < m_vertices.size()-1; i++)
        {
            currentPoint = m_vertices[i];
            nextPoint = m_vertices[i+1];
            canvas.DrawLine(currentPoint, nextPoint);
        }
        currentPoint = m_vertices.back();
        nextPoint = m_vertices[0];
        canvas.DrawLine(currentPoint, nextPoint);
    }

    [[nodiscard]]  std::vector<Point> GetVertices() const
    {
        return m_vertices;
    }
private:
    std::vector<Point> m_vertices;
};


#endif //REGULARPOLYGON_H
