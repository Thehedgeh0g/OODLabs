//
// Created by thehedgeh0g on 22.10.24.
//

#ifndef INSERTIMAGECOMMAND_H
#define INSERTIMAGECOMMAND_H
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "AbstractCommand.h"
#include "../DocumentItem/DocumentItem.h"

namespace Command
{
    class InsertImageCommand : public AbstractCommand
    {
    public:
        InsertImageCommand(
            const std::optional<size_t> &position,
            std::vector<DocumentItem::DocumentItem> &documentItems,
            std::string path,
            int width,
            int height
        ) :
            m_position(position),
            m_documentItems(documentItems),
            m_path(std::move(path)),
            m_height(height),
            m_width(width)
        {
            m_name = "InsertImageCommand";
        }

    protected:
        void DoExecute() override;

        void DoUnexecute() override;

    private:
        std::optional<size_t> m_position;
        std::vector<DocumentItem::DocumentItem>& m_documentItems;
        std::string m_path;
        int m_height;
        int m_width;
    };
}
#endif //INSERTIMAGECOMMAND_H
