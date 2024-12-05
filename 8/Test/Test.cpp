#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./../MultiGumBallMachine/MultiGumballMachine.h"
#include "./../MultiGumBallMachine/IMultiGumballMachine.h"
#include "./../MultiGumBallMachine/State/SoldState.h"
#include "./../MultiGumBallMachine/State/HasQuarterState.h"
#include "./../MultiGumBallMachine/State/NoQuarterState.h"
#include "./../MultiGumBallMachine/State/SoldOutState.h"

using namespace ::testing;
using namespace multiGumballMachine;

class MultiGumballMachineTest : public ::testing::Test
{
};

TEST_F(MultiGumballMachineTest, InitialState)
{
    MultiGumballMachine machine(5);
    EXPECT_EQ(machine.ToString(),
              "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\n           0 quarters\nMachine is waiting for quarter\n");
}

TEST_F(MultiGumballMachineTest, RefillMachine)
{
    MultiGumballMachine machine(0);
    EXPECT_EQ(machine.ToString(),
              "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 0 gumballs\n           0 quarters\nMachine is sold out\n");
    machine.Refill(10);
    EXPECT_EQ(machine.ToString(),
              "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 10 gumballs\n           0 quarters\nMachine is waiting for quarter\n");
    machine.Refill(10);
    EXPECT_EQ(machine.ToString(),
              "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 20 gumballs\n           0 quarters\nMachine is waiting for quarter\n");
}

TEST_F(MultiGumballMachineTest, InsertQuarter)
{
    MultiGumballMachine machine(5);
    machine.InsertQuarter();
    EXPECT_EQ(machine.ToString(),
              "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\n           1 quarter\nMachine is waiting for turn of crank\n");
}

TEST_F(MultiGumballMachineTest, EjectQuarter)
{
    MultiGumballMachine machine(5);
    machine.InsertQuarter();
    machine.EjectQuarters();
    EXPECT_EQ(machine.ToString(),
              "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\n           0 quarters\nMachine is waiting for quarter\n");
}

TEST_F(MultiGumballMachineTest, MultipleEjectQuarter)
{
    MultiGumballMachine machine(5);
    machine.InsertQuarter();
    machine.InsertQuarter();
    machine.EjectQuarters();
    EXPECT_EQ(machine.ToString(),
              "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 5 gumballs\n           0 quarters\nMachine is waiting for quarter\n");
}

TEST_F(MultiGumballMachineTest, DispenseGumball)
{
    MultiGumballMachine machine(5);
    machine.InsertQuarter();
    machine.TurnCrank();
    EXPECT_EQ(machine.ToString(),
              "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 4 gumballs\n           0 quarters\nMachine is waiting for quarter\n");
}

TEST_F(MultiGumballMachineTest, MultipleDispenseGumball)
{
    MultiGumballMachine machine(5);
    machine.InsertQuarter();
    machine.InsertQuarter();
    machine.TurnCrank();
    machine.TurnCrank();
    EXPECT_EQ(machine.ToString(),
              "\nMighty Gumball, Inc.\nC++-enabled Standing Gumball Model #2016\nInventory: 3 gumballs\n           0 quarters\nMachine is waiting for quarter\n");
}

TEST_F(MultiGumballMachineTest, TurnCrankWithoutQuarter)
{
    MultiGumballMachine machine(5);
    testing::internal::CaptureStdout();
    machine.TurnCrank();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "You turned but there's no quarter\nYou need to pay first\n");
}

TEST_F(MultiGumballMachineTest, SoldOutTests)
{
    MultiGumballMachine machine(1);
    machine.InsertQuarter();
    machine.TurnCrank();
    machine.InsertQuarter();
    testing::internal::CaptureStdout();
    machine.TurnCrank();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "You turned but there's no gumballs\nNo gumball dispensed\n");
}

TEST_F(MultiGumballMachineTest, EjectWhenSoldOutAndNoQartersTests)
{
    MultiGumballMachine machine(1);
    machine.InsertQuarter();
    machine.TurnCrank();
    machine.InsertQuarter();
    machine.TurnCrank();
    testing::internal::CaptureStdout();
    machine.EjectQuarters();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "You can't eject, you haven't inserted a quarter yet\n");
}

class MockMultiGumballMachine final : public IMultiGumballMachine
{
public:
    ~MockMultiGumballMachine() override = default;

