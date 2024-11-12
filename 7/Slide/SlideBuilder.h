//
// Created by thehedgeh0g on 11.11.24.
//

#ifndef SLIDESERVICE_H
#define SLIDESERVICE_H
#include <istream>
#include <memory>

#include "Slide.h"
#include "../ShapeFactory/IShapeFactory.h"
#include "../Shape/Group.h"


class SlideBuilder {
public:
    explicit SlideBuilder(shapeFactory::IShapeFactory &shapeFactory, std::unique_ptr<Slide>& slide) : m_shapeFactory(shapeFactory), m_currentSlide(slide)
    {
    }

    void CreateSlide(std::istream &inputData)
    {
        std::string line;
        auto firstGroup = std::make_unique<shapes::Group>();
        std::vector<std::unique_ptr<shapes::Group>> groupStack;
        groupStack.push_back(std::move(firstGroup));

        while (!inputData.eof())
        {
            std::getline(inputData, line);
            if (IsStartOrEndCreateGroup(line))
            {
                continue;
            }

            if (auto shape = m_shapeFactory.CreateShape(line))
            {
                groupStack.back()->InsertShape(std::move(shape), groupStack.back()->GetShapesCount());
            }
        }

        m_currentSlide->AddShapes(std::move(groupStack));

    }

private:

    bool IsStartOrEndCreateGroup(
            const std::string &line
            )
    {
        if (line == shapes::Group::typeStart)
        {
            m_groupDeepness++;
            return true;
        }

        if (line == shapes::Group::typeEnd)
        {
            m_groupDeepness--;
            return true;
        }

        return false;
    }

    void pushIntoGroup(shapes::Group& group, std::unique_ptr<shapes::IShape> shape, int deep)
    {
        if (deep == m_groupDeepness)
        {
            group.InsertShape(std::move(shape));
        }
        else
        {
            auto& nestedShape = group.GetShapeAtIndex(group.GetShapesCount() - 1);
            auto* nestedGroup = dynamic_cast<shapes::Group*>(nestedShape.get());

            if (nestedGroup)
            {
                pushIntoGroup(*nestedGroup, std::move(shape), deep + 1);
            }
            else
            {
                throw std::runtime_error("Nested shape is not a group");
            }
        }
    }


    int m_groupDeepness = 0;
    shapeFactory::IShapeFactory &m_shapeFactory;
    std::unique_ptr<Slide>& m_currentSlide;
};
#endif //SLIDESERVICE_H
