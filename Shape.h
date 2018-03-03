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
		RegisterVector(Shape, m_edges, int);
	}
	virtual ~Shape() {};
private:
	int m_type;
	double m_area;
	std::vector<int> m_edges;

};
 