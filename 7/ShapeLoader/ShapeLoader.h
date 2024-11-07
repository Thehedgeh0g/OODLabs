//
// Created by thehedgeh0g on 06.11.24.
//

#ifndef SHAPELOADER_H
#define SHAPELOADER_H
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include "../Shape/Shape.h"
#include "../Shape/Rectangle.h"
#include "../Shape/Triangle.h"
#include "../Shape/Ellipse.h"
#include "../Shape/Group.h"

class ShapeLoader {
public:
    static std::vector<std::shared_ptr<Shape>> loadShapesFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file: " + filename);
        }

        return loadShapes(file);
    }

private:
    static std::vector<std::shared_ptr<Shape>> loadShapes(std::istream& input) {
        std::vector<std::shared_ptr<Shape>> shapes;
        std::string line;

        while (std::getline(input, line)) {
            std::istringstream iss(line);
            std::string type;
            iss >> type;
            std::shared_ptr<Shape> shape = nullptr;
            std::string fillColor, outlineColor;
            double lineThickness;

            if (type == "rectangle") {
                int x, y, width, height;
                iss >> x >> y >> width >> height >> fillColor >> outlineColor >> lineThickness;
                shape = std::make_shared<Rectangle>(x, y, width, height);
                shape->SetFillStyle(FillStyle(true, fillColor));
                shape->SetLineStyle(LineStyle(true, outlineColor, lineThickness));
                shapes.push_back(shape);
            }
            else if (type == "ellipse") {
                double centerX, centerY, rx, ry;
                iss >> centerX >> centerY >> rx >> ry >> fillColor >> outlineColor >> lineThickness;
                shape = std::make_shared<Ellipse>(centerX, centerY, rx, ry);
                shape->SetFillStyle(FillStyle(true, fillColor));
                shape->SetLineStyle(LineStyle(true, outlineColor, lineThickness));
                shapes.push_back(shape);
            }
            else if (type == "triangle") {
                double x1, y1, x2, y2, x3, y3;
                iss >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> fillColor >> outlineColor >> lineThickness;
                shape = std::make_shared<Triangle>(Point(x1, y1), Point(x2, y2), Point(x3, y3));
                shape->SetFillStyle(FillStyle(true, fillColor));
                shape->SetLineStyle(LineStyle(true, outlineColor, lineThickness));
                shapes.push_back(shape);
            }
            else if (type == "group") {
                auto group = std::make_shared<Group>();
                auto groupShapes = loadShapes(input);

                for (const auto& shapeInGroup : groupShapes) {
                    group->AddShape(shapeInGroup);
                }
                shapes.push_back(group);
            }
            else if (type == "endgroup") {
                return shapes;
            }
            else {
                throw std::runtime_error("Unknown shape type: " + type);
            }
        }

        return shapes;
    }
};


#endif //SHAPELOADER_H
