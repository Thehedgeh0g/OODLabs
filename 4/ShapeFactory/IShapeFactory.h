//
// Created by thehedgeh0g on 15.10.24.
//

#ifndef ISHAPEFACTORY_H
#define ISHAPEFACTORY_H
#include <memory>

#include "../Shape/Shape.h"

namespace Factory
{
    class IShapeFactory
    {
    public:
        virtual ~IShapeFactory() = default;

        [[nodiscard]] virtual std::unique_ptr<shape::Shape> CreateShape(std::string shapeData) const = 0;
    };
}

#endif //ISHAPEFACTORY_H
