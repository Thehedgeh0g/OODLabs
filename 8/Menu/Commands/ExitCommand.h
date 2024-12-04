//
// Created by thehedgeh0g on 03.12.24.
//

#ifndef EXITCOMMAND_H
#define EXITCOMMAND_H
#include <iostream>

#include "ICommand.h"

namespace menu
{
class ExitCommand : public Command {
public:
    bool execute() override {
        std::cout << "Выход из программы...\n";
        return true;
    }
};

}
#endif //EXITCOMMAND_H
