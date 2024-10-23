#include "AbstractCommand.h"

namespace Command
{
    void AbstractCommand::Execute()
    {
        DoExecute();
        m_isExecuted = true;
    }

    void AbstractCommand::Unexecute()
    {
        DoUnexecute();
        m_isExecuted = false;
    }

    bool AbstractCommand::IsExecuted() const
    {
        return m_isExecuted;
    }

    std::string AbstractCommand::GetName() const
    {
        return m_name;
    }
}
