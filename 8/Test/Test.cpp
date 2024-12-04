//
// Created by thehedgeh0g on 03.12.24.
//
#include <gtest/gtest.h>
#include "../MultiGumBallMachine/MultiGumballMachine.h"
#include "../MultiGumBallMachine/Naive/NaiveGumBallMachine.h"


class NaiveMultiGumballMachineTest : public ::testing::Test
{
};

// Тест начального состояния автомата
TEST_F(NaiveMultiGumballMachineTest, InitialState)
{
    auto machine = naive::CGumballMachine(5);
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\n           0 quarters\nMachine is waiting for quarter\n");
}

// Тест добавления монеты
TEST_F(NaiveMultiGumballMachineTest, InsertQuarter)
{
    auto machine = naive::CGumballMachine(5);
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\n           0 quarters\nMachine is waiting for quarter\n");
    EXPECT_NO_THROW(machine.InsertQuarter());
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\n           1 quarter\nMachine is waiting for turn of crank\n");
    EXPECT_NO_THROW(machine.TurnCrank());
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 4 gumballs\n           0 quarters\nMachine is waiting for quarter\n");
}

// Тест возврата монеты
TEST_F(NaiveMultiGumballMachineTest, EjectQuarter)
{
    auto machine = naive::CGumballMachine(5);
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\n           0 quarters\nMachine is waiting for quarter\n");
    EXPECT_NO_THROW(machine.InsertQuarter());
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\n           1 quarter\nMachine is waiting for turn of crank\n");
    EXPECT_NO_THROW(machine.EjectQuarters());
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\n           0 quarters\nMachine is waiting for quarter\n");
}

// Тест возврата нескольких монет
TEST_F(NaiveMultiGumballMachineTest, MultipleEjectQuarter)
{
    auto machine = naive::CGumballMachine(5);
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\n           0 quarters\nMachine is waiting for quarter\n");
    EXPECT_NO_THROW(machine.InsertQuarter());
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\n           1 quarter\nMachine is waiting for turn of crank\n");
    EXPECT_NO_THROW(machine.InsertQuarter());
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\n           2 quarters\nMachine is waiting for turn of crank\n");
    EXPECT_NO_THROW(machine.EjectQuarters());
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\n           0 quarters\nMachine is waiting for quarter\n");
}

// Тест продажи жвачки
TEST_F(NaiveMultiGumballMachineTest, DispenseGumball)
{
    auto machine = naive::CGumballMachine(5);
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\n           0 quarters\nMachine is waiting for quarter\n");
    EXPECT_NO_THROW(machine.InsertQuarter());
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\n           1 quarter\nMachine is waiting for turn of crank\n");
    EXPECT_NO_THROW(machine.TurnCrank());
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 4 gumballs\n           0 quarters\nMachine is waiting for quarter\n");
    EXPECT_NO_THROW(machine.EjectQuarters());
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 4 gumballs\n           0 quarters\nMachine is waiting for quarter\n");
}

// Тест продажи нескольких жвачек
TEST_F(NaiveMultiGumballMachineTest, MultipleDispenseGumball)
{
    auto machine = naive::CGumballMachine(5);
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\n           0 quarters\nMachine is waiting for quarter\n");
    EXPECT_NO_THROW(machine.InsertQuarter());
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\n           1 quarter\nMachine is waiting for turn of crank\n");
    EXPECT_NO_THROW(machine.InsertQuarter());
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\n           2 quarters\nMachine is waiting for turn of crank\n");
    EXPECT_NO_THROW(machine.TurnCrank());
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 4 gumballs\n           1 quarter\nMachine is waiting for turn of crank\n");
    EXPECT_NO_THROW(machine.TurnCrank());
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 3 gumballs\n           0 quarters\nMachine is waiting for quarter\n");
    EXPECT_NO_THROW(machine.EjectQuarters());
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 3 gumballs\n           0 quarters\nMachine is waiting for quarter\n");
}

// Тест на "нет монеты"
TEST_F(NaiveMultiGumballMachineTest, TurnCrankWithoutQuarter)
{
    auto machine = naive::CGumballMachine(5);
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\n           0 quarters\nMachine is waiting for quarter\n");
    EXPECT_NO_THROW(machine.TurnCrank());
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\n           0 quarters\nMachine is waiting for quarter\n");
    EXPECT_NO_THROW(machine.TurnCrank());
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\n           0 quarters\nMachine is waiting for quarter\n");
}

class MultiGumballMachineTest : public ::testing::Test
{
};

