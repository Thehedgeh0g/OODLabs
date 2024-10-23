#include "SetTitleCommand.h"
//
// Created by thehedgeh0g on 23.10.24.
//
namespace Command
{
    void SetTitleCommand::DoExecute()
    {
        std::swap(m_title, m_newTitle);
    }

    void SetTitleCommand::DoUnexecute()
    {
        std::swap(m_newTitle, m_title);
    }
}
