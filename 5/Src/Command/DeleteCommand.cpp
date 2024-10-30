//
// Created by thehedgeh0g on 22.10.24.
//

#include "DeleteCommand.h"

namespace Command
{
    void DeleteCommand::DoExecute()
    {
        if (m_documentItems.empty())
        {
            return;
        }

        if (m_position >= m_documentItems.size())
        {
            //не падает
            throw std::invalid_argument("Out of range by position");
        }

        auto& item = m_documentItems.at(m_position);

        std::shared_ptr<DocumentItem::IImage> image = item.GetImage();
        std::shared_ptr<DocumentItem::IParagraph> paragraph = item.GetParagraph();

        std::shared_ptr<DocumentItem::DocumentItem> documentItem;
        if (image == nullptr)
        {
            documentItem = std::make_shared<DocumentItem::DocumentItem>(paragraph);
        }
        else
        {
            documentItem = std::make_shared<DocumentItem::DocumentItem>(image);
        }

        m_documentItem = std::make_unique<DocumentItem::DocumentItem>(*documentItem);

        m_documentItems.erase(m_documentItems.begin() + m_position);
    }

    void DeleteCommand::DoUnexecute()
    {
        if (m_documentItem == nullptr)
        {
            return;
        }

        m_documentItems.insert(
            m_documentItems.begin() + m_position,
            *m_documentItem);

        m_documentItem = nullptr;
    }
}
