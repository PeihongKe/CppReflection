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