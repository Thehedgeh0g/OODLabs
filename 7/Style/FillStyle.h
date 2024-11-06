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

    FillStyle(bool enabled = false, const std::string& color = "undefiend")
        : isEnabled(enabled), color(color) {}
};
#endif //FILLSTYLE_H
