//
// Created by thehedgeh0g on 06.11.24.
//
#include <gtest/gtest.h>
#include <sstream>

#include "../Shape/Point.h"
#include "../Shape/Rectangle.h"
#include "../Shape/Ellipse.h"
#include "../Shape/Triangle.h"
#include "../Shape/Group.h"
#include "../Canvas/ConsoleCanvas.h"
#include "../ShapeFactory/ShapeFactory.h"

TEST(RectangleTest, DrawWithStylesEnabled)
{
    std::ostringstream output;
    auto canvas = std::make_shared<ConsoleCanvas>(output);

    // Новый формат создания фигуры через фабрику
    shapeFactory::ShapeFactory factory;
    auto shape = factory.CreateShape("rectangle #FF0000FF #0000FFFF 10 20 30 40");

    shape->GetFillStyle().Enable(true);
    shape->GetOutlineStyle().Enable(true);
    shape->Draw(canvas);

    std::string expectedOutput = "Setting fill color to: r: 0; g:0; b:255; a:255\n"
            "Filling polygon with points: (10, 20) (40, 20) (40, 60) (10, 60) \n"
            "Setting line color to: r: 255; g:0; b:0; a:255\n"
            "Drawing line from (10, 20) to (40, 20)\n"
            "Drawing line from (40, 20) to (40, 60)\n"
            "Drawing line from (40, 60) to (10, 60)\n"
            "Drawing line from (10, 60) to (10, 20)\n";
    EXPECT_EQ(output.str(), expectedOutput);
}

TEST(RectangleTest, DrawWithStylesDisabled)
{
    std::ostringstream output;
    auto canvas = std::make_shared<ConsoleCanvas>(output);

    shapeFactory::ShapeFactory factory;
    auto shape = factory.CreateShape("rectangle #FF0000FF #0000FFFF 10 20 30 40");

    shape->GetFillStyle().Enable(false);
    shape->GetOutlineStyle().Enable(false);
    shape->Draw(canvas);

    std::string expectedOutput = "";
    EXPECT_EQ(output.str(), expectedOutput);
}

// Аналогичные изменения для тестов Ellipse и Triangle
TEST(EllipseTest, DrawWithStylesEnabled)
{
    std::ostringstream output;
    auto canvas = std::make_shared<ConsoleCanvas>(output);

    shapeFactory::ShapeFactory factory;
    auto shape = factory.CreateShape("ellipse #FF0000FF #0000FFFF 50 60 20 15");

    shape->GetFillStyle().Enable(true);
    shape->GetOutlineStyle().Enable(true);
    shape->Draw(canvas);

    std::string expectedOutput = "Setting line color to: r: 255; g:0; b:0; a:255\n"
            "Drawing ellipse with center (60, 52.5), horizontal radius 10 and vertical radius 7.5\n"
            "Setting fill color to: r: 0; g:0; b:255; a:255\n"
            "Filling ellipse at (60, 52.5) with width 20 and height 15\n";
    EXPECT_EQ(output.str(), expectedOutput);
}

TEST(TriangleTest, DrawWithStylesEnabled)
{
    std::ostringstream output;
    auto canvas = std::make_shared<ConsoleCanvas>(output);

    shapeFactory::ShapeFactory factory;
    auto shape = factory.CreateShape("triangle #FF0000FF #0000FFFF 0 0 10 0 5 10");

    shape->GetFillStyle().Enable(true);
    shape->GetOutlineStyle().Enable(true);
    shape->Draw(canvas);

    std::string expectedOutput = "Setting fill color to: r: 0; g:0; b:255; a:255\n"
            "Filling polygon with points: (5, 0) (0, 0) (10, 0) \n"
            "Setting line color to: r: 255; g:0; b:0; a:255\n"
            "Drawing line from (5, 0) to (0, 0)\n"
            "Drawing line from (0, 0) to (10, 0)\n"
            "Drawing line from (10, 0) to (5, 0)\n";
    EXPECT_EQ(output.str(), expectedOutput);
}

TEST(TriangleTest, DrawWithStylesDisabled)
{
    std::ostringstream output;
    auto canvas = std::make_shared<ConsoleCanvas>(output);


    shapeFactory::ShapeFactory factory;
    auto shape = factory.CreateShape("triangle #FF0000FF #0000FFFF 0 0 10 0 5 10");
    shape->GetFillStyle().Enable(false);
    shape->GetOutlineStyle().Enable(false);
    shape->Draw(canvas);

    std::string expectedOutput = "";
    EXPECT_EQ(output.str(), expectedOutput);
}

