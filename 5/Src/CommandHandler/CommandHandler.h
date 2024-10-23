//
// Created by thehedgeh0g on 23.10.24.
//

#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "../Command/ICommand.h"

namespace CommandHandler
{
    class CommandHandler
    {
    public:
        void ExecuteCommand(std::string command, std::unique_ptr<Command::ICommand> macroCommand)
        {
        }

    private:

        bool m_isMacroCommandInProgress;

    };
} // CommandHandler

#endif //COMMANDHANDLER_H
