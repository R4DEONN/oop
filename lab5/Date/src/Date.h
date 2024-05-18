#pragma once

#include <ctime>

// Месяц
enum class Month
{
	JANUARY = 1, FEBRUARY, MARCH, APRIL,
	MAY, JUNE, JULY, AUGUST, SEPTEMBER,
	OCTOBER, NOVEMBER, DECEMBER
};

// День недели
enum class WeekDay
{
	SUNDAY = 0, MONDAY, TUESDAY, WEDNESDAY,
	THURSDAY, FRIDAY, SATURDAY
};

class Date
{
public:
	// инициализируем дату заданными днем, месяцем и годом.
	// примечание: год >= 1970
	Date(unsigned day, Month month, unsigned year);

	// инициализируем дату количеством дней, прошедших после 1 января 1970 года
	// например, 2 = 3 января 1970, 32 = 2 февраля 1970 года и т.д.
	explicit Date(unsigned timestamp);

	// Конструктор по умолчанию. Создаёт дату, равную 1 января 1970.
	Date();

	// возвращает день месяца (от 1 до 31)
	[[nodiscard]] unsigned GetDay() const;

	// возвращает месяц
	[[nodiscard]] Month GetMonth() const;

	// возвращает год
	[[nodiscard]] unsigned GetYear() const;

	// возвращает день недели
	[[nodiscard]] WeekDay GetWeekDay() const;

	[[nodiscard]] unsigned GetTimestamp() const;

	Date& operator++();
	Date operator++(int);
	Date& operator--();
	Date operator--(int);
	unsigned operator-(const Date& date) const;
	Date operator-(unsigned days) const;
	Date& operator+=(unsigned days);
	Date& operator-=(unsigned days);
	auto operator<=>(const Date& other) const = default;

private:
	unsigned m_timestamp = 0;

	constexpr static const unsigned MIN_YEAR = 1970;
	constexpr static const unsigned MAX_YEAR = 9999;
	constexpr static const unsigned DAYS_OFFSET_FOR_START_DATE = 4;
	constexpr static const unsigned MIN_MONTH = 1;
	constexpr static const unsigned MAX_MONTH = 12;
	constexpr static const unsigned MIN_DAY = 1;
	constexpr static const unsigned MAX_DAY = 2932897;
	constexpr static const unsigned DAYS_OF_WEEK = 7;

	[[nodiscard]] bool IsLeapYear(unsigned year) const;
	[[nodiscard]] unsigned GetDaysInMonth(Month month, unsigned year) const;
	[[nodiscard]] unsigned DateToTimestamp(unsigned day, Month month, unsigned year) const;
	void ValidateDatetime(unsigned day, Month month, unsigned year) const;
	void ValidateTimestamp() const;
};

inline Date operator+(const Date& date, unsigned days)
{
	return Date(date.GetTimestamp() + days - 1);
}

inline Date operator+(unsigned days, const Date& date)
{
	return Date(date.GetTimestamp() + days - 1);
}