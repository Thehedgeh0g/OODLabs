//
// Created by thehedgeh0g on 22.10.24.
//

#ifndef EDITPARAGRAPHCOMMAND_H
#define EDITPARAGRAPHCOMMAND_H
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "AbstractCommand.h"
#include "./../DocumentItem/DocumentItem.h"


namespace Command
{
    class EditParagraphCommand : public AbstractCommand
    {
    public:
        EditParagraphCommand(
            const std::optional<size_t> &position,
            std::vector<DocumentItem::DocumentItem> &documentItems,
            std::string newText
        ) :
            m_position(position),
            m_documentItems(documentItems),
            m_newText(std::move(newText))
        {
            m_name = "EditParagraphCommand";
        }

        bool ReplaceEdit(const ICommand &edit) override;

    protected:
        void DoExecute() override;

        void DoUnexecute() override;

    private:
        std::optional<size_t> m_position;
        std::vector<DocumentItem::DocumentItem>& m_documentItems;
        std::string m_text;
        std::string m_newText;
    };
}

#endif //EDITPARAGRAPHCOMMAND_H
