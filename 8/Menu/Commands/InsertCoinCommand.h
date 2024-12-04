//
// Created by thehedgeh0g on 03.12.24.
//

#ifndef INSERTCOINCOMMAND_H
#define INSERTCOINCOMMAND_H
#include "ICommand.h"
#include "../../MultiGumBallMachine/MultiGumballMachine.h"

namespace menu
{
class InsertCoinCommand : public Command {
public:
    explicit InsertCoinCommand(multiGumballMachine::MultiGumballMachine& machine) : machine(machine) {}
    bool execute() override {
        machine.InsertQuarter();
        return false;
    }

private:
    multiGumballMachine::MultiGumballMachine& machine;
};
}
#endif //INSERTCOINCOMMAND_H
