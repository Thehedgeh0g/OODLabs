//
// Created by thehedgeh0g on 22.10.24.
//

#include "InsertImageCommand.h"

#include <fstream>
#include <iostream>

#include "../DocumentItem/Image.h"

namespace Command
{
    InsertImageCommand::~InsertImageCommand()
    {
        if (!m_isExecuted)
        {
            remove(m_path.c_str());
        }
    }

    void InsertImageCommand::DoExecute()
    {
        const DocumentItem::DocumentItem newImage(std::make_shared<DocumentItem::Image>(m_path, m_width, m_height));

        if (m_position.has_value() && m_position.value() <= m_documentItems.size())
        {
            m_documentItems.insert(m_documentItems.begin() + m_position.value(), newImage);
        }
        else if (!m_position.has_value())
        {
            m_documentItems.push_back(newImage);
        }
        else
        {
            std::cerr << "Invalid position: " << m_position.value() << std::endl;
        }
    }

    void InsertImageCommand::DoUnexecute()
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
            std::cerr << "Invalid position for undo: " << m_position.value() << std::endl;
        }
    }
}
