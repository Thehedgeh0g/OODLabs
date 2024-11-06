//
// Created by thehedgeh0g on 06.11.24.
//
#include <gtest/gtest.h>
#include <sstream>
#include "../Shape/Rectangle.h"
#include "../Shape/Ellipse.h"
#include "../Shape/Triangle.h"
#include "../Shape/Group.h"
#include "../Canvas/ConsoleCanvas.h"

TEST(RectangleTest, DrawWithStylesEnabled) {
    std::ostringstream output;
    ConsoleCanvas canvas(output);
    Rectangle rect(10, 20, 30, 40);

    FillStyle fillStyle(true, "red");
    LineStyle lineStyle(true, "black", 2.0);

    rect.SetFillStyle(fillStyle);
    rect.SetLineStyle(lineStyle);
    rect.Draw(canvas);

    std::string expectedOutput = "Setting fill color to: red\n"
                                 "Filling polygon with points: (10, 20) (40, 20) (40, 60) (10, 60) \n"
                                 "Setting line color to: black\n"
                                 "Setting line thickness to: 2\n"
                                 "Drawing line from (10, 20) to (40, 20)\n"
                                 "Drawing line from (40, 20) to (40, 60)\n"
                                 "Drawing line from (40, 60) to (10, 60)\n"
                                 "Drawing line from (10, 60) to (10, 20)\n";
    EXPECT_EQ(output.str(), expectedOutput);
}

TEST(RectangleTest, DrawWithStylesDisabled) {
    std::ostringstream output;
    ConsoleCanvas canvas(output);
    Rectangle rect(10, 20, 30, 40);

    FillStyle fillStyle(false, "red");
    LineStyle lineStyle(false, "black", 2.0);

    rect.SetFillStyle(fillStyle);
    rect.SetLineStyle(lineStyle);
    rect.Draw(canvas);

    std::string expectedOutput = "";
    EXPECT_EQ(output.str(), expectedOutput);
}

TEST(EllipseTest, DrawWithStylesEnabled) {
    std::ostringstream output;
    ConsoleCanvas canvas(output);
    Ellipse ellipse(50, 60, 20, 15);

    FillStyle fillStyle(true, "blue");
    LineStyle lineStyle(true, "green", 1.5);

    ellipse.SetFillStyle(fillStyle);
    ellipse.SetLineStyle(lineStyle);
    ellipse.Draw(canvas);

    std::string expectedOutput = "Setting line color to: green\n"
                                 "Setting line thickness to: 1.5\n"
                                 "Drawing ellipse with center (50, 60), horizontal radius 20 and vertical radius 15\n"
                                 "Setting fill color to: blue\n"
                                 "Filling ellipse at (50, 60) with width 40 and height 30\n";
    EXPECT_EQ(output.str(), expectedOutput);
}

TEST(EllipseTest, DrawWithStylesDisabled) {
    std::ostringstream output;
    ConsoleCanvas canvas(output);
    Ellipse ellipse(50, 60, 20, 15);

    FillStyle fillStyle(false, "blue");
    LineStyle lineStyle(false, "green", 1.5);

    ellipse.SetFillStyle(fillStyle);
    ellipse.SetLineStyle(lineStyle);
    ellipse.Draw(canvas);

    std::string expectedOutput = "";
    EXPECT_EQ(output.str(), expectedOutput);
}

TEST(TriangleTest, DrawWithStylesEnabled) {
    std::ostringstream output;
    ConsoleCanvas canvas(output);
    Triangle triangle({0, 0}, {10, 0}, {5, 10});

    FillStyle fillStyle(true, "yellow");
    LineStyle lineStyle(true, "purple", 2.5);

    triangle.SetFillStyle(fillStyle);
    triangle.SetLineStyle(lineStyle);
    triangle.Draw(canvas);

    std::string expectedOutput = "Setting line color to: purple\n"
                                 "Setting line thickness to: 2.5\n"
                                 "Drawing line from (0, 0) to (10, 0)\n"
                                 "Drawing line from (10, 0) to (5, 10)\n"
                                 "Drawing line from (5, 10) to (0, 0)\n"
                                 "Setting fill color to: yellow\n"
                                 "Filling polygon with points: (0, 0) (10, 0) (5, 10) \n";
    EXPECT_EQ(output.str(), expectedOutput);
}

TEST(TriangleTest, DrawWithStylesDisabled) {
    std::ostringstream output;
    ConsoleCanvas canvas(output);
    Triangle triangle({0, 0}, {10, 0}, {5, 10});

    FillStyle fillStyle(false, "yellow");
    LineStyle lineStyle(false, "purple", 2.5);

    triangle.SetFillStyle(fillStyle);
    triangle.SetLineStyle(lineStyle);
    triangle.Draw(canvas);

    std::string expectedOutput = "";
    EXPECT_EQ(output.str(), expectedOutput);
}

TEST(GroupTest, DrawWithStylesDisabled) {
    std::ostringstream output;
    ConsoleCanvas canvas(output);
    auto group = std::make_shared<Group>();

    auto rect = std::make_shared<Rectangle>(0, 0, 20, 10);
    auto ellipse = std::make_shared<Ellipse>(30, 30, 10, 5);

    FillStyle fillStyle(false, "gray");
    LineStyle lineStyle(false, "cyan", 1.0);

    rect->SetFillStyle(fillStyle);
    rect->SetLineStyle(lineStyle);
    ellipse->SetFillStyle(fillStyle);
    ellipse->SetLineStyle(lineStyle);

    group->AddShape(rect);
    group->AddShape(ellipse);
    group->Draw(canvas);

    std::string expectedOutput = "";
    EXPECT_EQ(output.str(), expectedOutput);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
