//
// Created by thehedgeh0g on 11.11.24.
//

#ifndef ISHAPEFACTORY_H
#define ISHAPEFACTORY_H
#include <memory>

namespace shapes
{
class IShape;
}

namespace shapeFactory
{
class IShapeFactory
{
public:
    virtual std::shared_ptr<shapes::IShape> CreateShape(const std::string & description) = 0;

    virtual ~IShapeFactory() = default;
};

}
#endif //ISHAPEFACTORY_H
