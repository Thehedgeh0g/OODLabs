//
// Created by thehedgeh0g on 16.10.24.
//

#ifndef PAINTER_H
#define PAINTER_H
#include "IPainter.h"

namespace Painter
{
    class Painter : public IPainter
    {
    public:
        ~Painter() override = default;

        void DrawPicture(draft::PictureDraft &draft, draft::ICanvas &canvas) override
        {
            for (const auto &shape: draft)
            {
                shape->Draw(canvas);
            }
        }
    };
}

#endif //PAINTER_H
