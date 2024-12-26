//
// Created by thehedgeh0g on 22.10.24.
//

#ifndef ICOMMAND_H
#define ICOMMAND_H

namespace History
{
    class ICommand
    {
    public:
        virtual ~ICommand() = default;

        virtual void Execute() = 0;

        virtual void Unexecute() = 0;

        virtual bool ReplaceEdit(const ICommand& edit) = 0;

        [[nodiscard]] virtual bool IsExecuted() const = 0;

        [[nodiscard]] virtual std::string GetName() const = 0;
    };
}
#endif //ICOMMAND_H
