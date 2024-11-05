//
// Created by thehedgeh0g on 29.10.24.
//
#include <iostream>

#include "./app/ModernGraphicsCanvasAdapter.h"
#include "./shape_drawing_lib/shape_drawing_lib.h"
#include "./graphics_lib/graphics_lib.h"
#include "./modern_graphics_lib/modern_graphics_lib.h"
#include "app/ModernGraphicsCanvasClassAdapter.h"

using namespace std;
using namespace graphics_lib;
using namespace modern_graphics_lib;
using namespace shape_drawing_lib;

namespace app
{
    void PaintPicture(CCanvasPainter &painter)
    {
        using namespace shape_drawing_lib;

        const CTriangle triangle({10, 15}, {100, 200}, {150, 250});
        const CRectangle rectangle({30, 40}, 18, 24);

        painter.Draw(triangle);
        painter.Draw(rectangle);
    }

    void PaintPictureOnCanvas()
    {
        CCanvas simpleCanvas;
        CCanvasPainter painter(simpleCanvas);

        PaintPicture(painter);
    }

    void PaintPictureOnModernGraphicsRenderer()
    {
        CModernGraphicsRenderer renderer(cout);
        ModernGraphicsCanvasClassAdapter modernGraphicsAdapter(cout);
        CCanvasPainter painter(modernGraphicsAdapter);

        renderer.BeginDraw();

        PaintPicture(painter);

        renderer.EndDraw();
    }
}


int main()
{
    cout << "Should we use new API (y|n)?";

    string userInput;

    if (getline(cin, userInput) && (userInput == "y" || userInput == "Y"))
    {
        app::PaintPictureOnModernGraphicsRenderer();
    }
    else
    {
        app::PaintPictureOnCanvas();
    }

    return 0;
}
