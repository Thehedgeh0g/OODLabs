//
// Created by thehedgeh0g on 23.10.24.
//

#ifndef MACROCOMMAND_H
#define MACROCOMMAND_H
#include <functional>
#include <memory>
#include <string>
#include <utility>

#include "AbstractCommand.h"

namespace Command
{
    class MacroCommand : public AbstractCommand
    {
    public:
        explicit MacroCommand();

        void AddCommand(const std::unique_ptr<ICommand>& command);

        void SetName(std::string name)
        {
            m_name = std::move(name);
        }

        [[nodiscard]] std::string GetName() const
        {
            return m_name;
        }

    protected:
        void DoExecute() override;

        void DoUnexecute() override;

    private:
        std::vector<std::unique_ptr<ICommand> > m_commands = {};
        std::string m_name;
    };
} // Command

#endif //MACROCOMMAND_H
