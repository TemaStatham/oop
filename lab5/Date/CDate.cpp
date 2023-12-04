#include "CDate.h"
#include <iomanip>

unsigned MIN_YEAR = 1970;
unsigned MAX_YEAR = 9999;
unsigned NUMBER_OF_DAYS_IN_LEAP_YEAR = 366;
unsigned NUMBER_OF_DAYS_IN_YEAR = 365;

CDate::CDate(unsigned day, Month month, unsigned year)
{
	if (!IsValidDateComponents(day, month, year))
	{
		isValidInitialization = false;
	}
	unsigned totalDays = 0;
	for (unsigned y = MIN_YEAR; y < year; ++y)
	{
		totalDays += (IsLeapYear(y) ? NUMBER_OF_DAYS_IN_LEAP_YEAR : NUMBER_OF_DAYS_IN_YEAR);
	}
	// выбрать исключение седлать метод исвалуе фолс
	for (int m = 1; m < static_cast<int>(month); ++m)
	{
		totalDays += DaysInMonth(static_cast<Month>(m), year);
	}

	totalDays += day - 1;

	m_daysSince1970 = totalDays;
}

CDate::CDate(unsigned timestamp)
	: m_daysSince1970(timestamp)
{
}

unsigned CDate::GetDay() const
{
	unsigned days, year;
	Month month;
	GetDateComponents(days, year, month);
	return days + 1;
}

Month CDate::GetMonth() const
{
	unsigned days, year;
	Month month;
	GetDateComponents(days, year, month);
	return month;
}

unsigned CDate::GetYear() const
{
	unsigned days, year;
	Month month;
	GetDateComponents(days, year, month);
	return year;
}

WeekDay CDate::GetWeekDay() const
{
	return static_cast<WeekDay>((m_daysSince1970 + 1) % 7);
}

bool CDate::IsValid() const
{
	unsigned days, year;
	Month month;
	GetDateComponents(days, year, month);
	unsigned day = days + 1;

	return IsValidDateComponents(day, month, year) && isValidInitialization;
}

CDate& CDate::operator++()
{
	m_daysSince1970++;
	return *this;
}

CDate CDate::operator++(int)
{
	CDate temp = *this;
	m_daysSince1970++;
	return temp;
}

CDate& CDate::operator--()
{
	m_daysSince1970--;
	return *this;
}

CDate CDate::operator--(int)
{
	CDate temp = *this;
	m_daysSince1970--;
	return temp;
}

CDate CDate::operator+(unsigned days) const
{
	CDate result = *this;
	result.m_daysSince1970 += days;
	return result;
}

CDate CDate::operator-(unsigned days) const
{
	CDate result = *this;
	result.m_daysSince1970 -= days;
	return result;
}

int CDate::operator-(const CDate& other) const
{
	return m_daysSince1970 - other.m_daysSince1970;
}

CDate& CDate::operator+=(unsigned days)
{
	m_daysSince1970 += days;
	return *this;
}

CDate& CDate::operator-=(unsigned days)
{
	m_daysSince1970 -= days;
	return *this;
}

bool CDate::operator==(const CDate& other) const
{
	return m_daysSince1970 == other.m_daysSince1970;
}

bool CDate::operator!=(const CDate& other) const
{
	return m_daysSince1970 != other.m_daysSince1970;
}

bool CDate::operator<(const CDate& other) const
{
	return m_daysSince1970 < other.m_daysSince1970;
}

bool CDate::operator>(const CDate& other) const
{
	return m_daysSince1970 > other.m_daysSince1970;
}

bool CDate::operator<=(const CDate& other) const
{
	return m_daysSince1970 <= other.m_daysSince1970;
}

bool CDate::operator>=(const CDate& other) const
{
	return m_daysSince1970 >= other.m_daysSince1970;
}

unsigned CDate::DaysInMonth(Month month, unsigned year) const
{
	if (month == Month::APRIL || month == Month::JUNE || month == Month::SEPTEMBER || month == Month::NOVEMBER)
	{
		return 30;
	}
	if (month == Month::FEBRUARY)
	{
		if (IsLeapYear(year))
		{
			return 29;
		}
		return 28;
	}
	return 31;
}

bool CDate::IsLeapYear(unsigned year) const
{
	return (year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0));
}

unsigned CDate::GetYearFromDays(unsigned& days) const
{
	unsigned year = MIN_YEAR;
	while (days >= NUMBER_OF_DAYS_IN_YEAR)
	{
		if (IsLeapYear(year))
		{
			if (days < NUMBER_OF_DAYS_IN_LEAP_YEAR)
			{
				break;
			}
			days -= NUMBER_OF_DAYS_IN_LEAP_YEAR;
			year++;
			continue;
		}
		days -= NUMBER_OF_DAYS_IN_YEAR;
		year++;
	}
	return year;
}

void CDate::GetDateComponents(unsigned& days, unsigned& year, Month& month) const
{
	days = m_daysSince1970;
	year = GetYearFromDays(days);
	month = GetMonthFromDays(days, year);
}

bool CDate::IsValidDateComponents(unsigned day, Month month, unsigned year) const
{
	if (year < MIN_YEAR || year > MAX_YEAR)
	{
		return false;
	}

	if (month < Month::JANUARY || month > Month::DECEMBER)
	{
		return false;
	}

	if (day < 1 || day > DaysInMonth(month, year))
	{
		return false;
	}

	return true;
}

Month CDate::GetMonthFromDays(unsigned& days, unsigned& year) const
{
	Month month = Month::JANUARY;
	while (days >= DaysInMonth(month, year))
	{
		days -= DaysInMonth(month, year);
		month = static_cast<Month>(static_cast<unsigned>(month) + 1);
	}
	return month;
}

std::istream& operator>>(std::istream& is, CDate& date)
{
	unsigned day, monthNumber, year;
	char dot1, dot2;

	if (!(is >> day >> dot1 >> monthNumber >> dot2 >> year) || !is || dot1 != '.' || dot2 != '.')
	{
		is.setstate(std::ios::failbit | is.rdstate());
		return is;
	}

	Month month = static_cast<Month>(monthNumber);

	if (date.IsValidDateComponents(day, month, year))
	{
		date = CDate{ day, month, year };
	}

	return is;
}

std::ostream& operator<<(std::ostream& os, const CDate& date)
{
	if (!date.IsValid())
	{
		os << "Invalid data" << std::endl;
		return os;
	}

	unsigned days, year;
	Month month;
	date.GetDateComponents(days, year, month);
	unsigned day = days + 1;

	if (!date.IsValidDateComponents(day, month, year))
	{
		os << "Invalid date components" << std::endl;
	}

	os << std::setw(2) << std::setfill('0') << day << '.'
	   << std::setw(2) << std::setfill('0') << static_cast<unsigned>(month) << '.'
	   << std::setw(4) << std::setfill('0') << year;

	return os;
}
