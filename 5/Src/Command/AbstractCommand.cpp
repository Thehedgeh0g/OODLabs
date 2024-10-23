#include "AbstractCommand.h"
//
// Created by thehedgeh0g on 23.10.24.
//
namespace Command
{
    void AbstractCommand::Execute()
    {
        ICommand::Execute();
        m_isExecuted = true;
    }

    void AbstractCommand::Unexecute()
    {
        ICommand::Unexecute();
        m_isExecuted = false;
    }

    bool AbstractCommand::IsExecuted()
    {
        return m_isExecuted;
    }

    std::string AbstractCommand::GetName()
    {
        return m_name;
    }
}
