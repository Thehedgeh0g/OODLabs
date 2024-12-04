#pragma once

#include <iostream>
#include <boost/format.hpp>

#include "fmt/format.h"

namespace naive
{
class CGumballMachine
{
public:
	enum class State
	{
		SoldOut,		// Жвачка закончилась
		NoQuarter,		// Нет монетки
		HasQuarter,		// Есть монетка
		Sold,			// Монетка выдана
	};

	CGumballMachine(unsigned count)
		: m_count(count)
		, m_state(count > 0 ? State::NoQuarter : State::SoldOut)
	{
	}

	void InsertQuarter()
	{
		using namespace std;
		switch (m_state)
		{
		case State::SoldOut:
			cout << "You can't insert a quarter, the machine is sold out\n";
			break;
		case State::NoQuarter:
			cout << "You inserted a quarter\n";
			m_quarter++;
			m_state = State::HasQuarter;
			break;
		case State::HasQuarter:
			if (m_quarter < MAX_QUARTER_COUNT)
			{
				m_quarter++;
				std::cout << "You inserted another quarter\n";
			}
			else
			{
				std::cout << "You can't insert another quarter\n";
			}
			break;
		case State::Sold:
			cout << "Please wait, we're already giving you a gumball\n";
			break;
		}
	}

	void EjectQuarters()
	{
		using namespace std;
		switch (m_state)
		{
		case State::HasQuarter:
			cout << "All quarters returned\n";
			m_quarter = 0;
			m_state = State::NoQuarter;
			break;
		case State::NoQuarter:
			cout << "You haven't inserted a quarter\n";
			break;
		case State::Sold:
			cout << "Sorry you already turned the crank\n";
			break;
			case State::SoldOut:
				if (m_quarter > 0)
				{
					m_quarter = 0;
					m_state = State::NoQuarter;
				}
				else
				{
					std::cout << "You can't eject, you haven't inserted a quarter yet\n";
				}
			break;
		}
	}

	void TurnCrank()
	{
		using namespace std;
		switch (m_state)
		{
		case State::SoldOut:
			cout << "You turned but there's no gumballs\n";
			break;
		case State::NoQuarter:
			cout << "You turned but there's no quarter\n";
			break;
		case State::HasQuarter:
			if (m_quarter <= 0)
			{
				std::cout << "No quarters left.\n";
				m_state = State::NoQuarter;
			}
			else
			{
				cout << "You turned...\n";
				m_state = State::Sold;
				Dispense();
			}
			break;
		case State::Sold:
			cout << "Turning twice doesn't get you another gumball\n";
			break;
		}
	}

	void Refill(unsigned numBalls)
	{
		m_count = numBalls;
		m_state = numBalls > 0 ? State::NoQuarter : State::SoldOut;
	}

	[[nodiscard]] std::string ToString()const
	{
		std::string state =
			(m_state == State::SoldOut)    ? "sold out" :
			(m_state == State::NoQuarter)  ? "waiting for quarter" :
			(m_state == State::HasQuarter) ? "waiting for turn of crank"
			                               : "delivering a gumball";
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
							   state
			);
	}

private:
	void Dispense()
	{
		using namespace std;
		switch (m_state)
		{
		case State::Sold:
			cout << "A gumball comes rolling out the slot\n";
			--m_count;
			--m_quarter;
			if (m_count == 0)
			{
				cout << "Oops, out of gumballs\n";
				m_state = State::SoldOut;
			}
			if (m_quarter > 0)
			{
				m_state = State::HasQuarter;
			}
			else
			{
				m_state = State::NoQuarter;
			}
			break;
		case State::NoQuarter:
			cout << "You need to pay first\n";
			break;
		case State::SoldOut:
			std::cout << "No gumball dispensed\n";
			break;
		case State::HasQuarter:
			cout << "No gumball dispensed\n";
			break;
		}
	}

	static constexpr unsigned MAX_QUARTER_COUNT = 5;
	unsigned m_count;
    unsigned m_quarter = 0;
	State m_state = State::SoldOut;
};
}
