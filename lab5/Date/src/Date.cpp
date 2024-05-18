#include "stdexcept"
#include "Date.h"
#include "iostream"

Date::Date()
: m_timestamp(MIN_DAY)
{

}

Date::Date(unsigned int timestamp)
{
	m_timestamp = timestamp + 1;
	ValidateTimestamp();
}

Date::Date(unsigned day, Month month, unsigned year)
{
	ValidateDatetime(day, month, year);
	m_timestamp = DateToTimestamp(day, month, year);
}

unsigned Date::GetDay() const
{
	unsigned year = MIN_YEAR;
	Month month = Month::JANUARY;
	unsigned days = m_timestamp;

	while (days > static_cast<unsigned>(IsLeapYear(year) ? 366 : 365))
	{
		days -= IsLeapYear(year) ? 366 : 365;
		year++;
	}

	unsigned daysInMonth = GetDaysInMonth(month, year);
	while (days > daysInMonth)
	{
		days -= daysInMonth;
		month = static_cast<Month>(static_cast<unsigned>(month) + 1);
		daysInMonth = GetDaysInMonth(month, year);
	}

	return days;
}

unsigned Date::GetDaysInMonth(Month month, unsigned year) const
{
	switch (month)
	{
	case Month::APRIL:
	case Month::JUNE:
	case Month::SEPTEMBER:
	case Month::NOVEMBER:
		return 30;
	case Month::FEBRUARY:
		return IsLeapYear(year) ? 29 : 28;
	default:
		return 31;
	}
}

Month Date::GetMonth() const
{
	unsigned year = MIN_YEAR;
	Month month = Month::JANUARY;
	unsigned days = m_timestamp;

	while (days > static_cast<unsigned>(IsLeapYear(year) ? 366 : 365))
	{
		days -= IsLeapYear(year) ? 366 : 365;
		year++;
	}

	unsigned daysInMonth = GetDaysInMonth(month, year);
	while (days > daysInMonth)
	{
		days -= daysInMonth;
		month = static_cast<Month>(static_cast<unsigned>(month) + 1);
		daysInMonth = GetDaysInMonth(month, year);
	}

	return month;
}

bool Date::IsLeapYear(unsigned year) const
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

unsigned Date::GetYear() const
{
	unsigned year = MIN_YEAR;
	unsigned days = m_timestamp;

	while (days > static_cast<unsigned>(IsLeapYear(year) ? 366 : 365))
	{
		days -= IsLeapYear(year) ? 366 : 365;
		year++;
	}

	return year;
}

WeekDay Date::GetWeekDay() const
{
	unsigned day = (m_timestamp - MIN_DAY + DAYS_OFFSET_FOR_START_DATE) % DAYS_OF_WEEK;
	return static_cast<WeekDay>(day);
}

unsigned Date::DateToTimestamp(unsigned int day, Month month, unsigned int year) const
{
	unsigned days = 0;
	for (unsigned y = MIN_YEAR; y < year; ++y)
	{
		days += IsLeapYear(y) ? 366 : 365;
	}
	for (unsigned m = MIN_MONTH; m < static_cast<unsigned>(month); ++m)
	{
		days += GetDaysInMonth(static_cast<Month>(m), year);
	}
	days += day;
	return days;
}

void Date::ValidateDatetime(unsigned int day, Month month, unsigned int year) const
{
	if (year < MIN_YEAR || year > MAX_YEAR)
	{
		throw std::invalid_argument("Invalid year");
	}

	unsigned daysInMonth = GetDaysInMonth(month, year);
	if (day > daysInMonth)
	{
		throw std::invalid_argument("Invalid day");
	}
}

Date& Date::operator++()
{
	m_timestamp++;
	return *this;
}

Date Date::operator++(int)
{
	auto temp = *this;
	m_timestamp++;
	return temp;
}

Date& Date::operator--()
{
	m_timestamp--;
	return *this;
}

Date Date::operator--(int)
{
	auto temp = *this;
	m_timestamp--;
	return temp;
}

unsigned Date::GetTimestamp() const
{
	return m_timestamp;
}

unsigned Date::operator-(const Date& date) const
{
	return (GetTimestamp() - 1) - (date.GetTimestamp() - 1);
}

Date& Date::operator+=(unsigned days)
{
	m_timestamp += days;
	ValidateTimestamp();
	return *this;
}

void Date::ValidateTimestamp() const
{
	if (m_timestamp > MAX_DAY)
	{
		throw std::invalid_argument("Overflow timestamp");
	}
}

Date Date::operator-(unsigned int days) const
{
	return Date(GetTimestamp() - days - 1);
}

Date& Date::operator-=(unsigned days)
{
	m_timestamp -= days;
	return *this;
}

std::ostream& operator<<(std::ostream& out, const Date& date)
{
	out << date.GetDay() << '.' << static_cast<unsigned>(date.GetMonth()) << '.' << date.GetYear();
	return out;
}

std::istream& operator>>(std::istream& in, Date& date)
{
	unsigned year;
	unsigned month;
	unsigned day;
	char dot1;
	char dot2;

	in >> day >> dot1 >> month >> dot2 >> year;

	if (dot1 != '.' || dot2 != '.')
	{
		in.setstate(std::ios::badbit);
	}

	date = Date(day, static_cast<Month>(month), year);
	return in;
}
