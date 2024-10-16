//
// Created by thehedgeh0g on 16.10.24.
//


#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "./../Shape/Shape.h"
#include "./../Draft/ICanvas.h"
#include "./../ShapeFactory/ShapeFactory.h"
#include "./../Designer/Designer.h"
#include "./../Painter/Painter.h"
#include "./../Client/Client.h"

using ::testing::_;
using ::testing::Return;

class MockShape : public shape::Shape
{
public:
    explicit MockShape(shape::Color color) : Shape(color) {}

    MOCK_METHOD(void, Draw, (draft::ICanvas &canvas), (override));
};

class MockShapeFactory : public Factory::IShapeFactory
{
public:
    MOCK_METHOD(std::unique_ptr<shape::Shape>, CreateShape, (std::string description), (const, override));
};

class MockDesigner : public Designer::IDesigner
{
public:
    MOCK_METHOD(draft::PictureDraft, CreateDraft, (std::istream & inputData), (override));
};

class MockPainter : public Painter::IPainter {
public:
    MOCK_METHOD(void, DrawPicture, (draft::PictureDraft &draft, draft::ICanvas &canvas), (override));
};

class MockCanvas : public draft::ICanvas {
public:
    MOCK_METHOD(void, SetColor, (shape::Color color), (override));
    MOCK_METHOD(void, DrawLine, (shape::Point start, shape::Point end), (override));
    MOCK_METHOD(void, DrawEllipse, (shape::Point center, double hx, double hy), (override));
};

void AssertEqualPoint(shape::Point expectedPoint, shape::Point actualPoint)
{
    EXPECT_EQ(expectedPoint.x, actualPoint.x);
    EXPECT_EQ(expectedPoint.y, actualPoint.y);
}

TEST (rectangle, create_success)
{
    shape::Color color = shape::Color::BLACK;
    shape::Point leftTop(10, 20);
    shape::Point rightBottom(20, 30);
    double width = 30;

    shape::Rectangle rectangle(color, leftTop, rightBottom);

    EXPECT_EQ(color, rectangle.GetColor());
    AssertEqualPoint(leftTop, rectangle.GetLeftTop());
    AssertEqualPoint(leftTop, rectangle.GetLeftTop());
}

TEST(rectangle, draw_success)
{
    shape::Color color = shape::Color::BLACK;
    shape::Point leftTop(10.0, 20.0);
    shape::Point rightBottom(20.0, 10.0);

    shape::Rectangle rectangle(color, leftTop, rightBottom);

    MockCanvas mockCanvas;

    EXPECT_CALL(mockCanvas, SetColor(color))
            .Times(1);

    EXPECT_CALL(mockCanvas, DrawLine(shape::Point(10.0, 20.0), shape::Point(20.0, 20.0)))
            .Times(1);
    EXPECT_CALL(mockCanvas, DrawLine(shape::Point(20.0, 20.0), shape::Point(20.0, 10.0)))
            .Times(1);
    EXPECT_CALL(mockCanvas, DrawLine(shape::Point(20.0, 10.0), shape::Point(10.0, 10.0)))
            .Times(1);
    EXPECT_CALL(mockCanvas, DrawLine(shape::Point(10.0, 10.0), shape::Point(10.0, 20.0)))
            .Times(1);

    rectangle.Draw(mockCanvas);
}

TEST (ellipse, create_success)
{
    shape::Color color = shape::Color::BLACK;
    shape::Point center(50, 50);
    double horizontalRadius = 30;
    double verticalRadius = 20;

    shape::Ellipse ellipse(color, center, horizontalRadius, verticalRadius);

    EXPECT_EQ(color, ellipse.GetColor());
    AssertEqualPoint(center, ellipse.GetCenter());
    EXPECT_EQ(horizontalRadius, ellipse.GetHorizontalRadius());
    EXPECT_EQ(verticalRadius, ellipse.GetVerticalRadius());
}

