//
// Created by thehedgeh0g on 03.12.24.
//

#ifndef NOQUARTERSTATE_H
#define NOQUARTERSTATE_H
#include "IState.h"

namespace multiGumballMachine
{
class NoQuarterState : public IState
{
public:
    explicit NoQuarterState(IMultiGumballMachine & gumballMachine)
            : m_gumballMachine(gumballMachine)
    {}

    void InsertQuarter() override
    {
        std::cout << "You inserted a quarter\n";
        m_gumballMachine.AddQuarter();
        m_gumballMachine.SetHasQuarterState();
    }

    void EjectQuarter() override
    {
        std::cout << "You haven't inserted a quarter\n";
    }

    void TurnCrank() override
    {
        std::cout << "You turned but there's no quarter\n";
    }

    void Dispense() override
    {
        std::cout << "You need to pay first\n";
    }

    void Refill(unsigned numBalls) override
    {
        std::cout << "Added gumball\n";
        m_gumballMachine.RefillBalls(numBalls);
    }

    [[nodiscard]] std::string ToString() const override
    {
        return "waiting for quarter";
    }

private:
    IMultiGumballMachine & m_gumballMachine;
};
}
#endif //NOQUARTERSTATE_H
