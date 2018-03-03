#pragma once

#include <map>
#include <string>
#include <vector>
#include <string>
#include <sstream>

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)


class MetaField
{
public:

	MetaField(const std::string& fieldName, std::size_t ofst, const std::string& typeName ): m_field_name(fieldName), m_offset(ofst), m_typename(typeName) {}

	std::string name() const { return m_field_name; }	
	std::size_t offset() const { return m_offset;  }
	std::string typeName() const { return m_typename; }

private:
	std::string m_field_name;	
	std::size_t m_offset;
	std::string m_typename;

};

class VectorMetaField : public MetaField
{
public:
	VectorMetaField(const std::string& fieldName, std::size_t ofst, const std::string& elementTypeName) : MetaField(fieldName, ofst, "vector"), m_elem_type(elementTypeName)
	{}

	std::string elemType() const { return m_elem_type; }
	//std::size_t size() const { return m_vector_size; }

private:
	std::string m_elem_type;
	//std::size_t m_vector_size;
};

template<typename T>
class MetaData
{
public:

	void AddField(const MetaField& field)
	{
		fields.push_back(field.name());
		offsetByName[field.name()] = field.offset();
		typeNameByFiledName[field.name()] = field.typeName();
	}

	static MetaData& Get()
	{
		static MetaData meta ;
		return meta;
	}

	size_t Offset(const std::string& fieldName) const
	{
		// return offsetByName[ fieldName ];
		return offsetByName.at( fieldName );
		//return 1;
	}

	std::string TypeName(const std::string& fieldName) const
	{
		return typeNameByFiledName.at(fieldName);
	
	}

	std::vector<std::string> Fields() const
	{
		return fields;
	}

private:
	std::vector<std::string> fields;
	std::map<std::string, size_t> offsetByName; 
	std::map<std::string, std::string> typeNameByFiledName;

};


class MetaManager
{
public:
	typedef void(*metaLoaderFunc)();

	void loadMetaData()
	{
		for (auto f : loaders)
		{
			f();
		}
	}

	void addLoader(metaLoaderFunc f)
	{
		loaders.push_back(f);
	}

	static MetaManager& Get()
	{
		static MetaManager manager;
		return manager;
	}

private:
	std::vector<metaLoaderFunc> loaders;


};
//
//class MetaRegister
//{
//public:
//	typedef void(*func)();
//
//
//	MetaRegister()
//	{
//	}
//
//	void addLoader(func f)
//	{
//		loaders.push_back(f);
//	}
//
//	void addSuperClass(const std::string& sup, const std::string& sub)
//	{
//		superClassBySubClass.insert( { sup, sub } );
//	}
//
//	void addFields(const std::string& fieldName, std::size_t fieldOffset)
//	{
//		auto meta = MetaField(fieldName, fieldOffset);
// 
//
//		//if (fieldsByClass.find(className) == fieldsByClass.end() )
//		//{
//		//	fieldsByClass[className];
//		//}
//
//		//fieldsByClass[className].push_back(field);
//	}
//
//	void loadMetaData()
//	{
//		for(auto f : loaders)
//		{ 
//			f();
//		}
//	}
//
//	template<typename type>
//	std::string serialize(const type& obj)
//	{
//		std::stringstream ss;
//		auto typeName = typeid(type).name();
//		auto fields = fieldsByClass[typeName];
//		//ss << obj.m_version;
//		for (auto f : fields)
//		{
//			auto fieldName = f.field;
//			auto typeName = f.type;
//			ss << std::to_string(obj.m_type);
//		}
//
//		return ss.str();
//	}
//
//
//	template<typename type>
//	type deserialize(const std::string& serializedObj, type a = type())
//	{
//		type obj;
//		obj.m_version = std::stoi(serializedObj);
//		return obj;
//
//		
//	}
//	
//
//private:
//
//	std::vector<func> loaders;
//	std::vector<std::string> classNames;
//	std::map<std::string, std::vector<MetaField>>  fieldsByClass;
//	std::map<std::string, std::string > superClassBySubClass;
//	
//
//} ;



//class MetaDataManager {
//public:
//	static MetaRegister& Get() {
//		static MetaRegister instance;
//		return instance;
//	}
//};
//
//template<typename T>
//class TypeClass
//{
//public:
//	typedef T Type;
//	T* get() // return a pointer to be turned into type
//	{
//		static TypeClass c;
//		return &c;
//	}
//};
//
//void type()
//{
//	TypeClass<int>()
//}
//
//



template<typename T>
T* NullCast(void)
{
	return reinterpret_cast<T *>(NULL);
}

#define RegisterClass(className) MetaManager::Get().addLoader((className##::load))									   
//#define RegisterSuperClass (superClass, subClass) MetaDataManager::Get().addSuperClass( typeid(superClass).name() ), typeid(subClass).name() )							
#define RegisterVariable(clazz, field, type) MetaData<clazz>::Get().AddField( MetaField( TOSTRING(field), (unsigned)(&(NullCast<clazz>()->##field)), TOSTRING(type) ))
#define RegisterVector(clazz, field, elemType) MetaData<clazz>::Get().AddField( VectorMetaField( TOSTRING(field), (unsigned)(&(NullCast<clazz>()->##field)), TOSTRING(elemType) ))

//#define RegisterSuperClass(className) MetaDataManager->addLoader(&className##::load)