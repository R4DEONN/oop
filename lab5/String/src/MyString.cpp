#include <cstring>
#include <utility>
#include "MyString.h"
#include "algorithm"
#include "iostream"

char MyString::m_nullChar = '\0';

MyString::MyString()
	: m_capacity(0), m_size(0)
{
	m_chars = &m_nullChar;
}

MyString::MyString(size_t size, size_t capacity, char* chars)
	: m_size(size),
	m_capacity(capacity),
	m_chars(chars)
{}

MyString::MyString(const char* pString)
: MyString(std::strlen(pString), std::strlen(pString) * 2 + 1, new char[std::strlen(pString) * 2 + 1])
{
	std::memcpy(m_chars, pString, m_size + 1);
}

MyString::MyString(const char* pString, size_t length)
	: MyString(length, length * 2 + 1, new char[length * 2 + 1])
{
	std::memcpy(m_chars, pString, m_size);
	m_chars[m_size] = '\0';
}

MyString::MyString(const MyString& other)
	: MyString(other.m_size, other.m_capacity, new char[other.m_capacity])
{
	std::memcpy(m_chars, other.m_chars, m_size + 1);
}

MyString::MyString(MyString&& other) noexcept
	: MyString(other.m_size, other.m_capacity, other.m_chars)
{
	other.m_chars = &m_nullChar;
	other.m_capacity = 0;
	other.m_size = 0;
}

MyString::MyString(const std::string& stlString)
	: MyString(stlString.c_str(), stlString.length())
{
}

MyString::~MyString()
{
	if (m_chars != &m_nullChar)
	{
		delete[] m_chars;
	}
}

size_t MyString::GetLength() const noexcept
{
	return m_size;
}

const char* MyString::GetStringData() const noexcept
{
	return m_chars;
}

size_t MyString::GetCapacity() const noexcept
{
	return m_capacity;
}

MyString& MyString::operator=(const MyString& other)
{
	if (this != &other)
	{
		if (m_capacity >= other.m_size)
		{
			m_size = other.m_size;
			std::memcpy(m_chars, other.m_chars, m_size);
			m_chars[m_size] = '\0';
		}
		else
		{
			MyString tmp(other);

			std::swap(m_chars, tmp.m_chars);
			std::swap(m_size, tmp.m_size);
			std::swap(m_capacity, tmp.m_capacity);
		}
	}

	return *this;
}

MyString& MyString::operator=(MyString&& other) noexcept
{
	if (this != &other)
	{
		if (m_chars != &m_nullChar)
		{
			delete[] m_chars;
		}

		m_chars = std::exchange(other.m_chars, &m_nullChar);
		m_capacity = std::exchange(other.m_capacity, 0);
		m_size = std::exchange(other.m_size, 0);
	}

	return *this;
}

bool MyString::operator==(const MyString& other) const
{
	if (m_size != other.m_size)
	{
		return false;
	}

	return std::memcmp(m_chars, other.m_chars, m_size) == 0;
}

MyString MyString::SubString(size_t start, size_t length) const
{
	if (start >= m_size)
	{
		return {};
	}

	size_t subLength = std::min(length, m_size - start);
	return { m_chars + start, subLength };
}

void MyString::Clear()
{
	m_size = 0;
}

MyString MyString::operator+(const MyString& other) const
{
	size_t newSize = m_size + other.m_size;
	size_t newCapacity = newSize * 2 + 1;
	char* newChars = new char[newCapacity];
	std::memcpy(newChars, m_chars, m_size);
	std::memcpy(newChars + m_size, other.m_chars, other.m_size + 1);

	return {newSize, newCapacity, newChars};
}

MyString MyString::operator+(const std::string& other) const
{
	size_t newSize = m_size + other.size();
	size_t newCapacity = newSize * 2 + 1;
	char* newChars = new char[newCapacity];
	std::memcpy(newChars, m_chars, m_size);
	std::memcpy(newChars + m_size, other.c_str(), other.size() + 1);

	return {newSize, newCapacity, newChars};
}

MyString MyString::operator+(const char* other) const
{
	size_t newSize = m_size + std::strlen(other);
	size_t newCapacity = newSize * 2 + 1;
	char* newChars = new char[newCapacity];
	std::memcpy(newChars, m_chars, m_size);
	std::memcpy(newChars + m_size, other, std::strlen(other) + 1);

	return {newSize, newCapacity, newChars};
}

MyString MyString::operator+(const char ch) const
{
	size_t newSize = m_size + 1; //TODO: remove duplicate code
	size_t newCapacity = newSize * 2 + 1;
	char* newChars = new char[newCapacity];
	std::memcpy(newChars, m_chars, m_size);
	newChars[m_size] = ch;
	newChars[m_size + 1] = '\0';

	return { newSize, newCapacity, newChars };
}

MyString& MyString::operator+=(const MyString& other)
{
	if (m_size + other.m_size > m_capacity)
	{
		//TODO: Упростить
		auto newSize = m_size + other.m_size;
		auto newCapacity = newSize * 2 + 1;
		char* newChars = new char[newCapacity];
		std::memcpy(newChars, m_chars, m_size);
		std::memcpy(newChars + m_size, other.m_chars, other.m_size + 1);
		m_size = newSize;
		m_capacity = newCapacity;
		if (m_chars != &m_nullChar)
		{
			delete[] m_chars;
		}
		m_chars = newChars;
	}
	else
	{
		std::memcpy(m_chars + m_size, other.m_chars, other.m_size + 1);
		m_size += other.m_size;
	}
	return *this;
}

bool MyString::operator<(const MyString& other) const
{
	int cmp = std::memcmp(m_chars, other.m_chars, std::min(m_size, other.m_size));
	return cmp < 0 || (cmp == 0 && m_size < other.m_size);
}

bool MyString::operator<=(const MyString& other) const
{
	return !(*this > other);
}

bool MyString::operator>(const MyString& other) const
{
	return other < *this;
}

bool MyString::operator>=(const MyString& other) const
{
	return !(*this < other);
}

const char& MyString::operator[](size_t index) const
{
	if (index >= m_size)
	{
		throw std::out_of_range("Index out of range");
	}

	return m_chars[index];
}

char& MyString::operator[](size_t index)
{
	if (index >= m_size)
	{
		throw std::out_of_range("Index out of range");
	}
	return m_chars[index];
}

std::ostream& operator<<(std::ostream& os, const MyString& str)
{
	os << str.GetStringData();
	return os;
}

std::istream& operator>>(std::istream& is, MyString& str)
{
	std::string input;
	is >> input;
	str = MyString(input);
	return is;
}