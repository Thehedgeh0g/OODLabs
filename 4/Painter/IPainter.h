//
// Created by thehedgeh0g on 16.10.24.
//

#ifndef IPAINTER_H
#define IPAINTER_H

namespace Painter
{
    class IPainter
    {
    public:
        virtual ~IPainter() = default;

        virtual void DrawPicture(draft::PictureDraft &draft, draft::ICanvas &canvas) = 0;
    };
}
#endif //IPAINTER_H
