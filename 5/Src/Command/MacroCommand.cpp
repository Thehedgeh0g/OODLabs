//
// Created by thehedgeh0g on 23.10.24.
//

#include "MacroCommand.h"

namespace Command {
    void MacroCommand::AddCommand(const std::unique_ptr<ICommand>& command)
    {
        m_commands.push_back(command);
    }

    void MacroCommand::DoExecute()
    {
        for (const auto& command: m_commands)
        {
            if (!command->IsExecuted())
            {
                command->Execute();
            }
        }
    }

    void MacroCommand::DoUnexecute()
    {
        for (const auto& command: m_commands)
        {
            if (command->IsExecuted())
            {
                command->Unexecute();
            }
        }
    }

} // Command