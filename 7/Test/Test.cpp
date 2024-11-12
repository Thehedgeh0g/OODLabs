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

TEST(RectangleTest, DrawWithStylesEnabled)
{
    std::ostringstream output;
    auto canvas = std::make_shared<ConsoleCanvas>(output);

    auto fillStyle = std::make_unique<style::Style>(style::Color("#FF0000FF"));
    auto lineStyle = std::make_unique<style::Style>(style::Color("#0000FFFF"));
    shapes::Rectangle rect(10, 20, 30, 40, std::move(fillStyle), std::move(lineStyle));

    rect.GetFillStyle().Enable(true);
    rect.GetOutlineStyle().Enable(true);
    rect.Draw(canvas);

    std::string expectedOutput = "Setting fill color to: r: 0; g:0; b:255; a:255\n"
            "Filling polygon with points: (30, 40) (40, 40) (40, 60) (30, 60) \n"
            "Setting line color to: r: 255; g:0; b:0; a:255\n"
            "Drawing line from (30, 40) to (40, 40)\n"
            "Drawing line from (40, 40) to (40, 60)\n"
            "Drawing line from (40, 60) to (30, 60)\n"
            "Drawing line from (30, 60) to (30, 40)\n";
    EXPECT_EQ(output.str(), expectedOutput);
}

TEST(RectangleTest, DrawWithStylesDisabled)
{
    std::ostringstream output;
    auto canvas = std::make_shared<ConsoleCanvas>(output);

    auto fillStyle = std::make_unique<style::Style>(style::Color("#FF0000FF"));
    auto lineStyle = std::make_unique<style::Style>(style::Color("#0000FFFF"));
    shapes::Rectangle rect(10, 20, 30, 40, std::move(fillStyle), std::move(lineStyle));

    rect.GetFillStyle().Enable(false);
    rect.GetOutlineStyle().Enable(false);

    rect.Draw(canvas);

    std::string expectedOutput = "";
    EXPECT_EQ(output.str(), expectedOutput);
}

TEST(EllipseTest, DrawWithStylesEnabled)
{
    std::ostringstream output;
    auto canvas = std::make_shared<ConsoleCanvas>(output);

    auto fillStyle = std::make_unique<style::Style>(style::Color("#FF0000FF"));
    auto lineStyle = std::make_unique<style::Style>(style::Color("#0000FFFF"));
    shapes::Ellipse ellipse({50, 60}, 20, 15, std::move(fillStyle), std::move(lineStyle));

    ellipse.GetFillStyle().Enable(true);
    ellipse.GetOutlineStyle().Enable(true);
    ellipse.Draw(canvas);

    std::string expectedOutput = "Setting line color to: r: 255; g:0; b:0; a:255\n"
            "Drawing ellipse with center (50, 60), horizontal radius 20 and vertical radius 15\n"
            "Setting fill color to: r: 0; g:0; b:255; a:255\n"
            "Filling ellipse at (50, 60) with width 40 and height 30\n";
    EXPECT_EQ(output.str(), expectedOutput);
}

TEST(EllipseTest, DrawWithStylesDisabled)
{
    std::ostringstream output;
    auto canvas = std::make_shared<ConsoleCanvas>(output);

    auto fillStyle = std::make_unique<style::Style>(style::Color("#FF0000FF"));
    auto lineStyle = std::make_unique<style::Style>(style::Color("#0000FFFF"));
    shapes::Ellipse ellipse({50, 60}, 20, 15, std::move(fillStyle), std::move(lineStyle));

    ellipse.GetFillStyle().Enable(false);
    ellipse.GetOutlineStyle().Enable(false);
    ellipse.Draw(canvas);

    std::string expectedOutput = "";
    EXPECT_EQ(output.str(), expectedOutput);
}

TEST(TriangleTest, DrawWithStylesEnabled)
{
    std::ostringstream output;
    auto canvas = std::make_shared<ConsoleCanvas>(output);

    auto fillStyle = std::make_unique<style::Style>(style::Color("#FF0000FF"));
    auto lineStyle = std::make_unique<style::Style>(style::Color("#0000FFFF"));
    shapes::Triangle triangle({0, 0}, {10, 0}, {5, 10}, std::move(lineStyle), std::move(fillStyle));

    triangle.GetFillStyle().Enable(true);
    triangle.GetOutlineStyle().Enable(true);
    triangle.Draw(canvas);

    std::string expectedOutput = "Setting fill color to: r: 255; g:0; b:0; a:255\n"
            "Filling polygon with points: (0, 0) (10, 0) (5, 10) \n"
            "Setting line color to: r: 0; g:0; b:255; a:255\n"
            "Drawing line from (0, 0) to (10, 0)\n"
            "Drawing line from (10, 0) to (5, 10)\n"
            "Drawing line from (5, 10) to (0, 0)\n";
    EXPECT_EQ(output.str(), expectedOutput);
}

TEST(TriangleTest, DrawWithStylesDisabled)
{
    std::ostringstream output;
    auto canvas = std::make_shared<ConsoleCanvas>(output);

    auto fillStyle = std::make_unique<style::Style>(style::Color("#FF0000FF"));
    auto lineStyle = std::make_unique<style::Style>(style::Color("#0000FFFF"));
    shapes::Triangle triangle({0, 0}, {10, 0}, {5, 10}, std::move(lineStyle), std::move(fillStyle));

    triangle.GetFillStyle().Enable(false);
    triangle.GetOutlineStyle().Enable(false);
    triangle.Draw(canvas);

    std::string expectedOutput = "";
    EXPECT_EQ(output.str(), expectedOutput);
}

