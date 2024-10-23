//
// Created by thehedgeh0g on 23.10.24.
//
#include "Document.h"

#include "../Command/EditParagraphCommand.h"
#include "../Command/InsertImageCommand.h"
#include "../Command/InsertParagraphCommand.h"
#include "./../Command/SaveCommand.h"
#include "./../Command/ResizeImageCommand.h"
#include "./../Command/DeleteCommand.h"
#include "./../Command/SetTitleCommand.h"

namespace Document
{
    size_t Document::GetItemsCount() const
    {
        return m_documentItems.size();
    }

    DocumentItem::ConstDocumentItem Document::GetItem(size_t index) const
    {
        return m_documentItems.at(index);
    }

    DocumentItem::DocumentItem Document::GetItem(size_t index)
    {
        return m_documentItems.at(index);
    }

    void Document::DeleteItem(size_t index)
    {
        m_history.AddAndExecuteCommand(std::make_unique<Command::DeleteCommand>(index, m_documentItems));
    }

    std::string Document::GetTitle() const
    {
        return m_title;
    }

    void Document::SetTitle(const std::string &title)
    {
        m_history.AddAndExecuteCommand(std::make_unique<Command::SetTitleCommand>(m_title, title));
    }

    bool Document::CanUndo() const
    {
        return m_history.CanUndo();
    }

    void Document::Undo()
    {
        m_history.Undo();
    }

    bool Document::CanRedo() const
    {
        return m_history.CanRedo();
    }

    void Document::Redo()
    {
        m_history.Redo();
    }

    void Document::Save(const std::string &path) const
    {
        std::make_unique<Command::SaveCommand>(m_documentItems, path, m_title)->Execute();
    }

    void Document::InsertParagraph(const std::string &text, std::optional<size_t> position)
    {
        m_history.AddAndExecuteCommand(std::make_unique<Command::InsertParagraphCommand>(m_documentItems, text, position));
    }

    void Document::ReplaceText(const std::string &newText, size_t position)
    {
        m_history.AddAndExecuteCommand(std::make_unique<Command::EditParagraphCommand>(position, m_documentItems, newText));
    }

    void Document::InsertImage(const std::string &path, int width, int height, std::optional<size_t> position)
    {
        m_history.AddAndExecuteCommand(std::make_unique<Command::InsertImageCommand>(position, m_documentItems, path, width, height));
    }

    void Document::ResizeImage(int width, int height, size_t position)
    {
        m_history.AddAndExecuteCommand(std::make_unique<Command::ResizeImageCommand>(m_documentItems, width, height, position));
    }
}
