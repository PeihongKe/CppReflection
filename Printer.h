#pragma once

#include <string>
#include <memory>
#include <exception>

class Printer
{
public:
	virtual std::string Print(void *) const = 0;
};


class IntPrinter : public Printer
{
public:
	std::string Print(void * data) const override
	{
		auto value = static_cast<int*>(data);
		return std::to_string(*value);
	}
};


class DoublePrinter : public Printer
{
public:
	std::string Print(void * data) const override
	{
		auto value = static_cast<double*>(data);
		return std::to_string(*value);
	}
};


std::shared_ptr<Printer> getPrinter(const std::string typeName)
{
	if (typeName == "int")
		return std::make_shared<IntPrinter>();
	else if (typeName == "double")
		return std::make_shared<DoublePrinter>();
	else
		throw std::exception("only support int and double printers");
}

