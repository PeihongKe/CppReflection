// CppSerialization.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MetaDataRegister.h"
#include "Shape.h"

int main()
{
	RegisterClass(Shape);
	MetaDataManager::singleton().loadMetaData();
	auto& serializer = MetaDataManager::singleton();

	Shape s;
	auto res = serializer.serialize(s);
	auto obj = serializer.deserialize(res, Shape());

    return 0;
}

