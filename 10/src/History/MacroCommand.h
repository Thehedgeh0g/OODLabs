#ifndef MACROCOMMAND_H
#define MACROCOMMAND_H
#include <functional>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "AbstractCommand.h"

namespace History
{
class MacroCommand : public AbstractCommand
{
public:
    explicit MacroCommand():
        m_commands(), m_name()
    {
    };

    ~MacroCommand() override = default;

    void AddCommand(std::unique_ptr<ICommand> command);

    void SetName(std::string name)
    {
        m_name = std::move(name);
    }

    bool ReplaceEdit(const ICommand &edit) override
    {
        return false;
    }

    [[nodiscard]] std::string GetName() const
    {
        return m_name;
    }

protected:
    void DoExecute() override;

    void DoUnexecute() override;

private:
    std::vector<std::unique_ptr<ICommand>> m_commands = {};
    std::string m_name;
};
}

#endif //MACROCOMMAND_H
