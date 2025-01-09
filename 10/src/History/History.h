//
// Created by thehedgeh0g on 22.10.24.
//

#ifndef HISTORY_H
#define HISTORY_H
#include <cassert>
#include <deque>
#include "./MacroCommand.h"

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

    void AddAndExecuteCommand(std::unique_ptr<ICommand> command)
    {
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
                auto &prevCommand = m_commands[m_nextCommandIndex > 0 ? m_nextCommandIndex - 1 : 0];
                if (!command->ReplaceEdit(*prevCommand.get()))
                {
                    ++m_nextCommandIndex;
                }
                else
                {
                    m_commands.pop_back();
                }
                m_commands.back() = std::move(command);
            }
            catch (...)
            {
                m_commands.pop_back();
                throw;
            }
        }
    }

private:
    std::deque<std::unique_ptr<ICommand>> m_commands;
    size_t m_nextCommandIndex = 0;
};
}
#endif //HISTORY_H
