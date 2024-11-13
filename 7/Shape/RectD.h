//
// Created by thehedgeh0g on 13.11.24.
//

#ifndef RECTD_H
#define RECTD_H

template <typename T>
struct Rect
{
    T left;
    T top;
    T width;
    T height;
};

typedef Rect<double> RectD;

#endif //RECTD_H
