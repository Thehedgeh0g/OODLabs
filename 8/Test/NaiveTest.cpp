//
// Created by thehedgeh0g on 04.12.24.
//

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "./../MultiGumBallMachine/Naive/NaiveGumBallMachine.h"
#include "fmt/format.h"

// Базовый тест для автомата с несколькими монетами
class MultiGumballMachineTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        machine = new naive::CGumballMachine(10);
    }

    void TearDown() override
    {
        delete machine;
    }

    naive::CGumballMachine *machine;
};

// Тест начального состояния автомата
TEST_F(MultiGumballMachineTest, InitialState)
{
    EXPECT_EQ(machine->ToString(), R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: 10 gumballs
           0 quarters
Machine is waiting for quarter
)");
}

// Тест на "Refill"
TEST_F(MultiGumballMachineTest, RefillMachine)
{
    machine->Refill(5);
    EXPECT_EQ(machine->ToString(), R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: 15 gumballs
           0 quarters
Machine is waiting for quarter
)");
}

// Тест добавления монеты
TEST_F(MultiGumballMachineTest, InsertQuarter)
{
    machine->InsertQuarter();
    EXPECT_EQ(machine->ToString(), R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: 10 gumballs
           1 quarter
Machine is waiting for turn of crank
)");
}

// Тест возврата монеты
TEST_F(MultiGumballMachineTest, EjectQuarter)
{
    machine->InsertQuarter();
    machine->EjectQuarters();
    EXPECT_EQ(machine->ToString(), R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: 10 gumballs
           0 quarters
Machine is waiting for quarter
)");
}

// Тест возврата нескольких монет
TEST_F(MultiGumballMachineTest, MultipleEjectQuarter)
{
    machine->InsertQuarter();
    machine->InsertQuarter();
    machine->EjectQuarters();
    EXPECT_EQ(machine->ToString(), R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: 10 gumballs
           0 quarters
Machine is waiting for quarter
)");
}

// Тест продажи жвачки
TEST_F(MultiGumballMachineTest, DispenseGumball)
{
    machine->InsertQuarter();
    machine->TurnCrank();
    EXPECT_EQ(machine->ToString(), R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: 9 gumballs
           0 quarters
Machine is waiting for quarter
)");
}

// Тест продажи нескольких жвачек
TEST_F(MultiGumballMachineTest, MultipleDispenseGumball)
{
    machine->InsertQuarter();
    machine->TurnCrank();
    machine->InsertQuarter();
    machine->TurnCrank();
    EXPECT_EQ(machine->ToString(), R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: 8 gumballs
           0 quarters
Machine is waiting for quarter
)");
}

// Тест на "нет монеты"
TEST_F(MultiGumballMachineTest, TurnCrankWithoutQuarter)
{
    machine->TurnCrank();
    EXPECT_EQ(machine->ToString(), R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: 10 gumballs
           0 quarters
Machine is waiting for quarter
)");
}

// Тест на "Распродано"
TEST_F(MultiGumballMachineTest, SoldOutTests)
{
    naive::CGumballMachine soldOutMachine(0);
    EXPECT_EQ(soldOutMachine.ToString(), R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: 0 gumballs
           0 quarters
Machine is sold out
)");
}

// Тест на "Распродано", возврат монеты
TEST_F(MultiGumballMachineTest, EjectWhenSoldOutAndNoQuarters)
{
    naive::CGumballMachine soldOutMachine(0);
    soldOutMachine.EjectQuarters();
    EXPECT_EQ(soldOutMachine.ToString(), R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: 0 gumballs
           0 quarters
Machine is sold out
)");
}
