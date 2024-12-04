//
// Created by thehedgeh0g on 03.12.24.
//

#ifndef ISTATE_H
#define ISTATE_H

#include <string>
#include <iostream>

namespace multiGumballMachine
{
class IState
{
public:
    virtual void InsertQuarter() = 0;

    virtual void EjectQuarter() = 0;

    virtual void TurnCrank() = 0;

    virtual void Dispense() = 0;

    virtual void Refill(unsigned numBalls) = 0;

    [[nodiscard]] virtual std::string ToString() const = 0;

    virtual ~IState() = default;
};
}

#endif //ISTATE_H
