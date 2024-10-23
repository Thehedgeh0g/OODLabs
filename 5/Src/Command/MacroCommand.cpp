#include "MacroCommand.h"

namespace Command {
    void MacroCommand::AddCommand(std::unique_ptr<ICommand> command) // Измените здесь тоже
    {
        m_commands.push_back(std::move(command)); // Теперь это работает
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

}
