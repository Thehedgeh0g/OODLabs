//
// Created by thehedgeh0g on 22.10.24.
//

#ifndef INSERTPARAGRAPHCOMMAND_H
#define INSERTPARAGRAPHCOMMAND_H
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "AbstractCommand.h"
#include "./../DocumentItem/DocumentItem.h"

namespace Command
{
    class InsertParagraphCommand : public AbstractCommand
    {
    public:
        static constexpr std::string name = "InsertParagraph";

        InsertParagraphCommand(
            std::vector<DocumentItem::DocumentItem> &documentItems,
            std::string text,
            const std::optional<size_t> position
        ) :
            m_documentItems(documentItems),
            m_text(std::move(text)),
            m_position(position)
        {
            m_name = "InsertParagraphCommand";
        };

    protected:
        void DoExecute() override;

        void DoUnexecute() override;

    private:
        std::vector<DocumentItem::DocumentItem> &m_documentItems;
        std::string m_text;
        std::optional<size_t> m_position;
    };
}
#endif //INSERTPARAGRAPHCOMMAND_H
