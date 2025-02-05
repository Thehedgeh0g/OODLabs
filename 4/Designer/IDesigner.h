//
// Created by thehedgeh0g on 16.10.24.
//

#ifndef IDESIGNER_H
#define IDESIGNER_H
#include "./../Draft/PictureDraft.h"

namespace Designer
{
    class IDesigner
    {
    public:
        virtual draft::PictureDraft CreateDraft(std::istream &in) = 0;

        virtual ~IDesigner() = default;
    };
}
#endif //IDESIGNER_H
