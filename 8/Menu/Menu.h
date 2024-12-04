//
// Created by thehedgeh0g on 04.12.24.
//

#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <map>
#include <memory>
#include <string>

#include "Commands/ICommand.h"

namespace menu
{
class Menu
{
public:
    void addCommand(const std::string &key, const std::string &description, std::shared_ptr<Command> command)
    {
        commands[key] = {description, std::move(command)};
    }

    void show() const
    {
        std::cout << "\nМеню:\n";
        for (const auto &[key, value]: commands)
        {
            std::cout << key << ": " << value.first << '\n';
        }
    }

    bool execute(const std::string &key)
    {
        auto it = commands.find(key);
        if (it != commands.end())
        {
            return it->second.second->execute();
        }
        std::cout << "Неверный выбор. Попробуйте снова.\n";
        return false;
    }

private:
    std::map<std::string, std::pair<std::string, std::shared_ptr<Command> > > commands;
};
}
#endif //MENU_H
