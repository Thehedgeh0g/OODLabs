//
// Created by thehedgeh0g on 22.10.24.
//

#ifndef DELETECOMMAND_H
#define DELETECOMMAND_H
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "AbstractCommand.h"
#include "./../DocumentItem/DocumentItem.h"

namespace Command
{
    class DeleteCommand : public AbstractCommand
    {

    public:

        DeleteCommand(
            const size_t &position,
            std::vector<DocumentItem::DocumentItem> &documentItems
        ) :
            m_position(position),
            m_documentItems(documentItems)
        {
            m_name = "DeleteCommand";
        }

    protected:
        void DoExecute() override;

        void DoUnexecute() override;

    private:
        size_t m_position;
        std::vector<DocumentItem::DocumentItem>& m_documentItems;
        std::unique_ptr<DocumentItem::DocumentItem> m_documentItem = nullptr;
    };
}
#endif //DELETECOMMAND_H
