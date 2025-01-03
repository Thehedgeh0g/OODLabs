//
// Created by thehedgeh0g on 23.10.24.
//
#include "Client.h"

void Client::InsertParagraph(const std::string &pos, const std::string &text) const
{
    m_document->InsertParagraph(text, ParsePosition(pos));
}

void Client::InsertImage(const std::string &pos, const std::string &width, const std::string &height, const std::string &path) const
{
    m_document->InsertImage(path, std::stoi(width), std::stoi(height), ParsePosition(pos));
}

void Client::SetTitle(const std::string &newTitle) const
{
    m_document->SetTitle(newTitle);
}

void Client::List(std::ostream &output) const
{
    output << "Title: " << m_document->GetTitle() << "\n";
    for (int i = 0; i < m_document->GetItemsCount(); i++)
    {
        auto documentItem = m_document->GetItem(i);
        if (auto paragraph = documentItem.GetParagraph(); paragraph != nullptr)
        {
            output << (i + 1) << ". Paragrpah: " << paragraph->GetText() << "\n";
        }

        if (auto image = documentItem.GetImage(); image != nullptr)
        {
            output << (i + 1) << ". Image: " << image->GetWidth() << " " << image->GetHeight() << " " << image->GetPath() << "\n";
        }
    }
}

void Client::ReplaceText(const std::string &pos, const std::string &text) const
{
    const auto position = ParsePosition(pos);
    if (!position.has_value())
    {
        throw std::invalid_argument("Invalid position");
    }
    m_document->ReplaceText(text, position.value());
}

void Client::ResizeImage(const std::string &pos, const std::string &width, const std::string &height) const
{
    const auto position = ParsePosition(pos);
    if (!position.has_value())
    {
        throw std::invalid_argument("Invalid position");
    }
    m_document->ResizeImage(std::stoi(width), std::stoi(height), position.value());
}

void Client::DeleteItem(const std::string &pos) const
{
    auto position = ParsePosition(pos);
    if (!position.has_value())
    {
        throw std::invalid_argument("Invalid position");
    }
    m_document->DeleteItem(position.value());
}

void Client::Help(std::ostream &output)
{
    output << "Commands:\nInsertParagraph <позиция>|end <текст параграфа>\n"
                 "InsertImage <позиция>|end <ширина> <высота> <путь к файлу изображения>\n"
                 "SetTitle <заголовок документа>\n"
                 "List\n"
                 "ReplaceText <позиция> <текст параграфа>\n"
                 "ResizeImage <позиция> <ширина> <высота>\n"
                 "DeleteItem <позиция>\n"
                 "Help\n"
                 "Undo\n"
                 "Redo\n"
                 "Save <путь>" ;
}

void Client::Undo(std::ostream &output) const
{
    if (m_document->CanUndo())
    {
        m_document->Undo();
    }
    else
    {
        output << "Can't undo" << std::endl;
    }
}

void Client::Redo(std::ostream &output) const
{
    if (m_document->CanRedo())
    {
        m_document->Redo();
    }
    else
    {
        output << "Can't redo" << std::endl;
    }
}

void Client::Save(const std::string &path)
{
    m_document->Save(path);
}

std::optional<size_t> Client::ParsePosition(const std::string &pos)
{
    return pos == "end" ? std::nullopt : std::optional<size_t>(std::stoi(pos));
}

void Client::ExecuteCommand(std::string command, std::ostream &output)
{
    {
        size_t pos;
        std::vector<std::string> commandParams;
        while ((pos = command.find(DATA_DELIMITER)) != std::string::npos)
        {
            std::string token = command.substr(0, pos);
            commandParams.push_back(token);
            command.erase(0, pos + DATA_DELIMITER.length());
        }
        commandParams.push_back(command);
        auto it = m_figureMap.find(commandParams[0]);
        if (it != m_figureMap.end())
        {
            switch (it->second)
            {
                case 0:
                    return InsertParagraph(commandParams[1], commandParams[2]);
                case 1:
                    return InsertImage(commandParams[1], commandParams[2], commandParams[3], commandParams[4]);
                case 2:
                    return SetTitle(commandParams[1]);
                case 3:
                    return List(output);
                case 4:
                    return ReplaceText(commandParams[1], commandParams[2]);
                case 5:
                    return ResizeImage(commandParams[1], commandParams[2], commandParams[3]);
                case 6:
                    return DeleteItem(commandParams[1]);
                case 7:
                    return Help(output);
                case 8:
                    return Undo(output);
                case 9:
                    return Redo(output);
                case 10:
                    return Save(commandParams[1]);
                default:
                    throw std::invalid_argument("Unknown command");
            }
        }
        throw std::invalid_argument("Unknown command");
    }
}
