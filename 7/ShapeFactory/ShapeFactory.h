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
    std::unique_ptr<shapes::IShape> CreateShape(const std::string &description) override
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
    static std::unique_ptr<shapes::Triangle> CreateTriangle(
        std::istringstream &iss,
        std::unique_ptr<style::IStyle> outlineStyle,
        std::unique_ptr<style::IStyle> fillStyle
    )
    {
        const auto rect = ParseRect(iss);

        return std::make_unique<shapes::Triangle>(
            rect,
            std::move(outlineStyle),
            std::move(fillStyle)
        );
    }

    static std::unique_ptr<shapes::Ellipse> CreateEllipse(
        std::istringstream &iss,
        std::unique_ptr<style::IStyle> outlineStyle,
        std::unique_ptr<style::IStyle> fillStyle
    )
    {
        const auto rect = ParseRect(iss);

        return std::make_unique<shapes::Ellipse>(rect, std::move(outlineStyle), std::move(fillStyle));
    }

    static std::unique_ptr<shapes::Rectangle> CreateRectangle(
        std::istringstream &iss,
        std::unique_ptr<style::IStyle> outlineStyle,
        std::unique_ptr<style::IStyle> fillStyle
    )
    {
        const auto rect = ParseRect(iss);

        return std::make_unique<shapes::Rectangle>(rect, std::move(outlineStyle), std::move(fillStyle));
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
            std::cout << "Found error in color: \"" << e.what() << "\" color for shape not set" << std::endl;
            return std::make_unique<style::Style>(std::nullopt);
        }
    }

    static RectD ParseRect(std::istringstream &iss)
    {
        double left, top, width, height;

        if (!(iss >> left >> top >> width >> height))
        {
            throw std::invalid_argument("Invalid rect parameters");
        }

        if (width < 0 || height < 0)
        {
            throw std::invalid_argument("Width and height must be non-negative");
        }

        return {left, top, width, height};
    }
};
}
#endif //SHAPEFACTORY_H
