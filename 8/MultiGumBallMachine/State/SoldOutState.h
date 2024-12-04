//
// Created by thehedgeh0g on 03.12.24.
//

#ifndef SOLDOUTSTATE_H
#define SOLDOUTSTATE_H
#include "IState.h"
#include "./../IMultiGumballMachine.h"

namespace multiGumballMachine
{
class SoldOutState : public IState
{
public:
    explicit SoldOutState(IMultiGumballMachine & gumballMachine)
            :m_gumballMachine(gumballMachine)
    {}

    void InsertQuarter() override
    {
        std::cout << "You can't insert a quarter, the machine is sold out\n";
    }

    void EjectQuarter() override
    {
        if (m_gumballMachine.GetQuarterCount() > 0)
        {
            m_gumballMachine.ReturnAllQuarters();
        }
        else
        {
            std::cout << "You can't eject, you haven't inserted a quarter yet\n";
        }
    }

    void TurnCrank() override
    {
        std::cout << "You turned but there's no gumballs\n";
    }

    void Dispense() override
    {
        std::cout << "No gumball dispensed\n";
    }

    void Refill(unsigned numBalls) override
    {
        std::cout << "Added gumball\n";
        m_gumballMachine.RefillBall(numBalls);
        if (m_gumballMachine.GetBallCount() > 0)
        {
            if (m_gumballMachine.GetQuarterCount() > 0)
            {
                m_gumballMachine.SetHasQuarterState();
            }
            else
            {
                m_gumballMachine.SetNoQuarterState();
            }
        }
    }

    [[nodiscard]] std::string ToString() const override
    {
        return "sold out";
    }
private:
    IMultiGumballMachine & m_gumballMachine;
};
}
#endif //SOLDOUTSTATE_H
