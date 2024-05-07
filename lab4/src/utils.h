#ifndef _UTILS_H
#define _UTILS_H

#include <string>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <Point.h>

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

[[nodiscard]] inline double GetDistance(Point firstPoint, Point secondPoint)
{
	return std::hypot(firstPoint.x - secondPoint.x, firstPoint.y - secondPoint.y);
}

#endif //_UTILS_H
