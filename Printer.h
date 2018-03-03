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

 template<typename T>
 int getTypeSize()
 {
	 typename remove_pointer<T>::type type;
	 return sizeof(type);
 };

class VectorPrinter : public Printer
{
public:
	VectorPrinter(const std::string& elemTypeName) :m_elemTypeName(elemTypeName) {}
	std::string Print(void * data) const override
	{
		//auto value = static_cast<std::vector<ELEMTYPE>*>(data);
		//auto size = value.size();
		//auto innerPrinter = getPrinter(TOSTRING(ELEMTYPE));
		//for (int i = 0; i < size; ++i)
		//{
		//	innerPrinter->Print(*(value + i));
		//}
		//
	}

private:
	std::string m_elemTypeName;

};

//std::shared_ptr<Printer> getPrinter(const MetaField& meta)
//{
//	auto typeName = meta.name();
//	if (typeName == "int")
//		return std::make_shared<IntPrinter>();
//	else if (typeName == "double")
//		return std::make_shared<DoublePrinter>();
//	else if (typeName == "vector")
//	{
//		return std::make_shared<VectorPrinter>();
//	}
//	else
//		throw std::exception("only support int and double printers");
//}
//
