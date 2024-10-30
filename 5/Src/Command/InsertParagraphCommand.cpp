//
// Created by thehedgeh0g on 22.10.24.
//
#include "InsertParagraphCommand.h"
#include <iostream>

#include "../DocumentItem/Paragraph.h"

namespace Command
{
    void InsertParagraphCommand::DoExecute()
    {
        const DocumentItem::DocumentItem newParagraph(std::make_shared<DocumentItem::Paragraph>(m_text));

        if (m_position.has_value())
        {
            if (m_position.value() <= m_documentItems.size())
            {
                m_documentItems.insert(m_documentItems.begin() + m_position.value(), newParagraph);
            }
            else
            {
                // todo cerr не используем
                throw std::runtime_error("Invalid position: " + (m_position.has_value() ? std::to_string(m_position.value()) : "none"));
            }
        }
        else
        {
            m_documentItems.push_back(newParagraph);
        }
    }

    void InsertParagraphCommand::DoUnexecute()
    {
        if (m_position.has_value() && m_position.value() < m_documentItems.size())
        {
            m_documentItems.erase(m_documentItems.begin() + m_position.value());
        }
        else if (!m_position.has_value() && !m_documentItems.empty())
        {
            m_documentItems.pop_back();
        }
        else
        {
            throw std::runtime_error("Invalid position: " + (m_position.has_value() ? std::to_string(m_position.value()) : "none"));
        }
    }
}
