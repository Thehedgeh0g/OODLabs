//
// Created by thehedgeh0g on 22.10.24.
//

#ifndef RESIZEIMAGECOMMAND_H
#define RESIZEIMAGECOMMAND_H
#include <vector>

#include "AbstractCommand.h"
#include "../DocumentItem/DocumentItem.h"

namespace Command
{
    class ResizeImageCommand : public AbstractCommand
    {
    public:
        ResizeImageCommand(
            const std::vector<DocumentItem::DocumentItem> &documentItem,
            const int newWidth,
            const int newHeight,
            const size_t position
        ) :
            m_newWidth(newWidth),
            m_newHeight(newHeight),
            m_position(position),
            m_documentItem(documentItem)
        {
            m_name = "ResizeImageCommand";
        }

    protected:
        void DoExecute() override;

        void DoUnexecute() override;

    private:
        int m_width = 0;
        int m_height = 0;
        int m_newWidth;
        int m_newHeight;
        size_t m_position;
        std::vector<DocumentItem::DocumentItem> m_documentItem;
    };
}

#endif //RESIZEIMAGECOMMAND_H