    MOCK_METHOD(void, ReleaseBall, (), (override));
    MOCK_METHOD(unsigned, GetBallCount, (), (const, override));
    MOCK_METHOD(void, SetSoldOutState, (), (override));
    MOCK_METHOD(void, SetNoQuarterState, (), (override));
    MOCK_METHOD(void, SetSoldState, (), (override));
    MOCK_METHOD(void, SetHasQuarterState, (), (override));

    MOCK_METHOD(unsigned, GetQuarterCount, (), (const, override));
    MOCK_METHOD(unsigned, GetMaxQuarterCount, (), (const, override));
    MOCK_METHOD(void, AddQuarter, (), (override));
    MOCK_METHOD(void, RefillBalls, (unsigned numBalls), (override));
    MOCK_METHOD(void, ReturnAllQuarters, (), (override));
};

TEST(SoldStateTests, DispenseCallsReleaseBallAndTransitionsCorrectly)
{
    MockMultiGumballMachine mockMachine;
    SoldState state(mockMachine);

    EXPECT_CALL(mockMachine, GetQuarterCount()).WillOnce(Return(0));
    EXPECT_CALL(mockMachine, ReleaseBall()).Times(1);
    EXPECT_CALL(mockMachine, GetBallCount()).WillOnce(Return(1));
    EXPECT_CALL(mockMachine, SetNoQuarterState()).Times(1);

    state.Dispense();
}

TEST(SoldStateTests, DispenseTransitionsToSoldOutStateWhenEmpty)
{
    MockMultiGumballMachine mockMachine;
    SoldState state(mockMachine);

    EXPECT_CALL(mockMachine, ReleaseBall()).Times(1);
    EXPECT_CALL(mockMachine, GetBallCount()).WillOnce(Return(0));
    EXPECT_CALL(mockMachine, SetSoldOutState()).Times(1);

    state.Dispense();
}


TEST(SoldStateTests, InsertQuarterPrintsMessage)
{
    MockMultiGumballMachine mockMachine;
    SoldState state(mockMachine);
    testing::internal::CaptureStdout();
    state.InsertQuarter();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Please wait, we're already giving you a gumball\n");
}

TEST(SoldStateTests, EjectQuarterPrintsMessage)
{
    MockMultiGumballMachine mockMachine;
    SoldState state(mockMachine);
    testing::internal::CaptureStdout();
    state.EjectQuarter();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Sorry you already turned the crank\n");
}

TEST(SoldOutStateTests, InsertQuarterPrintsMessage)
{
    MockMultiGumballMachine mockMachine;
    SoldOutState state(mockMachine);
    testing::internal::CaptureStdout();
    state.InsertQuarter();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "You can't insert a quarter, the machine is sold out\n");
}

TEST(SoldOutStateTests, TurnCrankPrintsMessage)
{
    MockMultiGumballMachine mockMachine;
    SoldOutState state(mockMachine);
    testing::internal::CaptureStdout();
    state.TurnCrank();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "You turned but there's no gumballs\n");
}

TEST(HasQuarterStateTests, DispensePrintsMessage)
{
    MockMultiGumballMachine mockMachine;
    HasQuarterState state(mockMachine);
    testing::internal::CaptureStdout();
    state.Dispense();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "No gumball dispensed\n");
}

TEST(NoQuarterStateTests, InsertQuarterTransitionsToHasQuarterState)
{
    MockMultiGumballMachine mockMachine;
    NoQuarterState state(mockMachine);

    EXPECT_CALL(mockMachine, AddQuarter()).Times(1);
    EXPECT_CALL(mockMachine, SetHasQuarterState()).Times(1);
    state.InsertQuarter();
}

TEST_F(MultiGumballMachineTest, RefillWhenHasQuarterState)
{
    MockMultiGumballMachine mockMachine;
    HasQuarterState state(mockMachine);
    EXPECT_CALL(mockMachine, RefillBalls(10));

    state.Refill(10);
}

TEST_F(MultiGumballMachineTest, RefillWhenSoldOutState)
{
    MockMultiGumballMachine mockMachine;
    SoldOutState state(mockMachine);
    EXPECT_CALL(mockMachine, GetBallCount()).WillOnce(testing::Return(0));
    EXPECT_CALL(mockMachine, RefillBalls(5)).Times(1);

    state.Refill(5);
}