TEST(ellipse, draw_success)
{
    shape::Color color = shape::Color::BLACK;
    shape::Point center(50, 50);
    double horizontalRadius = 30;
    double verticalRadius = 20;

    shape::Ellipse ellipse(color, center, horizontalRadius, verticalRadius);

    MockCanvas mockCanvas;

    EXPECT_CALL(mockCanvas, SetColor(color))
            .Times(1);

    EXPECT_CALL(mockCanvas, DrawEllipse(center, horizontalRadius, verticalRadius))
            .Times(1);

    ellipse.Draw(mockCanvas);
}

TEST (triangle, create_success)
{
    shape::Color color = shape::Color::BLACK;
    shape::Point point1(10, 20);
    shape::Point point2(40, 20);
    shape::Point point3(25, 50);

    shape::Triangle triangle(color, point1, point2, point3);

    EXPECT_EQ(color, triangle.GetColor());
    AssertEqualPoint(point1, triangle.GetVertex1());
    AssertEqualPoint(point2, triangle.GetVertex2());
    AssertEqualPoint(point3, triangle.GetVertex3());
}

TEST(triangle, draw_success)
{
    shape::Color color = shape::Color::BLACK;
    shape::Point point1(10, 20);
    shape::Point point2(40, 20);
    shape::Point point3(25, 50);

    shape::Triangle triangle(color, point1, point2, point3);

    MockCanvas mockCanvas;

    EXPECT_CALL(mockCanvas, SetColor(color))
            .Times(1);

    EXPECT_CALL(mockCanvas, DrawLine(point1, point2))
            .Times(1);
    EXPECT_CALL(mockCanvas, DrawLine(point2, point3))
            .Times(1);
    EXPECT_CALL(mockCanvas, DrawLine(point3, point1))
            .Times(1);

    triangle.Draw(mockCanvas);
}

TEST(shape_factory, create_triangle_success)
{
    std::string description = "triangle black 10 20 40 20 25 50";

    Factory::ShapeFactory shapeFactory;
    auto shape = shapeFactory.CreateShape(description);

    EXPECT_NE(shape, nullptr);
    EXPECT_EQ(typeid(*shape), typeid(shape::Triangle));

    auto* triangle = dynamic_cast<shape::Triangle*>(shape.get());
    ASSERT_NE(triangle, nullptr);

    EXPECT_EQ(triangle->GetColor(), shape::Color::BLACK);
    AssertEqualPoint(triangle->GetVertex1(), shape::Point(10, 20));
    AssertEqualPoint(triangle->GetVertex2(), shape::Point(40, 20));
    AssertEqualPoint(triangle->GetVertex3(), shape::Point(25, 50));
}

TEST(shape_factory, create_ellipse_success)
{
    std::string description = "ellipse red 50 50 30 20";

    Factory::ShapeFactory shapeFactory;
    auto shape = shapeFactory.CreateShape(description);

    EXPECT_NE(shape, nullptr);
    EXPECT_EQ(typeid(*shape), typeid(shape::Ellipse));

    auto* ellipse = dynamic_cast<shape::Ellipse*>(shape.get());
    ASSERT_NE(ellipse, nullptr);

    EXPECT_EQ(ellipse->GetColor(), shape::Color::RED);
    AssertEqualPoint(ellipse->GetCenter(), shape::Point(50, 50));
    EXPECT_EQ(ellipse->GetHorizontalRadius(), 30);
    EXPECT_EQ(ellipse->GetVerticalRadius(), 20);
}

TEST(shape_factory, create_rectangle_success)
{
    std::string description = "rectangle green 10 20 30 50";

    Factory::ShapeFactory shapeFactory;
    auto shape = shapeFactory.CreateShape(description);

    EXPECT_NE(shape, nullptr);
    EXPECT_EQ(typeid(*shape), typeid(shape::Rectangle));

    auto* rectangle = dynamic_cast<shape::Rectangle*>(shape.get());
    ASSERT_NE(rectangle, nullptr);

    EXPECT_EQ(rectangle->GetColor(), shape::Color::GREEN);
    AssertEqualPoint(rectangle->GetLeftTop(), shape::Point(10, 20));
    AssertEqualPoint(rectangle->GetRightBottom(), shape::Point(30, 50));
}

