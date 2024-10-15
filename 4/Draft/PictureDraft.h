//
// Created by thehedgeh0g on 16.10.24.
//

#ifndef PICTUREDRAFT_H
#define PICTUREDRAFT_H
#include <memory>
#include <vector>

#include "Shape.h"

class PictureDraft
{
public:
    std::vector<std::unique_ptr<Shape> >::iterator begin()
    {
        return m_shapes.begin();
    }

    std::vector<std::unique_ptr<Shape> >::iterator end()
    {
        return m_shapes.end();
    }

    std::vector<std::unique_ptr<Shape> >::const_iterator cbegin()
    {
        return m_shapes.cbegin();
    }

    std::vector<std::unique_ptr<Shape> >::const_iterator cend()
    {
        return m_shapes.cend();
    }

    void AddShape(std::unique_ptr<Shape> &&shape)
    {
        m_shapes.push_back(std::move(shape));
    }

private:
    std::vector<std::unique_ptr<Shape> > m_shapes;
};

#endif //PICTUREDRAFT_H
