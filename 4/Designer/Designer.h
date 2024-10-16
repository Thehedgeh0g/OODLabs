//
// Created by thehedgeh0g on 16.10.24.
//

#ifndef DESIGNER_H
#define DESIGNER_H
#include <iostream>

#include "IDesigner.h"
#include "./../ShapeFactory/ShapeFactory.h"
#include "./../Draft/PictureDraft.h"

namespace Designer
{
    class Designer : public IDesigner
    {
    public:
        explicit Designer(std::unique_ptr<Factory::IShapeFactory> &&factory) : m_factory(std::move(factory))
        {
        };

        draft::PictureDraft CreateDraft(std::istream &in) override
        {
            std::string line;

            draft::PictureDraft draft;

            while (!in.eof())
            {
                std::getline(in, line);
                try
                {
                    draft.AddShape(std::move(m_factory->CreateShape(line)));
                }
                catch (...)
                {
                    break;
                }
            }

            return draft;
        }

        ~Designer() override = default;

    private:
        std::unique_ptr<Factory::IShapeFactory> m_factory;
    };
}
#endif //DESIGNER_H
