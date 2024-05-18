#include "catch2/catch_test_macros.hpp"
#include "../src/Date.h"
#include "stdexcept"

void AssertDate(Date date, int day, Month month, int year, WeekDay weekDay)
{
	REQUIRE(date.GetDay() == day);
	REQUIRE(date.GetMonth() == month);
	REQUIRE(date.GetYear() == year);
	REQUIRE(date.GetWeekDay() == weekDay);
}
//
TEST_CASE("default constructor")
{
	auto date = Date();
	AssertDate(date, 1, Month::JANUARY, 1970, WeekDay::THURSDAY);
}

TEST_CASE("day constructor 2 january 1970")
{
	auto date = Date(1);
	AssertDate(date, 2, Month::JANUARY, 1970, WeekDay::FRIDAY);
}

TEST_CASE("day constructor 1 february 1970")
{
	auto date = Date(31);
	AssertDate(date, 1, Month::FEBRUARY, 1970, WeekDay::SUNDAY);
}

TEST_CASE("day constructor max")
{
	auto date = Date(2932896);
	AssertDate(date, 31, Month::DECEMBER, 9999, WeekDay::FRIDAY);
}

TEST_CASE("day constructor overflow")
{
	REQUIRE_THROWS_AS(Date(2932897), std::invalid_argument);
}

TEST_CASE("1 january with datetime")
{
	auto date = Date(1, Month::JANUARY, 1970);
	AssertDate(date, 1, Month::JANUARY, 1970, WeekDay::THURSDAY);
}

TEST_CASE("2 january with datetime")
{
	auto date = Date(2, Month::JANUARY, 1970);
	AssertDate(date, 2, Month::JANUARY, 1970, WeekDay::FRIDAY);
}

TEST_CASE("max with datetime")
{
	auto date = Date(31, Month::DECEMBER, 9999);
	AssertDate(date, 31, Month::DECEMBER, 9999, WeekDay::FRIDAY);
}

TEST_CASE("day constructor overflow day datetime")
{
	REQUIRE_THROWS_AS(Date(32, Month::DECEMBER, 9999), std::invalid_argument);
}

TEST_CASE("day constructor overflow year datetime")
{
	REQUIRE_THROWS_AS(Date(25, Month::DECEMBER, 10000), std::invalid_argument);
}

TEST_CASE("day constructor underflow year datetime")
{
	REQUIRE_THROWS_AS(Date(25, Month::DECEMBER, 1969), std::invalid_argument);
}

TEST_CASE("operations")
{
	Date date;
	date++;
	REQUIRE(date.GetDay() == 2);
	++date;
	REQUIRE(date == Date(2));
	date--;
	REQUIRE(date.GetTimestamp() == 2);
	--date;
	REQUIRE(date == Date());

	date += 1;
	REQUIRE(date == Date() + 1);
	REQUIRE(0 == date - date);
	REQUIRE(Date(1) - 1 == Date());
	date -= 1;
	REQUIRE(date == Date());
	REQUIRE(date != Date(1));
	REQUIRE(date < Date(1));
	REQUIRE(date <= Date(1));
	REQUIRE(date <= Date(0));
	REQUIRE(date >= Date(0));
	REQUIRE(date + 1 > Date(0));
}