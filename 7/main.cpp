#include "Canvas/Canvas.h"
#include "Shape/Ellipse.h"
#include "Shape/Group.h"
#include "Shape/Rectangle.h"
#include "Slide/Slide.h"

int main() {
    Slide slide;

    auto rectangle = std::make_shared<Rectangle>(10, 10, 200, 100);
    rectangle->SetLineStyle(LineStyle(true, "#FFFFFFFF", 2.0));
    rectangle->SetFillStyle(FillStyle(true, "#000000FF"));

    auto ellipse = std::make_shared<Ellipse>(150, 150, 50, 80);
    ellipse->SetLineStyle(LineStyle(true, "#FFFFFFFF", 1.5));
    ellipse->SetFillStyle(FillStyle(true, "#000000FF"));

    auto group = std::make_shared<Group>();
    group->AddShape(rectangle);
    group->AddShape(ellipse);

    slide.AddShape(group);
    auto canvas = Canvas(1000, 800, "./../Bin/Output.png");
    slide.Draw(canvas);

    return 0;
}