TEST(shape_factory, create_shape_unknown_type_error)
{
    std::string description = "unknownShape black";

    Factory::ShapeFactory shapeFactory;

    EXPECT_THROW(shapeFactory.CreateShape(description), std::invalid_argument);
}

TEST(picture_draft, add_shape_success)
{
    draft::PictureDraft draft;

    auto triangle = std::make_unique<MockShape>(shape::Color::BLACK);
    auto ellipse = std::make_unique<MockShape>(shape::Color::BLACK);
    auto rectangle = std::make_unique<MockShape>(shape::Color::BLACK);

    draft.AddShape(std::move(triangle));
    draft.AddShape(std::move(ellipse));
    draft.AddShape(std::move(rectangle));

    EXPECT_EQ(std::distance(draft.begin(), draft.end()), 3);
}

TEST(picture_draft, iterate_shapes_success)
{
    draft::PictureDraft draft;

    auto triangle = std::make_unique<MockShape>(shape::Color::BLACK);
    auto ellipse = std::make_unique<MockShape>(shape::Color::BLACK);

    draft.AddShape(std::move(triangle));
    draft.AddShape(std::move(ellipse));

    int count = 0;
    for (const auto& shape : draft)
    {
        EXPECT_NE(shape, nullptr);
        count++;
    }

    EXPECT_EQ(count, 2);

    count = 0;
    for (const auto& shape : draft)
    {
        EXPECT_NE(shape, nullptr);
        count++;
    }

    EXPECT_EQ(count, 2);
}

TEST(designer, create_draft_with_shapes_success) {
    auto mockFactory = std::make_unique<Factory::ShapeFactory>();
    Designer::Designer designer(std::move(mockFactory));

    std::istringstream inputData(
        "triangle black 10 20 40 20 25 50\n"
        "ellipse red 50 50 30 20\n"
        "rectangle green 10 20 30 50"
    );

    draft::PictureDraft draft = designer.CreateDraft(inputData);

    EXPECT_EQ(std::distance(draft.begin(), draft.end()), 3);
}


TEST(painter, draw_picture_success)
{
    Painter::Painter painter;
    MockCanvas mockCanvas;

    auto shape1 = std::make_unique<MockShape>(shape::Color::BLACK);
    auto shape2 = std::make_unique<MockShape>(shape::Color::RED);

    EXPECT_CALL(*shape1, Draw(testing::Ref(mockCanvas))).Times(1);
    EXPECT_CALL(*shape2, Draw(testing::Ref(mockCanvas))).Times(1);

    draft::PictureDraft draft;
    draft.AddShape(std::move(shape1));
    draft.AddShape(std::move(shape2));

    painter.DrawPicture(draft, mockCanvas);
}

TEST(client, handle_command) {
    auto mockDesigner = std::make_unique<MockDesigner>();
    auto mockPainter = std::make_unique<MockPainter>();
    auto mockCanvas = std::make_unique<MockCanvas>();

    EXPECT_CALL(*mockDesigner, CreateDraft(_))
        .Times(1);

    EXPECT_CALL(*mockPainter, DrawPicture(_, _))
        .Times(1);

    ASSERT_NE(nullptr, mockDesigner.get());
    ASSERT_NE(nullptr, mockPainter.get());
    ASSERT_NE(nullptr, mockCanvas.get());

    std::ostringstream outputData;
    auto client = Client(std::move(mockDesigner), std::move(mockPainter), std::move(mockCanvas));

    std::istringstream inputData("triangle black 10 20 40 20 25 50");

    client.Run(inputData, outputData);
}

GTEST_API_ int main(int argc, char **argv) {
    std::cout << "Running tests" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}