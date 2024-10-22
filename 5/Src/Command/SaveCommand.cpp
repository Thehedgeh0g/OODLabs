//
// Created by thehedgeh0g on 23.10.24.
//
#include "SaveCommand.h"
#include <fstream>
#include <iostream>
#include <filesystem>

namespace Command
{
    void SaveCommand::DoExecute()
    {
        std::string imagesDirectory = m_path + "/images";
        std::filesystem::create_directory(imagesDirectory);

        std::ofstream outFile(m_path + "/document.html");
        if (!outFile.is_open())
        {
            std::cerr << "Failed to open file for saving: " << m_path << std::endl;
            return;
        }

        outFile << "<!DOCTYPE html>\n<html>\n<head>\n<title>" << EscapeHtml(m_title) << "</title>\n</head>\n<body>\n";

        for (auto &item: m_documentItems)
        {
            if (item.GetParagraph())
            {
                outFile << "<p>" << EscapeHtml(item.GetParagraph()->GetText()) << "</p>\n";
            }
            else if (item.GetImage())
            {
                std::string imagePath = "images/" + std::filesystem::path(item.GetImage()->GetPath()).filename().
                                        string();
                remove(imagePath.c_str());

                std::ifstream source(item.GetImage()->GetPath(), std::ios::binary);
                std::ofstream destination(imagesDirectory + "/" + std::filesystem::path(item.GetImage()->GetPath()).filename().string(), std::ios::binary);
                destination << source.rdbuf();
                source.close();
                destination.close();
                outFile << "<img src=\"" << imagePath << "\" width=\"" << item.GetImage()->GetWidth() << "\" height=\""
                        << item.GetImage()->GetHeight() << "\" />\n";
            }
        }

        outFile << "</body>\n</html>";
        outFile.close();
    }

    void SaveCommand::DoUnexecute()
    {
        std::cerr << "SaveCommand cannot be undone." << std::endl;
    }

    std::string SaveCommand::EscapeHtml(const std::string &text)
    {
        std::string escaped;
        for (char c: text)
        {
            switch (c)
            {
                case '<':
                    escaped += "&lt;";
                    break;
                case '>':
                    escaped += "&gt;";
                    break;
                case '&':
                    escaped += "&amp;";
                    break;
                case '"':
                    escaped += "&quot;";
                    break;
                case '\'':
                    escaped += "&apos;";
                    break;
                default:
                    escaped += c;
                    break;
            }
        }
        return escaped;
    }
}
