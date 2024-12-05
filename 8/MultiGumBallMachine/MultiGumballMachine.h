//
// Created by thehedgeh0g on 03.12.24.
//

#ifndef MULTIGUMBALLMACHINE_H
#define MULTIGUMBALLMACHINE_H
#include <string>
#include <fmt/core.h>

#include "IMultiGumballMachine.h"
#include "State/HasQuarterState.h"
#include "State/IState.h"
#include "State/NoQuarterState.h"
#include "State/SoldOutState.h"
#include "State/SoldState.h"

namespace multiGumballMachine
{
class MultiGumballMachine : private IMultiGumballMachine
{
public:
    explicit MultiGumballMachine(unsigned numBalls):
        m_soldState(*this),
        m_soldOutState(*this),
        m_noQuarterState(*this),
        m_hasQuarterState(*this),
        m_state(&m_soldOutState),
        m_count(numBalls)
    {
        if (m_count > 0)
        {
            m_state = &m_noQuarterState;
        }
    }

    ~MultiGumballMachine() override
    = default;

    void EjectQuarters()
    {
        m_state->EjectQuarter();
    }

    void InsertQuarter()
    {
        m_state->InsertQuarter();
    }

    void TurnCrank()
    {
        m_state->TurnCrank();
        m_state->Dispense();
    }

    [[nodiscard]] std::string ToString() const
    {
        return fmt::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: {} gumball{}
           {} quarter{}
Machine is {}
)",
                               m_count,
                               m_count != 1 ? "s" : "",
                               m_quarter,
                               m_quarter != 1 ? "s" : "",
                               m_state->ToString()
            );
    }

    void Refill(unsigned numBalls)
    {
        m_state->Refill(numBalls);
    }

private:
    void ReleaseBall() override
    {
        if (m_count != 0)
        {
            std::cout << "A gumball comes rolling out the slot...\n";

            --m_count;
            --m_quarter;
        }
    }

    [[nodiscard]] unsigned GetBallCount() const override
    {
        return m_count;
    }

    [[nodiscard]] unsigned GetQuarterCount() const override
    {
        return m_quarter;
    }

    [[nodiscard]] unsigned GetMaxQuarterCount() const override
    {
        return MAX_QUARTER_COUNT;
    }

    void AddQuarter() override
    {
        ++m_quarter;
    }

    void RefillBalls(unsigned numBalls) override
    {
        m_count += numBalls;
    }

    void ReturnAllQuarters() override
    {
        std::cout << "Return all quarters\n";

        m_quarter = 0;
    }

    void SetSoldOutState() override
    {
        m_state = &m_soldOutState;
    }

    void SetNoQuarterState() override
    {
        m_state = &m_noQuarterState;
    }

    void SetSoldState() override
    {
        m_state = &m_soldState;
    }

    void SetHasQuarterState() override
    {
        m_state = &m_hasQuarterState;
    }

    static constexpr unsigned MAX_QUARTER_COUNT = 5;
    unsigned m_count = 0;
    unsigned m_quarter = 0;
    SoldState m_soldState;
    SoldOutState m_soldOutState;
    NoQuarterState m_noQuarterState;
    HasQuarterState m_hasQuarterState;
    IState *m_state;
};
}

#endif //MULTIGUMBALLMACHINE_H
