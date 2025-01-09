#include "AbstractCommand.h"

namespace History
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

bool AbstractCommand::ReplaceEdit(const ICommand &edit)
{
    return false;
}

bool AbstractCommand::IsExecuted() const
{
    return m_isExecuted; // Возвращаем состояние выполнения
}

std::string AbstractCommand::GetName() const
{
    return m_name; // Возвращаем имя команды
}
}
