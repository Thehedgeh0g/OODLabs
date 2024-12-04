//
// Created by thehedgeh0g on 04.12.24.
//
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./../GumBallMachine/GumBallMachineWithState.h"

using namespace ::testing;
using namespace with_state;


class MultiGumballMachineTest : public ::testing::Test
{
};

// Тест начального состояния автомата
TEST_F(MultiGumballMachineTest, InitialState)
{
    auto machine = CGumballMachine(5);
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\nMachine is waiting for quarter\n");
}

// Тест добавления монеты
TEST_F(MultiGumballMachineTest, InsertQuarter)
{
    auto machine = CGumballMachine(5);
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\nMachine is waiting for quarter\n");
    EXPECT_NO_THROW(machine.InsertQuarter());
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\nMachine is waiting for turn of crank\n");
    EXPECT_NO_THROW(machine.TurnCrank());
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 4 gumballs\nMachine is waiting for quarter\n");
}

// Тест возврата монеты
TEST_F(MultiGumballMachineTest, EjectQuarter)
{
    auto machine = CGumballMachine(5);
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\nMachine is waiting for quarter\n");
    EXPECT_NO_THROW(machine.InsertQuarter());
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\nMachine is waiting for turn of crank\n");
    EXPECT_NO_THROW(machine.EjectQuarter());
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\nMachine is waiting for quarter\n");
}

// Тест возврата нескольких монет
TEST_F(MultiGumballMachineTest, MultipleEjectQuarter)
{
    auto machine = CGumballMachine(5);
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\nMachine is waiting for quarter\n");
    EXPECT_NO_THROW(machine.InsertQuarter());
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\nMachine is waiting for turn of crank\n");
    EXPECT_NO_THROW(machine.InsertQuarter());
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\nMachine is waiting for turn of crank\n");
    EXPECT_NO_THROW(machine.EjectQuarter());
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\nMachine is waiting for quarter\n");
}

// Тест продажи жвачки
TEST_F(MultiGumballMachineTest, DispenseGumball)
{
    auto machine = CGumballMachine(5);
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\nMachine is waiting for quarter\n");
    EXPECT_NO_THROW(machine.InsertQuarter());
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\nMachine is waiting for turn of crank\n");
    EXPECT_NO_THROW(machine.TurnCrank());
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 4 gumballs\nMachine is waiting for quarter\n");
    EXPECT_NO_THROW(machine.EjectQuarter());
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 4 gumballs\nMachine is waiting for quarter\n");
}

// Тест продажи нескольких жвачек
TEST_F(MultiGumballMachineTest, MultipleDispenseGumball)
{
    auto machine = CGumballMachine(5);
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\nMachine is waiting for quarter\n");
    EXPECT_NO_THROW(machine.InsertQuarter());
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\nMachine is waiting for turn of crank\n");
    EXPECT_NO_THROW(machine.InsertQuarter());
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\nMachine is waiting for turn of crank\n");
    EXPECT_NO_THROW(machine.TurnCrank());
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 4 gumballs\nMachine is waiting for quarter\n");
    EXPECT_NO_THROW(machine.TurnCrank());
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 4 gumballs\nMachine is waiting for quarter\n");
    EXPECT_NO_THROW(machine.EjectQuarter());
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 4 gumballs\nMachine is waiting for quarter\n");
}

// Тест на "нет монеты"
TEST_F(MultiGumballMachineTest, TurnCrankWithoutQuarter)
{
    auto machine = CGumballMachine(5);
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\nMachine is waiting for quarter\n");
    EXPECT_NO_THROW(machine.TurnCrank());
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\nMachine is waiting for quarter\n");
    EXPECT_NO_THROW(machine.TurnCrank());
    EXPECT_EQ(machine.ToString(), "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\nMachine is waiting for quarter\n");
}

// Тест на заполнение автомата
TEST(MultiGumballMachineEdgeTest, EmptyMachine)
{
    CGumballMachine emptyMachine(0); // Создаем пустой автомат
    EXPECT_NO_THROW(emptyMachine.InsertQuarter()); // Не должно позволять вставить монету
    EXPECT_NO_THROW(emptyMachine.TurnCrank()); // Нельзя повернуть ручку
    EXPECT_NO_THROW(emptyMachine.EjectQuarter()); // Монету тоже нельзя вернуть
}

