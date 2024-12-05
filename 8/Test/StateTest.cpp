//
// Created by thehedgeh0g on 04.12.24.
//
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./../GumBallMachine/GumBallMachineWithState.h"
#include "../MultiGumBallMachine/State/HasQuarterState.h"

using namespace ::testing;
using namespace with_state;


class MultiGumballMachineTest : public ::testing::Test
{
};

// Тест начального состояния автомата
TEST_F(MultiGumballMachineTest, InitialState)
{
    auto machine = CGumballMachine(5);
    EXPECT_EQ(machine.ToString(),
              "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\nMachine is waiting for quarter\n");
}

// Тест добавления монеты
TEST_F(MultiGumballMachineTest, InsertQuarter)
{
    auto machine = CGumballMachine(5);
    EXPECT_EQ(machine.ToString(),
              "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\nMachine is waiting for quarter\n");
    EXPECT_NO_THROW(machine.InsertQuarter());
    EXPECT_EQ(machine.ToString(),
              "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\nMachine is waiting for turn of crank\n");
    EXPECT_NO_THROW(machine.TurnCrank());
    EXPECT_EQ(machine.ToString(),
              "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 4 gumballs\nMachine is waiting for quarter\n");
}

// Тест возврата монеты
TEST_F(MultiGumballMachineTest, EjectQuarter)
{
    auto machine = CGumballMachine(5);
    EXPECT_EQ(machine.ToString(),
              "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\nMachine is waiting for quarter\n");
    EXPECT_NO_THROW(machine.InsertQuarter());
    EXPECT_EQ(machine.ToString(),
              "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\nMachine is waiting for turn of crank\n");
    EXPECT_NO_THROW(machine.EjectQuarter());
    EXPECT_EQ(machine.ToString(),
              "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\nMachine is waiting for quarter\n");
}

// Тест возврата нескольких монет
TEST_F(MultiGumballMachineTest, MultipleEjectQuarter)
{
    auto machine = CGumballMachine(5);
    EXPECT_EQ(machine.ToString(),
              "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\nMachine is waiting for quarter\n");
    EXPECT_NO_THROW(machine.InsertQuarter());
    EXPECT_EQ(machine.ToString(),
              "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\nMachine is waiting for turn of crank\n");
    EXPECT_NO_THROW(machine.InsertQuarter());
    EXPECT_EQ(machine.ToString(),
              "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\nMachine is waiting for turn of crank\n");
    EXPECT_NO_THROW(machine.EjectQuarter());
    EXPECT_EQ(machine.ToString(),
              "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\nMachine is waiting for quarter\n");
}

// Тест продажи жвачки
TEST_F(MultiGumballMachineTest, DispenseGumball)
{
    auto machine = CGumballMachine(5);
    EXPECT_EQ(machine.ToString(),
              "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\nMachine is waiting for quarter\n");
    EXPECT_NO_THROW(machine.InsertQuarter());
    EXPECT_EQ(machine.ToString(),
              "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\nMachine is waiting for turn of crank\n");
    EXPECT_NO_THROW(machine.TurnCrank());
    EXPECT_EQ(machine.ToString(),
              "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 4 gumballs\nMachine is waiting for quarter\n");
    EXPECT_NO_THROW(machine.EjectQuarter());
    EXPECT_EQ(machine.ToString(),
              "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 4 gumballs\nMachine is waiting for quarter\n");
}

// Тест продажи нескольких жвачек
TEST_F(MultiGumballMachineTest, MultipleDispenseGumball)
{
    auto machine = CGumballMachine(5);
    EXPECT_EQ(machine.ToString(),
              "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\nMachine is waiting for quarter\n");
    EXPECT_NO_THROW(machine.InsertQuarter());
    EXPECT_EQ(machine.ToString(),
              "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\nMachine is waiting for turn of crank\n");
    EXPECT_NO_THROW(machine.InsertQuarter());
    EXPECT_EQ(machine.ToString(),
              "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\nMachine is waiting for turn of crank\n");
    EXPECT_NO_THROW(machine.TurnCrank());
    EXPECT_EQ(machine.ToString(),
              "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 4 gumballs\nMachine is waiting for quarter\n");
    EXPECT_NO_THROW(machine.TurnCrank());
    EXPECT_EQ(machine.ToString(),
              "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 4 gumballs\nMachine is waiting for quarter\n");
    EXPECT_NO_THROW(machine.EjectQuarter());
    EXPECT_EQ(machine.ToString(),
              "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 4 gumballs\nMachine is waiting for quarter\n");
}

// Тест на "нет монеты"
TEST_F(MultiGumballMachineTest, TurnCrankWithoutQuarter)
{
    auto machine = CGumballMachine(5);
    EXPECT_EQ(machine.ToString(),
              "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\nMachine is waiting for quarter\n");
    EXPECT_NO_THROW(machine.TurnCrank());
    EXPECT_EQ(machine.ToString(),
              "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\nMachine is waiting for quarter\n");
    EXPECT_NO_THROW(machine.TurnCrank());
    EXPECT_EQ(machine.ToString(),
              "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\nMachine is waiting for quarter\n");
}

