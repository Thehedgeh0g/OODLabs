//
// Created by flipd on 25.12.2024.
//

#ifndef IFIGURE_H
#define IFIGURE_H
#include <memory>

#include "../ICanvas.h"

struct RectD;

namespace view {
    class IFigure {
    public:
        virtual ~IFigure() = default;

        virtual void Draw(uint32_t color, std::unique_ptr<view::ICanvas> &canvas, bool drawFrame) = 0;

        virtual void UpdateFrame(RectD frame) = 0;

        virtual bool PointInFigure(Point point) = 0;
        virtual bool IsPointInFrame(Point point) = 0;

        virtual bool IsOnEditSquare(Point point) = 0;

        [[nodiscard]] virtual std::string GetTypeAsString() = 0;

        [[nodiscard]] virtual std::string GetFigureDataAsString() = 0;
    };
}
#endif //IFIGURE_H
