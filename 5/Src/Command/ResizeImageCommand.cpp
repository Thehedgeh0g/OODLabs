//
// Created by thehedgeh0g on 23.10.24.
//
#include "ResizeImageCommand.h"
#include <iostream>

namespace Command
{
    void ResizeImageCommand::DoExecute()
    {
        if (m_position < m_documentItem.size())
        {
            auto& item = m_documentItem[m_position];

            if (const auto image = item.GetImage(); image != nullptr)
            {
                m_width = image->GetWidth();
                m_height = image->GetHeight();

                image->Resize(m_newWidth, m_newHeight);
            }
            else
            {
                std::cerr << "Item at position " << m_position << " is not an image." << std::endl;
            }
        }
        else
        {
            std::cerr << "Invalid position: " << m_position << std::endl;
        }
    }

    void ResizeImageCommand::DoUnexecute()
    {
        // Проверяем, что позиция находится в пределах документа
        if (m_position < m_documentItem.size())
        {
            auto& item = m_documentItem[m_position];

            if (const auto image = item.GetImage(); image != nullptr)
            {
                // Восстанавливаем старые размеры
                image->Resize(m_width, m_height);
            }
            else
            {
                std::cerr << "Item at position " << m_position << " is not an image." << std::endl;
            }
        }
        else
        {
            std::cerr << "Invalid position: " << m_position << std::endl;
        }
    }
}
