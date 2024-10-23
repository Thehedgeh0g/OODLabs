//
// Created by thehedgeh0g on 22.10.24.
//
#include "EditParagraphCommand.h"
#include <iostream>

#include "../DocumentItem/Paragraph.h"

namespace Command
{
    void EditParagraphCommand::DoExecute()
    {
        if (m_position.has_value() && m_position.value() < m_documentItems.size())
        {
            auto& item = m_documentItems[m_position.value()];

            if (const auto paragraph = item.GetParagraph(); paragraph != nullptr)
            {
                m_text = paragraph->GetText();
                paragraph->SetText(m_newText);
            }
            else
            {
                std::cerr << "Item at the position is not a paragraph." << std::endl;
            }
        }
        else
        {
            std::cerr << "Invalid position: " << (m_position.has_value() ? std::to_string(m_position.value()) : "none") << std::endl;
        }
    }

    void EditParagraphCommand::DoUnexecute()
    {
        if (m_position.has_value() && m_position.value() < m_documentItems.size())
        {
            auto& item = m_documentItems[m_position.value()];

            if (const auto paragraph = item.GetParagraph(); paragraph != nullptr)
            {
                paragraph->SetText(m_text);
            }
            else
            {
                std::cerr << "Item at the position is not a paragraph." << std::endl;
            }
        }
        else
        {
            std::cerr << "Invalid position: " << (m_position.has_value() ? std::to_string(m_position.value()) : "none") << std::endl;
        }
    }
}
