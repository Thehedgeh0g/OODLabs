//
// Created by thehedgeh0g on 22.10.24.
//

#ifndef ICOMMAND_H
#define ICOMMAND_H

namespace Command
{
    class ICommand
    {
    public:
        virtual ~ICommand() = default;

        virtual void Execute() = 0;

        virtual void Unexecute() = 0;

        [[nodiscard]] virtual bool IsExecuted() const = 0;

        [[nodiscard]] virtual std::string GetName() const = 0;
    };
}
#endif //ICOMMAND_H
