//
// Created by flipd on 05.11.2024.
//

#ifndef LINESTYLE_H
#define LINESTYLE_H
#include <string>

class LineStyle {
public:
    bool isEnabled;
    std::string color;
    double thickness;

    LineStyle(bool enabled = true, const std::string &color = "rgba(0, 0, 0, 1)", double thickness = 1.0)
        : isEnabled(enabled), color(color), thickness(thickness) {
    }
};
#endif //LINESTYLE_H