TEST(GroupTest, DrawGroup)
{
    std::ostringstream output;
    auto canvas = std::make_shared<ConsoleCanvas>(output);

    shapeFactory::ShapeFactory factory;
    auto triangle = factory.CreateShape("triangle #FF0000FF #0000FFFF 0 0 10 0 5 10");

    triangle->GetFillStyle().Enable(true);
    triangle->GetOutlineStyle().Enable(true);

    auto ellipse = factory.CreateShape("ellipse #FF0000FF #0000FFFF 50 60 20 15");

    ellipse->GetFillStyle().Enable(true);
    ellipse->GetOutlineStyle().Enable(true);

    shapes::Group group;

    group.InsertShape(std::move(ellipse), group.GetShapesCount());
    group.InsertShape(std::move(triangle), group.GetShapesCount());
    group.Draw(canvas);

    std::string expectedOutput = "Setting line color to: r: 255; g:0; b:0; a:255\n"
            "Drawing ellipse with center (60, 52.5), horizontal radius 10 and vertical radius 7.5\n"
            "Setting fill color to: r: 0; g:0; b:255; a:255\n"
            "Filling ellipse at (60, 52.5) with width 20 and height 15\n"
            "Setting fill color to: r: 0; g:0; b:255; a:255\n"
            "Filling polygon with points: (5, 0) (0, 0) (10, 0) \n"
            "Setting line color to: r: 255; g:0; b:0; a:255\n"
            "Drawing line from (5, 0) to (0, 0)\n"
            "Drawing line from (0, 0) to (10, 0)\n"
            "Drawing line from (10, 0) to (5, 0)\n";
    EXPECT_EQ(output.str(), expectedOutput);
}

TEST(GroupShapeTest, GetStyleGroupShape)
{
    shapeFactory::ShapeFactory factory;
    auto triangle = factory.CreateShape("triangle #FF0000FF #0000FFFF 0 0 10 0 5 10");

    triangle->GetFillStyle().Enable(true);
    triangle->GetOutlineStyle().Enable(true);

    auto ellipse = factory.CreateShape("ellipse #FF0000FF #0000FFFF 50 60 20 15");

    ellipse->GetFillStyle().Enable(true);
    ellipse->GetOutlineStyle().Enable(true);
    shapes::Group groupShape;

    groupShape.InsertShape(std::move(ellipse), 0);
    groupShape.InsertShape(std::move(triangle), 1);

    auto outlineStyleColor = groupShape.GetOutlineStyle().GetColor();
    bool isOutlineStyleColorNullopt = false;
    if (outlineStyleColor == std::nullopt)
    {
        isOutlineStyleColorNullopt = true;
    }
    auto fillStyleColor = groupShape.GetFillStyle().GetColor();
    bool isFillStyleColorNullopt = false;
    if (fillStyleColor == std::nullopt)
    {
        isFillStyleColorNullopt = true;
    }

    EXPECT_FALSE(isOutlineStyleColorNullopt);
    EXPECT_FALSE(isFillStyleColorNullopt);
}

TEST(GroupShapeTest, GetStyleGroupShapeWithDiffColors)
{
    shapeFactory::ShapeFactory factory;
    auto triangle = factory.CreateShape("triangle #FF00AAFF #AA00FFFF 0 0 10 0 5 10");

    triangle->GetFillStyle().Enable(true);
    triangle->GetOutlineStyle().Enable(true);

    auto ellipse = factory.CreateShape("ellipse #FF0000FF #0000FFFF 50 60 20 15");

    ellipse->GetFillStyle().Enable(true);
    ellipse->GetOutlineStyle().Enable(true);
    shapes::Group groupShape;

    groupShape.InsertShape(std::move(ellipse), 0);
    groupShape.InsertShape(std::move(triangle), 1);

    auto outlineStyleColor = groupShape.GetOutlineStyle().GetColor();
    bool isOutlineStyleColorNullopt = false;
    if (outlineStyleColor == std::nullopt)
    {
        isOutlineStyleColorNullopt = true;
    }
    auto fillStyleColor = groupShape.GetFillStyle().GetColor();
    bool isFillStyleColorNullopt = false;
    if (fillStyleColor == std::nullopt)
    {
        isFillStyleColorNullopt = true;
    }

    EXPECT_TRUE(isOutlineStyleColorNullopt);
    EXPECT_TRUE(isFillStyleColorNullopt);
}

