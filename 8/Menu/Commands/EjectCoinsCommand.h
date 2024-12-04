//
// Created by thehedgeh0g on 03.12.24.
//

#ifndef EJECTCOINSCOMMAND_H
#define EJECTCOINSCOMMAND_H
#include "ICommand.h"
#include "../../MultiGumBallMachine/MultiGumballMachine.h"

namespace menu
{
class EjectCoinsCommand : public Command {
public:
    explicit EjectCoinsCommand(multiGumballMachine::MultiGumballMachine& machine) : machine(machine) {}
    bool execute() override {
        machine.EjectQuarters();
        return false;
    }

private:
    multiGumballMachine::MultiGumballMachine& machine;
};
}
#endif //EJECTCOINSCOMMAND_H
