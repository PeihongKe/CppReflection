#pragma once
#include <string>
#include <memory>
#include <map>
#include <string>
#include <sstream>

namespace BH
{

	class Curve
	{

	public:
		typedef std::shared_ptr<Curve> Sptr;
		typedef std::shared_ptr<const Curve> ConstSptr;
		typedef Curve T;
		//friend class Serializer<T>;
		friend class CurvePrinter;
		//friend class DeSerializer<T>;

		Curve() {}

		Curve(const std::string& name) : m_name(name)
		{

		}

		Curve(const std::string& name, const Sptr& base, const Sptr& antiBase) : m_name(name), m_baseCurve(base), m_antiBaseCurve(antiBase)
		{

		}


	private:
		std::string m_name;
		Sptr m_baseCurve;
		Sptr m_antiBaseCurve;
	};

}