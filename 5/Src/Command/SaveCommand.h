//
// Created by thehedgeh0g on 22.10.24.
//

#ifndef SAVECOMMAND_H
#define SAVECOMMAND_H
#include <utility>
#include <vector>

#include "AbstractCommand.h"
#include "../DocumentItem/DocumentItem.h"

namespace Command
{
    class SaveCommand : public AbstractCommand
    {
    public:
        SaveCommand(
            const std::vector<DocumentItem::DocumentItem> &documentItems,
            std::string path,
            std::string title
        ) : m_documentItems(documentItems),
            m_path(std::move(path)),
            m_title(std::move(title))
        {
            m_name = "SaveCommand";
        }

    protected:
        void DoExecute() override;

        void DoUnexecute() override;

    private:
        static std::string EscapeHtml(const std::string &text);

        std::vector<DocumentItem::DocumentItem> m_documentItems;
        std::string m_path;
        std::string m_title;
    };
}
#endif //SAVECOMMAND_H
