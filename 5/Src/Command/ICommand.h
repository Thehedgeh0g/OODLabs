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

        virtual void Execute();

        virtual void Unexecute();

        virtual bool IsExecuted();

        virtual std::string GetName();
    };
}
#endif //ICOMMAND_H
