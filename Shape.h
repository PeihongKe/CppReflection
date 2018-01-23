#pragma once
#include <typeinfo>
#include "MetaDataRegister.h"



class Shape: public ISerializable
{
public: 

	Shape()
	{

	}

	Shape(int type) : m_type(type)
	{

	}

	friend class MetaRegister;

	static void load()
	{
		//MetaDataManager::singleton().addFields(TOSTRING(Shape), TOSTRING(m_type), TOSTRING(int));
		RegisterVariable(Shape, m_type, int);
	}
	//virtual ~Shape() {};
private:
	int m_type;

};

class Circle: public Shape
{
public:
};


