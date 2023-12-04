#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../Date/CDate.h"
#include <sstream>

SCENARIO("Test class CDate")
{
	WHEN("Test valid initialize class CDate")
	{
		WHEN("Test intialize")
		{
			CDate date{ 10, Month::APRIL, 2019 };
			REQUIRE(date.IsValid());
			REQUIRE(date.GetDay() == 10);
			REQUIRE(date.GetMonth() == Month::APRIL);
			REQUIRE(date.GetWeekDay() == WeekDay::SUNDAY);
			REQUIRE(date.GetYear() == 2019);
		}

		WHEN("Test initialize overload")
		{
			CDate date{ 10, Month::APRIL, 10000 };
			REQUIRE(!date.IsValid());
		}
	}

	WHEN("Test invalid day initialize class CDate")
	{
		CDate date{ 32, Month::APRIL, 2019 };
		REQUIRE(!date.IsValid());
		REQUIRE(date.GetDay() == 2);
		REQUIRE(date.GetMonth() == Month::MAY);
		REQUIRE(date.GetWeekDay() == WeekDay::MONDAY);
		REQUIRE(date.GetYear() == 2019);
	}

	WHEN("Date creation test with one argument")
	{
		WHEN("Date creation test with one argument")
		{
			unsigned timestamp = 2;
			CDate date(timestamp);
			REQUIRE(date.GetDay() == 3);
			REQUIRE(date.GetMonth() == Month::JANUARY);
			REQUIRE(date.GetYear() == 1970);
			REQUIRE(date.GetWeekDay() == WeekDay::WEDNESDAY);
		}

		WHEN("Date creation test with one argument overload")
		{
			unsigned timestamp = 100000000000000;
			CDate date(timestamp);
			REQUIRE(!date.IsValid());
		}
	}

	WHEN("Test operator ++")
	{
		CDate date(13, Month::MAY, 2023);
		REQUIRE(date.GetDay() == 13);
		REQUIRE(date.GetMonth() == Month::MAY);
		REQUIRE(date.GetYear() == 2023);
		++date;
		REQUIRE(date.GetDay() == 14);
		REQUIRE(date.GetMonth() == Month::MAY);
		REQUIRE(date.GetYear() == 2023);
	}

	WHEN("Test operator ++")
	{
		CDate date(13, Month::MAY, 2023);
		REQUIRE(date.GetDay() == 13);
		REQUIRE(date.GetMonth() == Month::MAY);
		REQUIRE(date.GetYear() == 2023);
		CDate newDate = ++date;
		REQUIRE(newDate.GetDay() == 14);
		REQUIRE(newDate.GetMonth() == Month::MAY);
		REQUIRE(newDate.GetYear() == 2023);
	}

	WHEN("Test operator --")
	{
		CDate date(13, Month::MAY, 2023);
		REQUIRE(date.GetDay() == 13);
		REQUIRE(date.GetMonth() == Month::MAY);
		REQUIRE(date.GetYear() == 2023);
		--date;
		REQUIRE(date.GetDay() == 12);
		REQUIRE(date.GetMonth() == Month::MAY);
		REQUIRE(date.GetYear() == 2023);
	}

	WHEN("Test operator --")
	{
		CDate date(13, Month::MAY, 2023);
		REQUIRE(date.GetDay() == 13);
		REQUIRE(date.GetMonth() == Month::MAY);
		REQUIRE(date.GetYear() == 2023);
		CDate newDate = --date;
		REQUIRE(newDate.GetDay() == 12);
		REQUIRE(newDate.GetMonth() == Month::MAY);
		REQUIRE(newDate.GetYear() == 2023);
	}

	WHEN("Test operator +=")
	{
		CDate date(13, Month::MAY, 2023);
		REQUIRE(date.GetDay() == 13);
		REQUIRE(date.GetMonth() == Month::MAY);
		REQUIRE(date.GetYear() == 2023);
		date += 30;
		REQUIRE(date.GetDay() == 12);
		REQUIRE(date.GetMonth() == Month::JUNE);
		REQUIRE(date.GetYear() == 2023);
	}

	WHEN("Test operator +=")
	{
		CDate date(13, Month::MAY, 2023);
		REQUIRE(date.GetDay() == 13);
		REQUIRE(date.GetMonth() == Month::MAY);
		REQUIRE(date.GetYear() == 2023);
		CDate newDate = date += 30;
		REQUIRE(newDate.GetDay() == 12);
		REQUIRE(newDate.GetMonth() == Month::JUNE);
		REQUIRE(newDate.GetYear() == 2023);
	}

	WHEN("Test operator -=")
	{
		CDate date(13, Month::MAY, 2023);
		REQUIRE(date.GetDay() == 13);
		REQUIRE(date.GetMonth() == Month::MAY);
		REQUIRE(date.GetYear() == 2023);
		date -= 30;
		REQUIRE(date.GetDay() == 13);
		REQUIRE(date.GetMonth() == Month::APRIL);
		REQUIRE(date.GetYear() == 2023);
	}

	WHEN("Test operator -=")
	{
		CDate date(13, Month::MAY, 2023);
		REQUIRE(date.GetDay() == 13);
		REQUIRE(date.GetMonth() == Month::MAY);
		REQUIRE(date.GetYear() == 2023);
		CDate newDate = date -= 30;
		REQUIRE(newDate.GetDay() == 13);
		REQUIRE(newDate.GetMonth() == Month::APRIL);
		REQUIRE(newDate.GetYear() == 2023);
	}

	WHEN("Test operator ==")
	{
		CDate d1(12), d2(13);
		REQUIRE(!(d1 == d2));
		d2--;
		REQUIRE(d1 == d2);
	}

	WHEN("Test operator !=")
	{
		CDate d1(12), d2(13);
		REQUIRE(d1 != d2);
		d2--;
		REQUIRE(!(d1 != d2));
	}

	WHEN("Test operator > and <")
	{
		CDate d1(12), d2(13);
		REQUIRE(d1 < d2);
		d2 -= 10;
		REQUIRE(d1 > d2);
	}

	WHEN("Test operator >= and <=")
	{
		CDate d1(12), d2(13);
		REQUIRE(d1 <= d2);
		d2 -= 1;
		REQUIRE(d1 >= d2);
	}

	WHEN("Test operator << ")
	{
		CDate date(12, Month::DECEMBER, 2012);
		std::stringstream out;
		out << date;
		REQUIRE(out.str() == "12.12.2012");
	}

	WHEN("Test operator >> ")
	{
		CDate date;
		std::stringstream in("12.12.2012");
		in >> date;
		REQUIRE(date.GetDay() == 12);
		REQUIRE(date.GetMonth() == Month::DECEMBER);
		REQUIRE(date.GetYear() == 2012);
		REQUIRE(date.GetWeekDay() == WeekDay::SUNDAY);
	}

	WHEN("Test get date components")
	{
		CDate date(2012);
		unsigned day, year;
		Month month;
		date.GetDateComponents(day, year, month);
		REQUIRE(day == 5);
		REQUIRE(year == 1975);
		REQUIRE(month == Month::JULY);
		WHEN("Test is valid date components")
		{
			REQUIRE(date.IsValidDateComponents(day, month, year));
		}
	}

	WHEN("Test is valid date components overload")
	{
		WHEN("Test overload m_daySince1970")
		{
			CDate date(32, Month::APRIL, 10000);
			unsigned day, year;
			Month month;
			date.GetDateComponents(day, year, month);
			REQUIRE(!date.IsValidDateComponents(day, month, year));
		}

		WHEN("Test day overload")
		{
			CDate date(32, Month::APRIL, 2000);
			unsigned day, year;
			Month month;
			date.GetDateComponents(day, year, month);
			REQUIRE(date.IsValidDateComponents(day, month, year));
		}
	}
}