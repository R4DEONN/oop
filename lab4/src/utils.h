#ifndef _UTILS_H
#define _UTILS_H

#include <string>
#include <sstream>
#include <iomanip>

template <typename T>
std::string toStringWithPrecision(const T value, const int n = 2)
{
	std::ostringstream out;
	out.precision(n);
	out << std::fixed << value;
	return std::move(out).str();
}

template <typename T>
std::string toStringHex(const T value)
{
	std::ostringstream out;
	out << std::setw(6) << std::setfill('0') << std::hex << value;
	return std::move(out).str();
}

#endif //_UTILS_H
