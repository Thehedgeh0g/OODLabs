//
// Created by thehedgeh0g on 22.10.24.
//

#ifndef HISTORY_H
#define HISTORY_H
#include <cassert>
#include <deque>
#include "./../Command/ICommand.h"
#include "./../Command/MacroCommand.h"

namespace History
{
    class History
    {
    public:
        [[nodiscard]] bool CanUndo() const
        {
            return m_nextCommandIndex != 0;
        }

        void Undo()
        {
            if (CanUndo())
            {
                m_commands[m_nextCommandIndex - 1]->Unexecute();
                --m_nextCommandIndex;
            }
        }

        [[nodiscard]] bool CanRedo() const
        {
            return m_nextCommandIndex != m_commands.size();
        }

        void Redo()
        {
            if (CanRedo())
            {
                m_commands[m_nextCommandIndex]->Execute();
                ++m_nextCommandIndex;
            }
        }

        void AddAndExecuteCommand(std::unique_ptr<Command::ICommand> command)
        {
            if (m_commands.at(m_nextCommandIndex-1)->GetName() == command->GetName())
            {
                if (auto* macroCommand = dynamic_cast<Command::MacroCommand*>(command.get()))
                {
                    macroCommand->AddCommand(command);
                }
                else
                {
                    auto macro = std::make_unique<Command::MacroCommand>();
                    macro->SetName(command->GetName());
                    macro->AddCommand(m_commands.at(m_nextCommandIndex-1));
                    macro->AddCommand(command);
                    m_commands.pop_back();
                    m_commands.push_back(std::move(macro));
                }
                command->Execute();
                return;
            }
            if (m_nextCommandIndex < m_commands.size())
            {
                ++m_nextCommandIndex;
                command->Execute();
                m_commands.resize(m_nextCommandIndex);
                m_commands.back() = std::move(command);
            }
            else
            {
                assert(m_nextCommandIndex == m_commands.size());
                m_commands.emplace_back(nullptr);

                try
                {
                    command->Execute();
                    m_commands.back() = std::move(command);
                    ++m_nextCommandIndex;
                }
                catch (...)
                {
                    m_commands.pop_back();
                    throw;
                }

            }
        }

    private:
        std::deque<std::unique_ptr<Command::ICommand>> m_commands;
        size_t m_nextCommandIndex = 0;
    };
}
#endif HISTORY_H
