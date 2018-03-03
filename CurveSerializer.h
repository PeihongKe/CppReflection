#pragma once
 
#include <string>
#include <memory>
#include <map>
#include <string>
#include <sstream>
#include "Curves.h"

namespace BH
{

	std::string CurveAddressAndName(std::uintptr_t address, bool & exist)
	{
		static std::map<std::uintptr_t, std::string> nameByAddress;
		static int counter = 1;
		if (nameByAddress.find(address) != nameByAddress.end())
		{
			exist = true;
			return nameByAddress[address];
		}
		else
		{
			exist = false;
			auto name = "Curve." + std::to_string(counter);
			nameByAddress[address] = name;
			++counter;
			return name;
		}
	}

	class Printer;
	class IntPrinter;
	class DoublePrinter;
	class StringPrinter;
	class CurvePrinter;

	class SerializerFactory
	{
	public:
		static std::shared_ptr<Printer> getSerializer(const std::string& typeName)
		{
			if (typeName == "int")
			{
				return std::static_pointer_cast<Printer>(std::make_shared<IntPrinter>());
			}
			else if (typeName == "double")
			{
				return std::static_pointer_cast<Printer>(std::make_shared<DoublePrinter>());
			}
			else if (typeName == "string")
			{
				return std::static_pointer_cast<Printer>(std::make_shared<StringPrinter>());
			}
			else if (typeName == "Curve")
			{
				return std::static_pointer_cast<Printer>(std::make_shared<CurvePrinter>());
			}
		}
	};

	class Printer
	{
	public:
		virtual std::string Print(const std::string&, void *) const = 0;
	};

	class IntPrinter : public Printer
	{
	public:
		std::string Print(const std::string& name, void * data) const override
		{
			auto value = static_cast<int*>(data);
			return std::to_string(*value);
		}
	};

	class DoublePrinter : public Printer
	{
	public:
		std::string Print(const std::string& name, void * data) const override
		{
			auto value = static_cast<double*>(data);
			return std::to_string(*value);
		}
	};

	class StringPrinter : public Printer
	{
	public:
		std::string Print(const std::string& name, void * data) const override
		{
			auto value = static_cast<std::string*>(data);
			std::stringstream ss;
			ss << "<Type = 'Curve', ";
			ss << "ObjName = '" << name << "', ";
			ss << "Ref='string.0'>";
			ss << *value;
			ss << "</Type>";
			ss << std::endl;
			return ss.str();
		}
	};

	class CurvePrinter : public Printer
	{
	public:
		std::string Print(const std::string& name, void * data) const override
		{

			auto value = *(reinterpret_cast<Curve::Sptr*>(data));
			std::stringstream ss;
			std::string refName;
			bool exist = false;
			if (value != nullptr)
			{
				refName = CurveAddressAndName(reinterpret_cast<std::uintptr_t>(&*value), exist);
			}
			else
			{ 
				refName = "Curve.0";
			}

			ss << "<Type = 'Curve', ";
			ss << "ObjName = '" << name <<"', ";				

			if (exist)
			{			
				ss << "Ref= '" << refName << "'/>";
			}
			else
			{
				ss << "Ref= '" << refName << "'>";
				ss << std::endl;
				if (value == nullptr)
				{
					ss << "NULL";
				}
				else
				{
					// m_name 
					ss << SerializerFactory::getSerializer("string")->Print("m_name", &(value->m_name));
					auto base = value->m_baseCurve;
					ss << SerializerFactory::getSerializer("Curve")->Print("m_baseCurve", &(base));
					auto anti = value->m_antiBaseCurve;
					ss << SerializerFactory::getSerializer("Curve")->Print("m_antiBaseCurve", &(anti));
				}

				ss << "</Type>";
				ss << std::endl;
			}
			ss.flush();
			return ss.str();
		}
	};





	class Meta
	{
	public:
		std::string m_filedName;
		std::string m_typeName;
		bool m_isSharedPointer;
		bool m_isRawPointer;
	};




}