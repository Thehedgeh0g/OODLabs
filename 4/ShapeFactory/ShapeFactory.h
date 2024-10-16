//
// Created by ilya.lezhnin on 18.09.24.
//

#ifndef FIGUREBUILDER_H
#define FIGUREBUILDER_H
#include <memory>
#include <unordered_map>
#include <vector>

#include "./../Draft/Shape.h"
#include "./IShapeFactory.h"
#include "Ellipse.h"
#include "Rectangle.h"
#include "RegularPolygon.h"
#include "ShapeNames.h"
#include "Triangle.h"

class ShapeFactory : public IShapeFactory
{
public:
    [[nodiscard]] std::unique_ptr<Shape> CreateShape(std::string shapeData) const override
    {
        size_t pos;
        std::vector<std::string> shapeParams;
        while ((pos = shapeData.find(DATA_DELIMITER)) != std::string::npos)
        {
            std::string token = shapeData.substr(0, pos);
            shapeParams.push_back(token);
            shapeData.erase(0, pos + DATA_DELIMITER.length());
        }
        shapeParams.push_back(shapeData);

        if (const auto it = m_figureMap.find(shapeParams[0]); it != m_figureMap.end())
        {
            switch (it->second)
            {
                case static_cast<int>(ShapeNames::Ellipse):
                    return BuildEllipse(shapeParams);
                case static_cast<int>(ShapeNames::RegularPolygon):
                    return BuildRegularPolygon(shapeParams);
                case static_cast<int>(ShapeNames::Rectangle):
                    return BuildRectangle(shapeParams);
                case static_cast<int>(ShapeNames::Triangle):
                    return BuildTriangle(shapeParams);
                default:
                    return nullptr;
            }
        }
        return nullptr;
    }

    ~ShapeFactory() override = default;

protected:
    Color GetColorByString(const std::string &colorString) const
    {
        if (const auto it = m_colorMap.find(colorString); it != m_colorMap.end())
        {
            switch (it->second)
            {
                case 0:
                    return Color::Red;
                case 1:
                    return Color::Green;
                case 2:
                    return Color::Blue;
                case 3:
                    return Color::Yellow;
                case 4:
                    return Color::Pink;
                case 5:
                    return Color::Black;
                default:
                    throw std::invalid_argument("Invalid color string");
            }
        }
        throw std::invalid_argument("Invalid color string");
    }

    [[nodiscard]] std::unique_ptr<Shape> BuildEllipse(const std::vector<std::string> &circleInput) const
    {
        return std::make_unique<Ellipse>(
            Ellipse(
                GetColorByString(circleInput[1]),
                {
                    std::stod(circleInput[2]), std::stod(circleInput[3])
                },
                std::stod(circleInput[4]), std::stod(circleInput[5])
            )
        );
    }

    [[nodiscard]] std::unique_ptr<Shape> BuildRegularPolygon(const std::vector<std::string> &polygonInput) const
    {
        std::vector<Point> vertices;
        for (size_t i = 2; i < polygonInput.size() - 1; i++)
        {
            vertices.emplace_back(Point{std::stod(polygonInput[i]), std::stod(polygonInput[i + 1])});
        }
        return std::make_unique<RegularPolygon>(
            RegularPolygon(
                GetColorByString(polygonInput[1]),
                vertices
            )
        );
    }

    [[nodiscard]] std::unique_ptr<Shape> BuildRectangle(const std::vector<std::string> &rectangleInput) const
    {
        return std::make_unique<Rectangle>(
            Rectangle(
                GetColorByString(rectangleInput[1]),
                {std::stod(rectangleInput[2]), std::stod(rectangleInput[3])},
                {std::stod(rectangleInput[4]), std::stod(rectangleInput[5])}
            )
        );
    }

    [[nodiscard]] std::unique_ptr<Shape> BuildTriangle(const std::vector<std::string> &triangleInput) const
    {
        return std::make_unique<Triangle>(
            Triangle(
                GetColorByString(triangleInput[1]),
                Point(std::stod(triangleInput[2]), std::stod(triangleInput[3])),
                Point(std::stod(triangleInput[4]), std::stod(triangleInput[4])),
                Point(std::stod(triangleInput[6]), std::stod(triangleInput[7]))
            )
        );
    }

    const std::string DATA_DELIMITER = " ";

    std::unordered_map<std::string, int> m_figureMap = {
        {"ellipse", 0},
        {"rectangle", 1},
        {"triangle", 2},
        {"polygon", 3},
    };

    std::unordered_map<std::string, int> m_colorMap = {
        {"red", 0},
        {"green", 1},
        {"blue", 2},
        {"pink", 3},
        {"yellow", 4},
        {"black", 5},
    };
};

#endif //FIGUREBUILDER_H
