//
// Created by thehedgeh0g on 22.10.24.
//

#ifndef CLIENT_H
#define CLIENT_H
#include <iostream>
#include <utility>

#include "../Command/MacroCommand.h"
#include "../Document/IDocument.h"

class Client
{
public:
    explicit Client(std::unique_ptr<Document::IDocument> document): m_document(std::move(document))
    {
    };

    void Run(std::istream &input, std::ostream &output)
    {
        std::string line;
        while (true)
        {
            std::getline(input, line);
            if (line == "exit")
            {
                return;
            }
            try
            {
                ExecuteCommand(line, output);
            }
            catch (std::exception &e)
            {
                output << e.what() << "\n";
            }
        }
    }

private:
    void InsertParagraph(const std::string &pos, const std::string &text) const;

    void InsertImage(const std::string &pos, const std::string &width, const std::string &height,
                     const std::string &path) const;

    void SetTitle(const std::string &newTitle) const;

    void List(std::ostream &output) const;

    void ReplaceText(const std::string &pos, const std::string &text) const;

    void ResizeImage(const std::string &pos, const std::string &width, const std::string &height) const;

    void DeleteItem(const std::string &pos) const;

    void Help(std::ostream &output);

    void Undo(std::ostream &output) const;

    void Redo(std::ostream &output) const;

    void Save(const std::string &path);

    static std::optional<size_t> ParsePosition(const std::string &pos);

    void ExecuteCommand(std::string command, std::ostream &output);

    const std::string DATA_DELIMITER = " ";

    std::unordered_map<std::string, int> m_figureMap = {
        {"InsertParagraph", 0},
        {"InsertImage", 1},
        {"SetTitle", 2},
        {"List", 3},
        {"ReplaceText", 4},
        {"ResizeImage", 5},
        {"DeleteItem", 6},
        {"Help", 7},
        {"Undo", 8},
        {"Redo", 9},
        {"Save", 10},
    };

    std::unique_ptr<Document::IDocument> m_document;
};

#endif //CLIENT_H
