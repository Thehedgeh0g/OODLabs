//
// Created by thehedgeh0g on 22.10.24.
//

#ifndef SETTITLECOMMAND_H
#define SETTITLECOMMAND_H
#include <utility>
#include <vector>

#include "AbstractCommand.h"
#include "./../DocumentItem/DocumentItem.h"

namespace Command
{
    class SetTitleCommand : public AbstractCommand
    {
    public:
        SetTitleCommand(
        std::string & title, std::string  newTitle
        ) :
            m_newTitle(std::move(newTitle)),
            m_title(title)
        {
            m_name = "SetTitleCommand";
        }

        bool ReplaceEdit(const ICommand &edit) override;

    protected:
        void DoExecute() override;

        void DoUnexecute() override;

    private:
        std::string m_newTitle;
        std::string m_prevTitle;
        std::string & m_title;
    };
}
#endif //SETTITLECOMMAND_H
