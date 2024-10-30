#include "SetTitleCommand.h"
//
// Created by thehedgeh0g on 23.10.24.
//
namespace Command
{
    bool SetTitleCommand::ReplaceEdit(const ICommand &edit) {
        if (auto otherSetTitle = dynamic_cast<const SetTitleCommand *>(&edit);
            otherSetTitle &&
            otherSetTitle->m_newTitle == m_prevTitle
        )
        {
            m_prevTitle = otherSetTitle->m_prevTitle;
            return true;
        }
        return false;
    }

    void SetTitleCommand::DoExecute()
    {
        m_prevTitle = m_title;
        m_title = m_newTitle;
    }

    void SetTitleCommand::DoUnexecute()
    {
        m_title = m_prevTitle;
    }
}
