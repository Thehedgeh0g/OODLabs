```mermaid
classDiagram
    direction LR

    class CPoint {
        +int x
        +int y
        +CPoint(int x, int y)
    }

    class CModernGraphicsRenderer {
        -ostream & m_out
        -bool m_drawing
        +CModernGraphicsRenderer(ostream & strm)
        +void BeginDraw()
        +void DrawLine(const CPoint & start, const CPoint & end)
        +void EndDraw()
    }

    class ICanvas {
        <<interface>>
        +void MoveTo(int x, int y)*
        +void LineTo(int x, int y)*
    }

    class CCanvas {
        +void MoveTo(int x, int y)
        +void LineTo(int x, int y)
    }

    class ModernGraphicsCanvasAdapter {
        -CModernGraphicsRenderer & m_renderer
        -CPoint m_currentPosition
        +ModernGraphicsCanvasAdapter(CModernGraphicsRenderer & renderer)
        +void MoveTo(int x, int y)
        +void LineTo(int x, int y)
    }

    class ModernGraphicsCanvasClassAdapter {
        -CPoint m_start;
        -CRGBAColor m_color;
        +void SetColor(uint32_t rgbColor)
        +void MoveTo(int x, int y)
        +void LineTo(int x, int y)
    }

    class Point {
        +int x
        +int y
    }

    class ICanvasDrawable {
        +void Draw(ICanvas & canvas)*
    }

    class CTriangle {
        -Point m_p1
        -Point m_p2
        -Point m_p3
        +CTriangle(const Point & p1, const Point & p2, const Point & p3)
        +void Draw(ICanvas & canvas)
    }

    class CRectangle {
        -Point m_leftTop
        -int m_width
        -int m_height
        +CRectangle(const Point & leftTop, int width, int height)
        +void Draw(ICanvas & canvas)
    }

    class CCanvasPainter {
        -ICanvas & m_canvas
        +CCanvasPainter(ICanvas & canvas)
        +void Draw(const ICanvasDrawable & drawable)
    }

    class App {
        +void PaintPicture(CCanvasPainter & painter)
        +void PaintPictureOnCanvas()
        +void PaintPictureOnModernGraphicsRenderer()
    }

    App <.. CCanvas
    App <.. CCanvasPainter
    App <.. CModernGraphicsRenderer
    App <.. ModernGraphicsCanvasAdapter
    App <.. ModernGraphicsCanvasClassAdapter
    ICanvas <|.. CCanvas
    CTriangle <|-- ICanvasDrawable
    CRectangle <|-- ICanvasDrawable
    CCanvasPainter <.. ICanvasDrawable
    CCanvasPainter <.. ICanvas
    CTriangle *-- Point
    CRectangle *-- Point
    ModernGraphicsCanvasAdapter --> CModernGraphicsRenderer: adaptee
    ModernGraphicsCanvasAdapter ..|> ICanvas
    CModernGraphicsRenderer <.. CPoint
    
    ModernGraphicsCanvasClassAdapter ..|> ICanvas
    ModernGraphicsCanvasClassAdapter ..|> CModernGraphicsRenderer


```