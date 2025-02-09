#include "MacroCommand.h"

namespace History
{
void MacroCommand::AddCommand(std::unique_ptr<ICommand> command)
{
    m_commands.push_back(std::move(command));
}

void MacroCommand::DoExecute()
{
    for (const auto &command: m_commands)
    {
        if (!command->IsExecuted())
        {
            command->Execute();
        }
    }
}

void MacroCommand::DoUnexecute()
{
    for (const auto &command: m_commands)
    {
        if (command->IsExecuted())
        {
            command->Unexecute();
        }
    }
}

}
