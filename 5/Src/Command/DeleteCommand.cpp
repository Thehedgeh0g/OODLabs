//
// Created by thehedgeh0g on 22.10.24.
//

#include "DeleteCommand.h"
#include <iostream>

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
            throw std::invalid_argument("Out of range by position");
        }
        auto item = m_documentItems.at(m_position).GetImage() == nullptr
                        ? m_documentItems.at(m_position).GetParagraph()
                        : m_documentItems.at(m_position).GetImage();
        m_documentItem = std::make_unique<DocumentItem>(item);

        m_documentItems.erase(
            m_documentItems.begin() + static_cast<std::vector<DocumentItem::DocumentItem>::iterator::difference_type>(
                m_position));
    }

    void DeleteCommand::DoUnexecute()
    {
        if (m_documentItem == nullptr)
        {
            return;
        }

        m_documentItems.insert(
            m_documentItems.begin() + static_cast<std::vector<DocumentItem::DocumentItem>::iterator::difference_type>(
                m_position),
            *m_documentItem);

        m_documentItem = nullptr;
    }
}
