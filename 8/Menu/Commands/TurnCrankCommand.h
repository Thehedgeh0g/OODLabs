//
// Created by thehedgeh0g on 03.12.24.
//

#ifndef TURNCRANKCOMMAND_H
#define TURNCRANKCOMMAND_H
#include "ICommand.h"
#include "../../MultiGumBallMachine/MultiGumballMachine.h"

namespace menu
{
class TurnCrankCommand : public Command {
public:
    explicit TurnCrankCommand(multiGumballMachine::MultiGumballMachine& machine) : machine(machine) {}
    bool execute() override {
        machine.TurnCrank();
        return false;
    }

private:
    multiGumballMachine::MultiGumballMachine& machine;
};
}
#endif //TURNCRANKCOMMAND_H
