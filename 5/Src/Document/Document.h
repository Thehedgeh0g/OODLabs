//
// Created by thehedgeh0g on 22.10.24.
//

#ifndef DOCUMENT_H
#define DOCUMENT_H
#include <vector>

#include "IDocument.h"
#include "./../History/History.h"

namespace Document
{
    class Document : public IDocument
    {
    public:
        void InsertParagraph(const std::string &text, std::optional<size_t> position) override;

        void ReplaceText(const std::string &newText, size_t position) override;

        void InsertImage(const std::string &path, int width, int height, std::optional<size_t> position) override;

        void ResizeImage(int width, int height, size_t position) override;

        [[nodiscard]] DocumentItem::ConstDocumentItem GetItem(size_t index) const override;

        DocumentItem::DocumentItem GetItem(size_t index) override;

        [[nodiscard]] size_t GetItemsCount() const override;

        void DeleteItem(size_t index) override;

        [[nodiscard]] std::string GetTitle() const override;

        void SetTitle(const std::string &title) override;

        [[nodiscard]] bool CanUndo() const override;

        void Undo() override;

        [[nodiscard]] bool CanRedo() const override;

        void Redo() override;

        void Save(const std::string &path) const override;
    private:
        std::string m_title = "title";
        History::History m_history;
        std::vector<DocumentItem::DocumentItem> m_documentItems;
    };
}
#endif //DOCUMENT_H