TEST(GroupShapeTest, SetStyleGroupShape)
{
    style::Color expectedOutlineStyleColor('#FFAA00FF');
    style::Color expectedFillStyleColor('#00AAFFFF');
    shapeFactory::ShapeFactory factory;
    auto triangle = factory.CreateShape("triangle #FF00AAFF #AA00FFFF 0 0 10 0 5 10");
    triangle->GetFillStyle().Enable(true);
    triangle->GetOutlineStyle().Enable(true);

    auto ellipse = factory.CreateShape("ellipse #FF0000FF #0000FFFF 50 60 20 15");
    ellipse->GetFillStyle().Enable(true);
    ellipse->GetOutlineStyle().Enable(true);

    shapes::Group groupShape;

    groupShape.InsertShape(std::move(ellipse), 0);
    groupShape.InsertShape(std::move(triangle), 1);
    groupShape.GetOutlineStyle().SetColor(expectedOutlineStyleColor);
    groupShape.GetFillStyle().SetColor(expectedFillStyleColor);

    EXPECT_EQ(expectedOutlineStyleColor, groupShape.GetOutlineStyle().GetColor());
    EXPECT_EQ(expectedFillStyleColor, groupShape.GetFillStyle().GetColor());
}

TEST(GroupShapeTest, DrawEmptyGroup)
{
    std::ostringstream output;
    auto canvas = std::make_shared<ConsoleCanvas>(output);
    shapes::Group groupShape;
    groupShape.Draw(canvas);

    std::string expectedOutput = "";
    EXPECT_EQ(output.str(), expectedOutput);
}

TEST(GroupShapeTest, DrawGroupWithShapeAndEmptyGroup)
{
    std::ostringstream output;
    auto canvas = std::make_shared<ConsoleCanvas>(output);
    shapeFactory::ShapeFactory factory;

    auto groupWithShapes = std::make_unique<shapes::Group>();
    auto ellipse = factory.CreateShape("ellipse #FF0000FF #0000FFFF 50 60 20 15");
    ellipse->GetFillStyle().Enable(true);
    ellipse->GetOutlineStyle().Enable(true);
    auto emptyGroup = std::make_unique<shapes::Group>();
    groupWithShapes->InsertShape(std::move(ellipse), 0);
    groupWithShapes->InsertShape(std::move(emptyGroup), 1);
    groupWithShapes->Draw(canvas);
    std::string expectedOutput = "Setting line color to: r: 255; g:0; b:0; a:255\n"
            "Drawing ellipse with center (60, 52.5), horizontal radius 10 and vertical radius 7.5\n"
            "Setting fill color to: r: 0; g:0; b:255; a:255\n"
            "Filling ellipse at (60, 52.5) with width 20 and height 15\n";
    EXPECT_EQ(output.str(), expectedOutput);
}

TEST(GroupTest, DeleteShape)
{
    std::ostringstream output;
    auto canvas = std::make_shared<ConsoleCanvas>(output);

    shapeFactory::ShapeFactory factory;
    auto triangle = factory.CreateShape("triangle #FF0000FF #0000FFFF 0 0 10 0 5 10");

    triangle->GetFillStyle().Enable(true);
    triangle->GetOutlineStyle().Enable(true);

    auto ellipse = factory.CreateShape("ellipse #FF0000FF #0000FFFF 50 60 20 15");

    ellipse->GetFillStyle().Enable(true);
    ellipse->GetOutlineStyle().Enable(true);

    shapes::Group group;

    group.InsertShape(std::move(ellipse), 0);
    group.InsertShape(std::move(triangle), 1);
    group.Draw(canvas);
    group.RemoveShapeAtIndex(0);
    group.Draw(canvas);

    std::string expectedOutput = "Setting line color to: r: 255; g:0; b:0; a:255\n"
            "Drawing ellipse with center (60, 52.5), horizontal radius 10 and vertical radius 7.5\n"
            "Setting fill color to: r: 0; g:0; b:255; a:255\n"
            "Filling ellipse at (60, 52.5) with width 20 and height 15\n"
            "Setting fill color to: r: 0; g:0; b:255; a:255\n"
            "Filling polygon with points: (5, 0) (0, 0) (10, 0) \n"
            "Setting line color to: r: 255; g:0; b:0; a:255\n"
            "Drawing line from (5, 0) to (0, 0)\n"
            "Drawing line from (0, 0) to (10, 0)\n"
            "Drawing line from (10, 0) to (5, 0)\n"
            "Setting fill color to: r: 0; g:0; b:255; a:255\n"
            "Filling polygon with points: (5, 0) (0, 0) (10, 0) \n"
            "Setting line color to: r: 255; g:0; b:0; a:255\n"
            "Drawing line from (5, 0) to (0, 0)\n"
            "Drawing line from (0, 0) to (10, 0)\n"
            "Drawing line from (10, 0) to (5, 0)\n";
    EXPECT_EQ(output.str(), expectedOutput);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
