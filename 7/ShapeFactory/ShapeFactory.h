//
// Created by thehedgeh0g on 11.11.24.
//

#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H
#include <iostream>
#include <sstream>

#include "IShapeFactory.h"
#include "./../Shape/Ellipse.h"
#include "./../Shape/Rectangle.h"
#include "./../Shape/Triangle.h"
#include "./../Shape/Point.h"

namespace shapeFactory
{
class ShapeFactory : public IShapeFactory
{
public:
    std::shared_ptr<shapes::IShape> CreateShape(const std::string &description) override
    {
        std::istringstream iss(description);

        std::string shapeType;
        iss >> shapeType;

        auto outlineStyle = ParseStyle(iss);
        auto fillStyle = ParseStyle(iss);

        if (shapeType == "triangle")
        {
            return CreateTriangle(iss, std::move(outlineStyle), std::move(fillStyle));
        }
        if (shapeType == "ellipse")
        {
            return CreateEllipse(iss, std::move(outlineStyle), std::move(fillStyle));
        }
        if (shapeType == "rectangle")
        {
            return CreateRectangle(iss, std::move(outlineStyle), std::move(fillStyle));
        }

        throw std::invalid_argument("Unknown shape type");
    }

private:
    static std::shared_ptr<shapes::Triangle> CreateTriangle(
        std::istringstream &iss,
        std::unique_ptr<style::IStyle> outlineStyle,
        std::unique_ptr<style::IStyle> fillStyle
    )
    {
        double x1, y1, x2, y2, x3, y3;
        iss >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

        return std::make_unique<shapes::Triangle>(
            shapes::Point(x1, y1),
            shapes::Point(x2, y2),
            shapes::Point(x3, y3),
            std::move(outlineStyle),
            std::move(fillStyle)
        );
    }

    static std::shared_ptr<shapes::Ellipse> CreateEllipse(
        std::istringstream &iss,
        std::unique_ptr<style::IStyle> outlineStyle,
        std::unique_ptr<style::IStyle> fillStyle
    )
    {
        double centerX, centerY, rx, ry;
        iss >> centerX >> centerY >> rx >> ry;

        return std::make_unique<shapes::Ellipse>(shapes::Point(centerX, centerY), rx, ry, std::move(outlineStyle), std::move(fillStyle));
    }

    static std::shared_ptr<shapes::Rectangle> CreateRectangle(
        std::istringstream &iss,
        std::unique_ptr<style::IStyle> outlineStyle,
        std::unique_ptr<style::IStyle> fillStyle
    )
    {
        int x, y, width, height;
        iss >> x >> y >> width >> height;

        return std::make_unique<shapes::Rectangle>(x, y, width, height, std::move(outlineStyle), std::move(fillStyle));
    }

    static std::unique_ptr<style::IStyle> ParseStyle(std::istringstream &iss)
    {
        std::string colorStr;
        iss >> colorStr;
        try
        {
            style::Color color(colorStr);

            auto style = std::make_unique<style::Style>(color);
            style->Enable(true);

            return style;
        }
        catch (const std::invalid_argument &e)
        {
            std::cout << "Found error in color: \"" <<e.what()  << "\" color for shape not set" << std::endl;
            return std::make_unique<style::Style>(std::nullopt);
        }
    }
};
}
#endif //SHAPEFACTORY_H