// Тест начального состояния автомата
TEST_F(MultiGumballMachineTest, InitialState)
{
    auto machine = multiGumballMachine::MultiGumballMachine(5);
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\n           0 quarters\nMachine is waiting for quarter\n");
}

// Тест добавления монеты
TEST_F(MultiGumballMachineTest, InsertQuarter)
{
    auto machine = multiGumballMachine::MultiGumballMachine(5);
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\n           0 quarters\nMachine is waiting for quarter\n");
    EXPECT_NO_THROW(machine.InsertQuarter());
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\n           1 quarter\nMachine is waiting for turn of crank\n");
    EXPECT_NO_THROW(machine.TurnCrank());
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 4 gumballs\n           0 quarters\nMachine is waiting for quarter\n");
}

// Тест возврата монеты
TEST_F(MultiGumballMachineTest, EjectQuarter)
{
    auto machine = multiGumballMachine::MultiGumballMachine(5);
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\n           0 quarters\nMachine is waiting for quarter\n");
    EXPECT_NO_THROW(machine.InsertQuarter());
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\n           1 quarter\nMachine is waiting for turn of crank\n");
    EXPECT_NO_THROW(machine.EjectQuarters());
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\n           0 quarters\nMachine is waiting for quarter\n");
}

// Тест возврата нескольких монет
TEST_F(MultiGumballMachineTest, MultipleEjectQuarter)
{
    auto machine = multiGumballMachine::MultiGumballMachine(5);
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\n           0 quarters\nMachine is waiting for quarter\n");
    EXPECT_NO_THROW(machine.InsertQuarter());
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\n           1 quarter\nMachine is waiting for turn of crank\n");
    EXPECT_NO_THROW(machine.InsertQuarter());
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\n           2 quarters\nMachine is waiting for turn of crank\n");
    EXPECT_NO_THROW(machine.EjectQuarters());
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\n           0 quarters\nMachine is waiting for quarter\n");
}

// Тест продажи жвачки
TEST_F(MultiGumballMachineTest, DispenseGumball)
{
    auto machine = multiGumballMachine::MultiGumballMachine(5);
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\n           0 quarters\nMachine is waiting for quarter\n");
    EXPECT_NO_THROW(machine.InsertQuarter());
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\n           1 quarter\nMachine is waiting for turn of crank\n");
    EXPECT_NO_THROW(machine.TurnCrank());
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 4 gumballs\n           0 quarters\nMachine is waiting for quarter\n");
    EXPECT_NO_THROW(machine.EjectQuarters());
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 4 gumballs\n           0 quarters\nMachine is waiting for quarter\n");
}

// Тест продажи нескольких жвачек
TEST_F(MultiGumballMachineTest, MultipleDispenseGumball)
{
    auto machine = multiGumballMachine::MultiGumballMachine(5);
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\n           0 quarters\nMachine is waiting for quarter\n");
    EXPECT_NO_THROW(machine.InsertQuarter());
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\n           1 quarter\nMachine is waiting for turn of crank\n");
    EXPECT_NO_THROW(machine.InsertQuarter());
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\n           2 quarters\nMachine is waiting for turn of crank\n");
    EXPECT_NO_THROW(machine.TurnCrank());
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 4 gumballs\n           1 quarter\nMachine is waiting for turn of crank\n");
    EXPECT_NO_THROW(machine.TurnCrank());
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 3 gumballs\n           0 quarters\nMachine is waiting for quarter\n");
    EXPECT_NO_THROW(machine.EjectQuarters());
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 3 gumballs\n           0 quarters\nMachine is waiting for quarter\n");
}

// Тест на "нет монеты"
TEST_F(MultiGumballMachineTest, TurnCrankWithoutQuarter)
{
    auto machine = multiGumballMachine::MultiGumballMachine(5);
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\n           0 quarters\nMachine is waiting for quarter\n");
    EXPECT_NO_THROW(machine.TurnCrank());
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\n           0 quarters\nMachine is waiting for quarter\n");
    EXPECT_NO_THROW(machine.TurnCrank());
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\n           0 quarters\nMachine is waiting for quarter\n");
}

// Тест на заполнение автомата
TEST(MultiGumballMachineEdgeTest, EmptyMachine)
{
    multiGumballMachine::MultiGumballMachine emptyMachine(0); // Создаем пустой автомат
    EXPECT_NO_THROW(emptyMachine.InsertQuarter()); // Не должно позволять вставить монету
    EXPECT_NO_THROW(emptyMachine.TurnCrank()); // Нельзя повернуть ручку
    EXPECT_NO_THROW(emptyMachine.EjectQuarters()); // Монету тоже нельзя вернуть
}