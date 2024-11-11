//
// Created by thehedgeh0g on 10.11.24.
//

#ifndef ISTYLE_H
#define ISTYLE_H
#include <optional>

#include "Color.h"

namespace style
{
class IStyle
{
public:
    virtual ~IStyle() = default;

    [[nodiscard]] virtual std::optional<Color> GetColor() const = 0;

    [[nodiscard]] virtual std::optional<double> GetThickness() const = 0;

    [[nodiscard]] virtual std::optional<bool> IsEnabled() const = 0;

    virtual void SetColor(const Color &color) = 0;

    virtual void SetThickness(double thickness) = 0;

    virtual void Enable(bool enabled) = 0;
};
}
#endif //ISTYLE_H
