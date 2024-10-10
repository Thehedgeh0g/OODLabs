#pragma once

#include <utility>

#include "IBeverage.h"

// Базовая реализация напитка, предоставляющая его описание
class CBeverage : public IBeverage
{
public:
	explicit CBeverage(std::string  description)
		:m_description(std::move(description))
	{}

	[[nodiscard]] std::string GetDescription()const override
	{
		return m_description;
	}

protected:
	void SetDescription(const std::string& description)
	{
		m_description = description;
	}

private:
	std::string m_description;
};

// Кофе
class CCoffee : public CBeverage
{
public:

	explicit CCoffee(const std::string& description = "Coffee", const int size = 1)
		:CBeverage(description), m_size(size)
	{}

	[[nodiscard]] double GetCost() const override
	{
		return (m_size == 2) ? 100 : 70;
	}

	[[nodiscard]] std::string GetDescription() const override
	{
		std::string portion = (m_size == 2) ? " (Double portion)" : " (Standard portion)";
		return CBeverage::GetDescription() + portion;
	}

protected:
	int m_size;
};

// Капуччино
class CCappuccino : public CCoffee
{
public:
	explicit CCappuccino(const int size = 1)
		:CCoffee("Cappuccino", size)
	{}

	[[nodiscard]] double GetCost() const override
	{
		return (m_size == 2) ? 120 : 80;
	}
};

// Латте
class CLatte : public CCoffee
{
public:
	explicit CLatte(const int size = 1)
		:CCoffee("Latte", size)
	{}

	[[nodiscard]] double GetCost() const override
	{
		return (m_size == 2) ? 130 : 90;
	}
};

// Чай
class CTea : public CBeverage
{
public:
	enum class TeaType: int
	{
		Black = 1,
		Green = 2,
		Herbal = 3,
		Red = 4
	};

	explicit CTea(const int type = 0)
		:CBeverage(GetTeaTypeName(static_cast<TeaType>(type))), m_teaType(static_cast<TeaType>(type))
	{}

	[[nodiscard]] std::string GetDescription() const override
	{
		return CBeverage::GetDescription() + " Tea";
	}

	[[nodiscard]] double GetCost() const override
	{
		return 30;
	}

private:
	TeaType m_teaType;

	[[nodiscard]] static std::string GetTeaTypeName(const TeaType type) {
		switch (type)
		{
		case TeaType::Black: return "Black";
		case TeaType::Green: return "Green";
		case TeaType::Herbal: return "Herbal";
		case TeaType::Red: return "Red";
		default: return "Unknown";
		}
	}
};

// Молочный коктейль
class CMilkshake : public CBeverage
{
public:
	enum class PortionSize: int
	{
		Small = 1,
		Medium = 2,
		Large = 3
	};

	explicit CMilkshake(const int size = 2)
		:CBeverage(GetPortionSizeName(static_cast<PortionSize>(size)) + " Milkshake"), m_size(static_cast<PortionSize>(size))
	{}

	[[nodiscard]] double GetCost() const override
	{
		switch (m_size)
		{
		case PortionSize::Small: return 50;
		case PortionSize::Medium: return 60;
		case PortionSize::Large: return 80;
		default: return 60;
		}
	}

private:
	PortionSize m_size;

	[[nodiscard]] static std::string GetPortionSizeName(const PortionSize size) {
		switch (size)
		{
		case PortionSize::Small: return "Small";
		case PortionSize::Medium: return "Medium";
		case PortionSize::Large: return "Large";
		default: return "Medium";
		}
	}
};
