// CppSerialization.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MetaDataRegister.h"
#include "Shape.h"
#include <vector>
#include <iostream>
#include "Printer.h"
#include <sstream>
#include "Curves.h"
#include <memory>
#include "CurveSerializer.h"

#include <typeinfo>

#define PTR_ADD( PTR, OFFSET ) \
  ((void *)(((char *)(PTR)) + (OFFSET)))


//template<typename T >
//T create()
//{
//	T a;
//	return a;
//}
//
//
//class SampleBase;
//
//static SampleBase *NullCast(void)
//{
//	return reinterpret_cast<SampleBase *>(NULL);
//}



//class SampleBase
//{
//public:
//	SampleBase( SampleBase& rhs)
//	{
//		//
//		//std::cout << &(reinterpret_cast<SampleBase *>(0)->a) << std::endl;
//		//std::cout << &(reinterpret_cast<SampleBase *>(0)->b) << std::endl;
//		//std::cout << &(reinterpret_cast<SampleBase *>(0)->c) << std::endl;
//		////std::cout << &(reinterpret_cast<SampleBase *>(0)->d) << std::endl;
//		//std::cout << offsetof(class SampleBase, a) << std::endl;
//		//std::cout << offsetof(class SampleBase, b) << std::endl;
//		//std::cout << offsetof(class SampleBase, c) << std::endl;
//		//std::cout << offsetof(class SampleBase, d) << std::endl;
//		auto a_s = (unsigned)(&(NullCast()->a));
//		auto b_s = (unsigned)(&(NullCast()->b));
//		auto c_s = (unsigned)(&(NullCast()->c));
//		auto d_s = (unsigned)(&(NullCast()->d));
//		auto e_s = (unsigned)(&(NullCast()->e));
//
//		std::cout << a_s <<std::endl;
//		std::cout << b_s << std::endl;
//		std::cout << c_s << std::endl;
//		std::cout << d_s << std::endl;
//		std::cout << e_s << std::endl;
//
//		//auto a_r = *(reinterpret_cast<int*>(&rhs + a_s));
//		auto a_r = *(reinterpret_cast<int*>(PTR_ADD(&rhs, a_s)));
//		//auto b_r = *(reinterpret_cast<double*>(&rhs + b_s));
//		auto b_r = *(reinterpret_cast<double*>(PTR_ADD(&rhs, b_s)));
//		//auto c_r = (reinterpret_cast<std::vector<double> >(&rhs + c_s));
//		//auto d_r = *(reinterpret_cast<char*>(&rhs + d_s));
//		auto d_r = *(reinterpret_cast<char*>(PTR_ADD(&rhs, d_s)));
//		//auto e_r = *(reinterpret_cast<float*>(&rhs + e_s));
//		auto e_r = *(reinterpret_cast<float*>(PTR_ADD(&rhs, e_s)));
//
//
//		std::cout << "a_v\t" << rhs.a << std::endl;
//		std::cout << "b_v\t" << rhs.b << std::endl;
//		std::cout << "d_v\t" << rhs.d << std::endl;
//		std::cout << "e_v\t" << rhs.e << std::endl;
//
//		std::cout << "a_r\t" << a_r << std::endl;
//		std::cout << "b_r\t" << b_r << std::endl;
//		std::cout << "d_r\t" << d_r << std::endl;
//		std::cout << "e_r\t" << e_r << std::endl;
//		
//		//*rhs
//		//std::cout << &(SampleBase::a) << std::endl;
//	}
//
//	SampleBase(int a1 = 1, double b1 = 2., std::vector<double> c1 = std::vector<double>(), char d1 = 'a', float e1 = 4.) : a(a1), b(b1), c(c1), d(d1), e(e1) {}
//private:	
//	int a;
//	double b;
//	std::vector<double> c;
//	char d;
//	float e;
//
//};
//




template<typename T>
std::string serialize(T obj)
{
	auto meta = MetaData<T>::Get();
	std::stringstream ss;
	ss << "{\r\n"; 
	for (const std::string& fieldName : meta.Fields() )
	{		
		ss << "{ "; 
		auto offset = meta.Offset(fieldName);
		auto typeName = meta.TypeName(fieldName);
		void* data = PTR_ADD(&obj, offset);
		auto printer = getPrinter(typeName);
		auto res = printer->Print(data);
		ss << fieldName;
		ss << " : ";
		ss << res;

		ss << " , ";

		ss << "typeName";
		ss << " : ";
		ss << typeName;


		ss << " },\r\n";
							
		 
	}
	ss << "\r\n}";
	return ss.str();

}

//template<>
//std::string serialize<int>(int a )
//{
//	return std::to_string(a);
//}
//
//
//template<>
//std::string serialize<double>(double a)
//{
//	return std::to_string(a);
//}
//
//
//template<>
//std::string serialize<std::string>(std::string a)
//{
//	return a;
//}








int main()
{
	BH::Curve::Sptr usdDisc = std::make_shared<BH::Curve>("USD.D");
	BH::Curve::Sptr jpyProj = std::make_shared<BH::Curve>("JPY.STD");
	BH::Curve::Sptr usdProj = std::make_shared<BH::Curve>("USD.STD");
	BH::Curve::Sptr jpyXccy = std::make_shared<BH::Curve>("JPY.XCcy", usdDisc, usdDisc);

 
	/*std::cout << typeid(&jpyXccy).name() <<std::endl;
	std::cout << typeid(&*jpyXccy).name() << std::endl;
	std::cout << typeid(static_cast<void*>(&*jpyXccy)).name() << std::endl;*/
	//std::string aString = "abc";
	//std::cout << BH::SerializerFactory::getSerializer("string")->Print("aString", &aString);
	//std::cout<<BH::SerializerFactory::getSerializer("Curve")->Print("usdDisc", &usdDisc);
	std::cout << BH::SerializerFactory::getSerializer("Curve")->Print("jpyXccy", &jpyXccy);


	//// 1. register 
	//RegisterClass(Shape);

	//// 2. load
	//MetaManager::Get().loadMetaData();


	//auto& metaManger = MetaManager::Get();

	//auto& shapeMeta = MetaData<Shape>::Get();

	//Shape a(2, 5.1);
	//auto res = serialize(a);
	//auto b = 1;
	////SampleBase aa;
	//
	////SampleBase cc(aa);


	//std::cout << &((unsigned)(&(reinterpret_cast<SampleBase *>(NULL)->a))) << std::endl;
	//std::cout << &(SampleBase::b) << std::endl;
	//std::cout << &(SampleBase::c) << std::endl;
	//RegisterClass(Shape);
	//MetaDataManager::singleton().loadMetaData();
	//auto& serializer = MetaDataManager::singleton();

	//Shape s;
	//auto res = serializer.serialize(s);
	//auto obj = serializer.deserialize(res, Shape());

    return 0;
}

