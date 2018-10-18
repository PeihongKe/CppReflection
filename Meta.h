#pragma once

#include <cstddef>

class MetaData
{
public:
	MetaData(char* n, std::size_t s) : m_name(n), m_size(s) {}

	const char* name() const { return m_name; }
	std::size_t size() const { return m_size; }
	

private:
	const char* m_name;
	std::size_t m_size;

};

class MetaManager
{
public:
	static void resigsterMeta(const Meta)
};

template<typename T>
struct GetTypeName1
{
	std::string operator() ()
	{
		return "struct typename";
	}
};

template<>
struct GetTypeName1<int>
{
	std::string operator() ()
	{
		return "int";
	}
};


template<>
struct GetTypeName1<double>
{
	std::string operator() ()
	{
		return "double";
	}
};

template<typename T>
struct GetTypeName1<T*>
{
	std::string operator() ()
	{
		GetTypeName1<T> subType;
		return "pointer to " + subType();
	}
};

template<typename T>
struct GetTypeName1<std::vector<T>>
{
	std::string operator() ()
	{
		GetTypeName1<T> subType;
		return "vector to " + subType();
	}
};
 

template<typename T>
struct GetTypeName1<std::set<T>>
{
	std::string operator() ()
	{
		GetTypeName1<T> subType;
		return "set to " + subType();
	}
};


template<typename T1, typename T2>
struct GetTypeName1<std::map<T1, T2> >
{
	std::string operator() ()
	{
		GetTypeName1<T1> subType1;
		GetTypeName1<T2> subType2;
		return "map from " + subType1() + " to " + subType2();
	}
};

template<typename T>
T* NullCast(void)
{
	return reinterpret_cast<T *>(NULL);
}

int main1()
{
	double a = 1.1;
	int b = 2;
	std::vector<int> c;

	GetTypeName1<int*> pointerTypePrinter;
	GetTypeName1<std::vector<int>> vectorTypePrinter;
	GetTypeName1<std::vector<std::vector<int>>> vectorvectorTypePrinter;
	GetTypeName1<std::set<std::vector<int>>> setVectorTypePrinter;
	GetTypeName1<std::vector<std::set<int>>> vectorSetTypePrinter;

	GetTypeName1<std::map<int, int>> mapPrinter;
	GetTypeName1<std::map<int, std::vector<int>>> mapVectorPrinter;
	GetTypeName1<std::map<int, int*>> mapPointerPrinter;

	std::map<int, int> aInstance;

	std::cout << GetTypeName1<decltype(aInstance)>()();

}