// Тест на "Распродано"
TEST_F(MultiGumballMachineTest, SoldOutTests)
{
    auto machine = CGumballMachine(1);
    EXPECT_EQ(machine.ToString(),
              "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 1 gumball\nMachine is waiting for quarter\n");
    EXPECT_NO_THROW(machine.InsertQuarter());
    EXPECT_EQ(machine.ToString(),
              "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 1 gumball\nMachine is waiting for turn of crank\n");
    EXPECT_NO_THROW(machine.TurnCrank());
    EXPECT_EQ(machine.ToString(),
              "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 0 gumballs\nMachine is sold out\n");
    EXPECT_NO_THROW(machine.TurnCrank());
    EXPECT_EQ(machine.ToString(),
              "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 0 gumballs\nMachine is sold out\n");
    EXPECT_NO_THROW(machine.InsertQuarter());
    EXPECT_EQ(machine.ToString(),
              "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 0 gumballs\nMachine is sold out\n");
    EXPECT_NO_THROW(machine.EjectQuarter());
    EXPECT_EQ(machine.ToString(),
              "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 0 gumballs\nMachine is sold out\n");
}

class MockGumballMachine : public IGumballMachine
{
public:
    MOCK_METHOD(void, ReleaseBall, (), (override));
    MOCK_METHOD(unsigned, GetBallCount, (), (const, override));
    MOCK_METHOD(void, SetSoldOutState, (), (override));
    MOCK_METHOD(void, SetNoQuarterState, (), (override));
    MOCK_METHOD(void, SetSoldState, (), (override));
    MOCK_METHOD(void, SetHasQuarterState, (), (override));
};

TEST(SoldStateTests, DispenseCallsReleaseBallAndTransitionsCorrectly)
{
    MockGumballMachine mockMachine;
    CSoldState state(mockMachine);

    EXPECT_CALL(mockMachine, ReleaseBall()).Times(1);
    EXPECT_CALL(mockMachine, GetBallCount()).Times(1).WillOnce(testing::Return(1));
    EXPECT_CALL(mockMachine, SetNoQuarterState()).Times(1);

    state.Dispense();
}

TEST(SoldStateTests, DispenseTransitionsToSoldOutStateWhenEmpty)
{
    MockGumballMachine mockMachine;
    CSoldState state(mockMachine);

    EXPECT_CALL(mockMachine, ReleaseBall()).Times(1);
    EXPECT_CALL(mockMachine, GetBallCount()).Times(1).WillOnce(testing::Return(0));
    EXPECT_CALL(mockMachine, SetSoldOutState()).Times(1);

    state.Dispense();
}

TEST(SoldStateTests, InsertQuarterPrintsMessage)
{
    MockGumballMachine mockMachine;
    CSoldState state(mockMachine);

    EXPECT_EQ(state.ToString(), "delivering a gumball");
    testing::internal::CaptureStdout();
    state.InsertQuarter();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "Please wait, we're already giving you a gumball\n");
}

TEST(SoldStateTests, EjectQuarterPrintsMessage)
{
    MockGumballMachine mockMachine;
    CSoldState state(mockMachine);

    testing::internal::CaptureStdout();
    state.EjectQuarter();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "Sorry you already turned the crank\n");
}

TEST(SoldStateTests, TurnCrunkPrintsMessage)
{
    MockGumballMachine mockMachine;
    CSoldState state(mockMachine);

    testing::internal::CaptureStdout();
    state.TurnCrank();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "Turning twice doesn't get you another gumball\n");
}


TEST(SoldOutStateTests, InsertQuarterPrintsMessage)
{
    MockGumballMachine mockMachine;
    CSoldOutState state(mockMachine);

    testing::internal::CaptureStdout();
    state.InsertQuarter();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "You can't insert a quarter, the machine is sold out\n");
}

TEST(SoldOutStateTests, TurnCrankPrintsMessage)
{
    MockGumballMachine mockMachine;
    CSoldOutState state(mockMachine);

    testing::internal::CaptureStdout();
    state.TurnCrank();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "You turned but there's no gumballs\n");
}

TEST(HasQuarterStateTests, DispensePrintsMessage)
{
    MockGumballMachine mockMachine;
    CHasQuarterState state(mockMachine);

    testing::internal::CaptureStdout();
    state.Dispense();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "No gumball dispensed\n");
}

TEST(HasQuarterStateTests, EjectQuarterTransitionsToNoQuarterState)
{
    MockGumballMachine mockMachine;
    CHasQuarterState state(mockMachine);

    EXPECT_CALL(mockMachine, SetNoQuarterState()).Times(1);

    state.EjectQuarter();
}

TEST(HasQuarterStateTests, TurnCrankTransitionsToSoldState)
{
    MockGumballMachine mockMachine;
    CHasQuarterState state(mockMachine);

    EXPECT_CALL(mockMachine, SetSoldState()).Times(1);

    state.TurnCrank();
}

TEST(NoQuarterStateTests, InsertQuarterTransitionsToHasQuarterState)
{
    MockGumballMachine mockMachine;
    CNoQuarterState state(mockMachine);

    EXPECT_CALL(mockMachine, SetHasQuarterState()).Times(1);

    state.InsertQuarter();
}

TEST(NoQuarterStateTests, TurnCrankPrintsMessage)
{
    MockGumballMachine mockMachine;
    CNoQuarterState state(mockMachine);

    testing::internal::CaptureStdout();
    state.TurnCrank();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "You turned but there's no quarter\n");
}
