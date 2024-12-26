//
// Created by thehedgeh0g on 22.10.24.
//

#ifndef ABSTRACTCOMMAND_H
#define ABSTRACTCOMMAND_H
#include <string>

#include "ICommand.h"

namespace History
{
    class AbstractCommand : public ICommand
    {
    public:
        ~AbstractCommand() override = default;

        void Execute() override;

        void Unexecute() override;

        bool ReplaceEdit(const ICommand &edit) override;

        [[nodiscard]] bool IsExecuted() const override;

        [[nodiscard]] std::string GetName() const override;

    protected:
        virtual void DoExecute() = 0;

        virtual void DoUnexecute() = 0;

        bool m_isExecuted = false;

        std::string m_name;
    };
}
#endif //ABSTRACTCOMMAND_H
