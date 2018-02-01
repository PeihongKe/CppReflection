#pragma once
#include <typeinfo>
#include "MetaDataRegister.h"



class Shape
{
public: 

	Shape()
	{

	}

	Shape(int type, double area) : m_type(type), m_area(area)
	{

	}

	friend class MetaRegister;

	static void load()
	{
		RegisterVariable(Shape, m_type, int);		
		RegisterVariable(Shape, m_area, double);
	}
	virtual ~Shape() {};
private:
	int m_type;
	double m_area;

};
 