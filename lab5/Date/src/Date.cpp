#include "stdexcept"
#include "Date.h"

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

unsigned Date::GetDaysInMonth(Month month, unsigned year)
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
{	unsigned year = MIN_YEAR;

	unsigned shift_years = m_timestamp / 365.25;
	year += shift_years;

	unsigned days_remaining = m_timestamp;
	unsigned leap_years = (year - MIN_YEAR) / 4 - (year - MIN_YEAR) / 100 + (year - MIN_YEAR) / 400;

	days_remaining -= shift_years * 365 + leap_years;
	Month month = Month::JANUARY;
	unsigned days = days_remaining;

	unsigned daysInMonth = GetDaysInMonth(month, year);
	while (days > daysInMonth)
	{
		days -= daysInMonth;
		month = static_cast<Month>(static_cast<unsigned>(month) + 1);
		daysInMonth = GetDaysInMonth(month, year);
	}

	return month;
}

bool Date::IsLeapYear(unsigned year)
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

unsigned Date::GetYear() const
{
	unsigned year = MIN_YEAR;

	unsigned shift_years = m_timestamp / 365.25;
	year += shift_years;

//	unsigned days_remaining = m_timestamp;
//	unsigned leap_years = (year - MIN_YEAR) / 4 - (year - MIN_YEAR) / 100 + (year - MIN_YEAR) / 400;
//
//	days_remaining -= shift_years * 365 + leap_years;
//
//	if (days_remaining > 0)
//	{
//		while (days_remaining > static_cast<unsigned>(IsLeapYear(year) ? 366 : 365))
//		{
//			days_remaining -= IsLeapYear(year) ? 366 : 365;
//			year++;
//		}
//	}

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

void Date::ValidateDatetime(unsigned int day, Month month, unsigned int year)
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
	return m_timestamp - 1;
}

unsigned Date::operator-(const Date& date) const
{
	return (GetTimestamp()) - (date.GetTimestamp());
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
	return Date(GetTimestamp() - days);
}

Date& Date::operator-=(unsigned days)
{
	m_timestamp -= days;
	return *this;
}

