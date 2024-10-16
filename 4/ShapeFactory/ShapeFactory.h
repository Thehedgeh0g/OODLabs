//
// Created by ilya.lezhnin on 18.09.24.
//

#ifndef FIGUREBUILDER_H
#define FIGUREBUILDER_H
#include <memory>
#include <unordered_map>
#include <vector>

#include "./../Shape/Shape.h"
#include "./IShapeFactory.h"
#include "../Shape/Ellipse.h"
#include "../Shape/Rectangle.h"
#include "../Shape/RegularPolygon.h"
#include "../Shape/ShapeNames.h"
#include "../Shape/Triangle.h"

namespace Factory
{
    class ShapeFactory : public IShapeFactory
    {
    public:
        std::unique_ptr<shape::Shape> CreateShape(std::string shapeData) const override
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

            auto it = m_figureMap.find(shapeParams[0]);
            if (it != m_figureMap.end())
            {
                if (it->second == "ellipse")
                    return BuildEllipse(shapeParams);
                if (it->second == "polygon")
                    return BuildRegularPolygon(shapeParams);
                if (it->second == "rectangle")
                    return BuildRectangle(shapeParams);
                if (it->second == "triangle")
                    return BuildTriangle(shapeParams);
            }
            throw std::invalid_argument("Unknown shape");
        }

        ~ShapeFactory() override = default;

    protected:
        [[nodiscard]] static std::unique_ptr<shape::Shape> BuildEllipse(const std::vector<std::string> &circleInput)
        {
            return std::make_unique<shape::Ellipse>(
                shape::Ellipse(
                    shape::convertToColor(circleInput[1]),
                    {
                        std::stod(circleInput[2]), std::stod(circleInput[3])
                    },
                    std::stod(circleInput[4]), std::stod(circleInput[5])
                )
            );
        }

        [[nodiscard]] static std::unique_ptr<shape::Shape> BuildRegularPolygon(
            const std::vector<std::string> &polygonInput)
        {
            std::vector<shape::Point> vertices;
            for (size_t i = 2; i < polygonInput.size() - 1; i += 2)
            {
                vertices.emplace_back(shape::Point{std::stod(polygonInput[i]), std::stod(polygonInput[i + 1])});
            }
            return std::make_unique<shape::RegularPolygon>(
                shape::RegularPolygon(
                    shape::convertToColor(polygonInput[1]),
                    vertices
                )
            );
        }

        [[nodiscard]] static std::unique_ptr<shape::Shape> BuildRectangle(
            const std::vector<std::string> &rectangleInput)
        {
            return std::make_unique<shape::Rectangle>(
                shape::Rectangle(
                    shape::convertToColor(rectangleInput[1]),
                    {std::stod(rectangleInput[2]), std::stod(rectangleInput[3])},
                    {std::stod(rectangleInput[4]), std::stod(rectangleInput[5])}
                )
            );
        }

        [[nodiscard]] static std::unique_ptr<shape::Shape> BuildTriangle(const std::vector<std::string> &triangleInput)
        {
            return std::make_unique<shape::Triangle>(
                shape::Triangle(
                    shape::convertToColor(triangleInput[1]),
                    {std::stod(triangleInput[2]), std::stod(triangleInput[3])},
                    {std::stod(triangleInput[4]), std::stod(triangleInput[5])},
                    {std::stod(triangleInput[6]), std::stod(triangleInput[7])}
                )
            );
        }

        const std::string DATA_DELIMITER = " ";

        std::unordered_map<std::string, std::string> m_figureMap = {
            {"ellipse", "ellipse"},
            {"rectangle", "rectangle"},
            {"polygon", "polygon"},
            {"triangle", "triangle"},
        };
    };
}

#endif //FIGUREBUILDER_H
