//
// Created by flipd on 05.11.2024.
//

#ifndef FILLSTYLE_H
#define FILLSTYLE_H
#include <optional>
#include "Color.h"
#include "IStyle.h"

namespace style
{
class Style : public IStyle
{
public:
    explicit Style(std::optional<Color> color) : m_color(color)
    {
    }

    [[nodiscard]] std::optional<Color> GetColor() const override
    {
        return m_color;
    }

    [[nodiscard]] std::optional<double> GetThickness() const override
    {
        return 0;
    }

    [[nodiscard]] std::optional<bool> IsEnabled() const override
    {
        return m_isEnabled;
    }

    void SetColor(const Color &color) override
    {
        m_color = color;
    }

    void SetThickness(double thickness) override
    {
    }

    void Enable(bool enabled) override
    {
        m_isEnabled = enabled;
    }

private:
    std::optional<bool> m_isEnabled;
    std::optional<Color> m_color = std::nullopt;
};
}
#endif //FILLSTYLE_H
