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


class SlideService {
public:
    explicit SlideService(shapeFactory::IShapeFactory &shapeFactory)
            : m_shapeFactory(shapeFactory)
    {
        m_currentSlide = std::make_unique<Slide>();
    }

    void CreateSlide(std::istream &inputData)
    {
        std::string line;
        auto firstGroup = std::make_shared<shapes::Group>();
        std::vector<std::shared_ptr<shapes::Group>> groupStack;
        groupStack.push_back(firstGroup);

        while (!inputData.eof())
        {
            std::getline(inputData, line);
            if (IsStartOrEndCreateGroup(line, groupStack))
            {
                continue;
            }

            if (auto shape = m_shapeFactory.CreateShape(line))
            {
                groupStack.back()->InsertShape(shape, groupStack.back()->GetShapesCount());
            }
        }

        m_currentSlide->AddShapes(groupStack);

    }

    void DrawSlide(const std::shared_ptr<ICanvas> &canvas)
    {
        if (m_currentSlide != nullptr)
        {
            m_currentSlide->Draw(canvas);
        }
    }

    static bool IsStartOrEndCreateGroup(
            const std::string &line,
            std::vector<std::shared_ptr<shapes::Group>> &groupStack
            )
    {
        if (line == shapes::Group::typeStart)
        {
            auto newGroup = std::make_shared<shapes::Group>();

            groupStack.push_back(newGroup);
            return true;
        }

        if (line == shapes::Group::typeEnd)
        {
            if (groupStack.size() > 1)
            {
                auto newGroup = groupStack.back();
                if (newGroup->GetShapesCount() > 0)
                {
                    groupStack.back()->InsertShape(std::static_pointer_cast<shapes::IShape>(newGroup),
                                                   groupStack.back()->GetShapesCount());
                }
                groupStack.pop_back();
            }
            return true;
        }

        return false;
    }


private:
    shapeFactory::IShapeFactory &m_shapeFactory;
    std::unique_ptr<Slide> m_currentSlide;
};
#endif //SLIDESERVICE_H
