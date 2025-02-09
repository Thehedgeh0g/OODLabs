#ifndef LAB9_DRAWER_H
#define LAB9_DRAWER_H

#include <cassert>
#include "Geom.h"
#include "Image.h"

class Drawer
{
public:
    static void DrawLine(Image &image, Point from, Point to, uint32_t color)
    {
        const int deltaX = std::abs(to.x - from.x);
        const int deltaY = std::abs(to.y - from.y);

        if (deltaY > deltaX)
        {
            DrawSteepLine(image, from, to, color);
        }
        else
        {
            DrawSlopeLine(image, from, to, color);
        }
    }

    static void DrawCircle(Image &image, Point center, int radius, uint32_t color)
    {
        int x = radius;
        int y = 0;
        int decisionOver2 = (3 - x)/3;

        while (y <= x)
        {
           // assert(x * x + y * y <= radius * radius);
            //assert(x * x + y * y >= ((radius - 1) * (radius - 1) + radius));
            image.SetPixel({center.x + x, center.y + y}, color);
            image.SetPixel({center.x + y, center.y + x}, color);
            image.SetPixel({center.x - y, center.y + x}, color);
            image.SetPixel({center.x - x, center.y + y}, color);
            image.SetPixel({center.x - x, center.y - y}, color);
            image.SetPixel({center.x - y, center.y - x}, color);
            image.SetPixel({center.x + y, center.y - x}, color);
            image.SetPixel({center.x + x, center.y - y}, color);

            y++;

            if (decisionOver2 <= 0)
            {
                decisionOver2 += 2 * y + 1; 
            }
            else
            {
                x--;
                decisionOver2 += 2 * (y - x) + 1; 
            }
        }
    }


    static void DrawFilledCircle(Image &image, Point center, int radius, uint32_t color)
    {
        int x = radius;
        int y = 0;
        int decisionOver2 = (3 - radius)/3;

        while (y <= x)
        {
            DrawLine(image, {center.x + x, center.y + y}, {center.x - x, center.y + y}, color);
            if (y != 0)
            {
                DrawLine(image, {center.x - x, center.y - y}, {center.x + x, center.y - y}, color);
            }
            if (x != y)
            {
                DrawLine(image, {center.x + y, center.y + x}, {center.x - y, center.y + x}, color);
                DrawLine(image, {center.x - y, center.y - x}, {center.x + y, center.y - x}, color);
            }

            
            y++;

            if (decisionOver2 <= 0)
            {
                decisionOver2 += 2 * y + 1; 
            }
            else
            {
                x--;
                decisionOver2 += 2 * (y - x) + 1; 
            }
        }
    }

private:
    static int Sign(int value)
    {
        return (0 < value) - (value < 0);
    }

    static void DrawSteepLine(Image &image, Point from, Point to, uint32_t color)
    {
        const int deltaX = std::abs(to.x - from.x);
        const int deltaY = std::abs(to.y - from.y);

        assert(deltaY >= deltaX);

        if (from.y > to.y)
        {
            
            std::swap(from, to);
        }

        const int stepX = Sign(to.x - from.x); 
        const int errorThreshold = deltaY + 1; 
        const int deltaErr = deltaX + 1; 

        
        int error = deltaErr / 2;

        for (Point p = from; p.y <= to.y; ++p.y)
        {
            image.SetPixel({p.x, p.y}, color);
            assert((p.y != to.y) || (p.x == to.x));

            error += deltaErr; 

            if (error >= errorThreshold)
            {
                
                p.x += stepX; 
                error -= errorThreshold; 
            }
        }
    }

    /**
     * Ðèñóåò ïîëîãèé îòðåçîê (äëÿ êîòîðîãî |to.y - from.x| >= |to.y - from.y|).
     */
    static void DrawSlopeLine(Image &image, Point from, Point to, uint32_t color)
    {
        const int deltaX = std::abs(to.x - from.x);
        const int deltaY = std::abs(to.y - from.y);

        assert(deltaX >= deltaY);

        if (from.x > to.x)
        {
            
            std::swap(from, to);
        }

        

        const int stepY = Sign(to.y - from.y);
        const int errorThreshold = deltaX + 1;
        const int deltaErr = deltaY + 1;

        int error = deltaErr / 2;

        for (Point p = from; p.x <= to.x; ++p.x)
        {
            image.SetPixel({p.x, p.y}, color);
            assert((p.x != to.x) || (p.y == to.y));

            error += deltaErr;

            if (error >= errorThreshold)
            {
                p.y += stepY;
                error -= errorThreshold;
            }
        }
    }
};

#endif 
