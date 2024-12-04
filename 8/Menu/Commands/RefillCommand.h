//
// Created by thehedgeh0g on 03.12.24.
//

#ifndef REFILLCOMMAND_H
#define REFILLCOMMAND_H
#include "ICommand.h"
#include "../../MultiGumBallMachine/MultiGumballMachine.h"

namespace menu
{
class RefillCommand : public Command {
public:
    RefillCommand(multiGumballMachine::MultiGumballMachine& machine, int count) : machine(machine), count(count) {}
    bool execute() override {
        machine.Refill(count);
        return false;
    }

private:
    multiGumballMachine::MultiGumballMachine& machine;
    int count;
};
}
#endif //REFILLCOMMAND_H