TEST_F(MultiGumballMachineTest, RefillWhenMaxQuarterSoldOutState)
{
    MockMultiGumballMachine mockMachine;
    SoldOutState state(mockMachine);
    EXPECT_CALL(mockMachine, GetQuarterCount()).WillOnce(testing::Return(10));
    EXPECT_CALL(mockMachine, GetBallCount()).WillOnce(testing::Return(10));
    EXPECT_CALL(mockMachine, RefillBalls(10)).Times(1);
    EXPECT_CALL(mockMachine, SetHasQuarterState()).Times(1);

    state.Refill(10);
}

TEST_F(MultiGumballMachineTest, RefillWhenZeroQuarterSoldOutState)
{
    MockMultiGumballMachine mockMachine;
    SoldOutState state(mockMachine);
    EXPECT_CALL(mockMachine, GetQuarterCount()).WillOnce(testing::Return(0));
    EXPECT_CALL(mockMachine, GetBallCount()).WillOnce(testing::Return(10));
    EXPECT_CALL(mockMachine, RefillBalls(10)).Times(1);
    EXPECT_CALL(mockMachine, SetNoQuarterState()).Times(1);

    state.Refill(10);
}

TEST_F(MultiGumballMachineTest, EjectWhenZeroQuarterSoldOutState)
{
    MockMultiGumballMachine mockMachine;
    SoldOutState state(mockMachine);
    EXPECT_CALL(mockMachine, GetQuarterCount()).WillOnce(testing::Return(0));

    state.EjectQuarter();
}

TEST_F(MultiGumballMachineTest, EjectWhenMaxQuarterSoldOutState)
{
    MockMultiGumballMachine mockMachine;
    SoldOutState state(mockMachine);
    EXPECT_CALL(mockMachine, GetQuarterCount()).WillOnce(testing::Return(10));
    EXPECT_CALL(mockMachine, ReturnAllQuarters()).Times(1);

    state.EjectQuarter();
}

TEST_F(MultiGumballMachineTest, ToStringSoldOutState)
{
    MockMultiGumballMachine mockMachine;
    SoldOutState state(mockMachine);

    EXPECT_EQ(state.ToString(), "sold out");
}

TEST_F(MultiGumballMachineTest, InsertWhenHasQuarterState)
{
    MockMultiGumballMachine mockMachine;
    HasQuarterState state(mockMachine);
    EXPECT_CALL(mockMachine, GetQuarterCount()).WillOnce(testing::Return(10));
    EXPECT_CALL(mockMachine, GetMaxQuarterCount()).WillOnce(testing::Return(10));

    testing::internal::CaptureStdout();
    state.InsertQuarter();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "You can't insert another quarter\n");
}

TEST_F(MultiGumballMachineTest, TurnTrunkWhenHasQuarterState)
{
    MockMultiGumballMachine mockMachine;
    HasQuarterState state(mockMachine);
    EXPECT_CALL(mockMachine, GetQuarterCount()).WillOnce(testing::Return(0));
    EXPECT_CALL(mockMachine, SetNoQuarterState()).Times(1);

    testing::internal::CaptureStdout();
    state.TurnCrank();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "No quarters left.\n");
}

TEST_F(MultiGumballMachineTest, RefillWhenNoQuarterState)
{
    MockMultiGumballMachine mockMachine;
    NoQuarterState state(mockMachine);
    EXPECT_CALL(mockMachine, RefillBalls(10)).Times(1);

    testing::internal::CaptureStdout();
    state.Refill(10);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Added gumball\n");
}

TEST_F(MultiGumballMachineTest, EjectWhenNoQuarterState)
{
    MockMultiGumballMachine mockMachine;
    NoQuarterState state(mockMachine);

    testing::internal::CaptureStdout();
    state.EjectQuarter();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "You haven't inserted a quarter\n");
}

TEST_F(MultiGumballMachineTest, TurnCrankWhenSoldState)
{
    MockMultiGumballMachine mockMachine;
    SoldState state(mockMachine);

    testing::internal::CaptureStdout();
    state.TurnCrank();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Turning twice doesn't get you another gumball\n");
}

TEST_F(MultiGumballMachineTest, RefillWhenSoldState)
{
    MockMultiGumballMachine mockMachine;
    SoldState state(mockMachine);

    testing::internal::CaptureStdout();
    state.Refill(10);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Not added gumball when giving you a gumball\n");
}

TEST_F(MultiGumballMachineTest, StringSoldState)
{
    MockMultiGumballMachine mockMachine;
    SoldState state(mockMachine);

    state.EjectQuarter();
    EXPECT_EQ(state.ToString(), "delivering a gumball");
}
