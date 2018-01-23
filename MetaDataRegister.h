#pragma once

#include <map>
#include <string>
#include <vector>
#include <string>
#include <sstream>

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)



struct Field
{
	std::string field;
	std::string type;
};

class MetaRegister
{
public:
	typedef void(*func)();


	MetaRegister()
	{
	}

	void addLoader(func f)
	{
		loaders.push_back(f);
	}

	void addSuperClass(const std::string& sup, const std::string& sub)
	{
		superClassBySubClass.insert( { sup, sub } );
	}

	void addFields(const std::string& className, const std::string& fieldName, const std::string& fieldType)
	{
		auto field = Field();
		field.field = fieldName;
		field.type = fieldType;

		if (fieldsByClass.find(className) == fieldsByClass.end() )
		{
			fieldsByClass[className];
		}

		fieldsByClass[className].push_back(field);
	}

	void loadMetaData()
	{
		for(auto f : loaders)
		{ 
			f();
		}
	}

	template<typename type>
	std::string serialize(const type& obj)
	{
		std::stringstream ss;
		auto typeName = typeid(type).name();
		auto fields = fieldsByClass[typeName];
		//ss << obj.m_version;
		for (auto f : fields)
		{
			auto fieldName = f.field;
			auto typeName = f.type;
			ss << std::to_string(obj.m_type);
		}

		return ss.str();
	}


	template<typename type>
	type deserialize(const std::string& serializedObj, type a = type())
	{
		type obj;
		obj.m_version = std::stoi(serializedObj);
		return obj;

		
	}
	

private:

	std::vector<func> loaders;
	std::vector<std::string> classNames;
	std::map<std::string, std::vector<Field>>  fieldsByClass;
	std::map<std::string, std::string > superClassBySubClass;
	

} ;

MetaRegister& getMeta()
{
	static MetaRegister meta;
	return meta;
}

class MetaDataManager {
public:
	static MetaRegister& singleton() {
		static MetaRegister instance;
		return instance;
	}
};

 
class ISerializable
{
public:
	ISerializable(int version = 1): m_version(version){}

	friend class MetaRegister;
	virtual ~ISerializable() {}
private:
	int m_version;
	
};

#define RegisterClass(className) MetaDataManager::singleton().addLoader((className##::load))									   
#define RegisterSuperClass (superClass, subClass) MetaDataManager::singleton().addSuperClass( typeid(superClass).name() ), typeid(subClass).name() )							
#define RegisterVariable(clazz, field, type) MetaDataManager::singleton().addFields( typeid(clazz).name(), TOSTRING(field), typeid(type).name() )

//#define RegisterSuperClass(className) MetaDataManager->addLoader(&className##::load)