TEST(GroupTest, DrawGroup)
{
    std::ostringstream output;
    auto canvas = std::make_shared<ConsoleCanvas>(output);

    auto fillStyle = std::make_unique<style::Style>(style::Color("#FF0000FF"));
    auto lineStyle = std::make_unique<style::Style>(style::Color("#0000FFFF"));
    auto triangle = std::make_unique<shapes::Triangle>(shapes::Point{0, 0}, shapes::Point{10, 0}, shapes::Point{5, 10},
                                                       std::move(lineStyle), std::move(fillStyle));

    triangle->GetFillStyle().Enable(true);
    triangle->GetOutlineStyle().Enable(true);

    auto fillStyle2 = std::make_unique<style::Style>(style::Color("#FF0000FF"));
    auto lineStyle2 = std::make_unique<style::Style>(style::Color("#0000FFFF"));
    auto ellipse = std::make_unique<shapes::Ellipse>(shapes::Point{50, 60}, 20, 15, std::move(fillStyle2),
                                                     std::move(lineStyle2));

    ellipse->GetFillStyle().Enable(true);
    ellipse->GetOutlineStyle().Enable(true);

    shapes::Group group;

    group.InsertShape(std::move(ellipse), group.GetShapesCount());
    group.InsertShape(std::move(triangle), group.GetShapesCount());
    group.Draw(canvas);

    std::string expectedOutput = "Setting line color to: r: 255; g:0; b:0; a:255\n"
            "Drawing ellipse with center (50, 60), horizontal radius 20 and vertical radius 15\n"
            "Setting fill color to: r: 0; g:0; b:255; a:255\n"
            "Filling ellipse at (50, 60) with width 40 and height 30\n"
            "Setting fill color to: r: 255; g:0; b:0; a:255\n"
            "Filling polygon with points: (0, 0) (10, 0) (5, 10) \n"
            "Setting line color to: r: 0; g:0; b:255; a:255\n"
            "Drawing line from (0, 0) to (10, 0)\n"
            "Drawing line from (10, 0) to (5, 10)\n"
            "Drawing line from (5, 10) to (0, 0)\n";
    EXPECT_EQ(output.str(), expectedOutput);
}

TEST(GroupShapeTest, GetStyleGroupShape)
{
    auto fillStyle = std::make_unique<style::Style>(style::Color("#FF0000FF"));
    auto lineStyle = std::make_unique<style::Style>(style::Color("#0000FFFF"));
    auto triangle = std::make_unique<shapes::Triangle>(shapes::Point{0, 0}, shapes::Point{10, 0}, shapes::Point{5, 10},
                                                       std::move(lineStyle), std::move(fillStyle));

    triangle->GetFillStyle().Enable(true);
    triangle->GetOutlineStyle().Enable(true);
    auto fillStyle2 = std::make_unique<style::Style>(style::Color("#FF0000FF"));
    auto lineStyle2 = std::make_unique<style::Style>(style::Color("#0000FFFF"));
    auto ellipse = std::make_unique<shapes::Ellipse>(shapes::Point{50, 60}, 20, 15, std::move(fillStyle2),
                                                     std::move(lineStyle2));

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

TEST(GroupShapeTest, GetSameStyleGroupShape)
{
    style::Color expectedOutlineStyleColor('#FF0000FF');
    style::Color expectedFillStyleColor('#0000FFFF');
    auto fillStyle = std::make_unique<style::Style>(expectedFillStyleColor);
    auto lineStyle = std::make_unique<style::Style>(expectedOutlineStyleColor);
    auto triangle = std::make_unique<shapes::Triangle>(shapes::Point{0, 0}, shapes::Point{10, 0}, shapes::Point{5, 10},
                                                       std::move(lineStyle), std::move(fillStyle));

    triangle->GetFillStyle().Enable(true);
    triangle->GetOutlineStyle().Enable(true);
    auto fillStyle2 = std::make_unique<style::Style>(expectedFillStyleColor);
    auto lineStyle2 = std::make_unique<style::Style>(expectedOutlineStyleColor);
    auto ellipse = std::make_unique<shapes::Ellipse>(shapes::Point{50, 60}, 20, 15, std::move(fillStyle2),
                                                     std::move(lineStyle2));

    ellipse->GetFillStyle().Enable(true);
    ellipse->GetOutlineStyle().Enable(true);
    shapes::Group groupShape;

    groupShape.InsertShape(std::move(ellipse), 0);
    groupShape.InsertShape(std::move(triangle), 1);

    EXPECT_EQ(expectedOutlineStyleColor, groupShape.GetOutlineStyle().GetColor());
    EXPECT_EQ(expectedFillStyleColor, groupShape.GetFillStyle().GetColor());
}

TEST(GroupShapeTest, SetStyleGroupShape)
{
    style::Color expectedOutlineStyleColor('#FFAA00FF');
    style::Color expectedFillStyleColor('#00AAFFFF');
    auto fillStyle = std::make_unique<style::Style>(style::Color("#FF0000FF"));
    auto lineStyle = std::make_unique<style::Style>(style::Color("#0000FFFF"));
    auto triangle = std::make_unique<shapes::Triangle>(shapes::Point{0, 0}, shapes::Point{10, 0}, shapes::Point{5, 10},
                                                       std::move(lineStyle), std::move(fillStyle));

    triangle->GetFillStyle().Enable(true);
    triangle->GetOutlineStyle().Enable(true);
    auto fillStyle2 = std::make_unique<style::Style>(style::Color("#FF0000FF"));
    auto lineStyle2 = std::make_unique<style::Style>(style::Color("#0000FFFF"));
    auto ellipse = std::make_unique<shapes::Ellipse>(shapes::Point{50, 60}, 20, 15, std::move(fillStyle2),
                                                     std::move(lineStyle2));

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

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
