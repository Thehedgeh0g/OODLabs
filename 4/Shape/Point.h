//
// Created by thehedgeh0g on 15.10.24.
//

#ifndef POINT_H
#define POINT_H

namespace shape
{
    class Point
    {
    public:
        double x;
        double y;

        bool operator==(const Point &other) const
        {
            return x == other.x && y == other.y;
        }
    };
}
#endif //POINT_H
