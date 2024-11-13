//
// Created by thehedgeh0g on 11.11.24.
//

#ifndef IGROUP_H
#define IGROUP_H
#include <memory>
#include <limits>

namespace shapes
{
class IShape;

class IGroup
{
public:
    [[nodiscard]] virtual size_t GetShapesCount()const = 0;

    [[nodiscard]] virtual const std::unique_ptr<IShape>& GetShapeAtIndex(size_t index) = 0;

    virtual void InsertShape(std::unique_ptr<IShape> shape, size_t position = std::numeric_limits<size_t>::max()) = 0;

    virtual void RemoveShapeAtIndex(size_t index) = 0;

    virtual ~IGroup() = default;
};
}
#endif// IGROUP_H
