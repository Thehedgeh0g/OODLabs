//
// Created by flipd on 05.11.2024.
//

#ifndef FILLSTYLE_H
#define FILLSTYLE_H
#include <string>

class FillStyle {
public:
    bool isEnabled;
    std::string color;

    FillStyle(bool enabled = true, const std::string& color = "rgba(255, 255, 255, 1)")
        : isEnabled(enabled), color(color) {}
};
#endif //FILLSTYLE_H
