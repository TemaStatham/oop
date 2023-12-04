#include <istream>

#pragma once

enum class Month
{
	JANUARY = 1,
	FEBRUARY,
	MARCH,
	APRIL,
	MAY,
	JUNE,
	JULY,
	AUGUST,
	SEPTEMBER,
	OCTOBER,
	NOVEMBER,
	DECEMBER

};

enum class WeekDay
{
	SUNDAY = 0,
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY
};

class CDate
{
public:
	CDate(unsigned day, Month month, unsigned year);
	CDate(unsigned timestamp = 0);

	unsigned GetDay() const;
	Month GetMonth() const;
	unsigned GetYear() const;
	WeekDay GetWeekDay() const;
	bool IsValid() const;

	CDate& operator++();
	CDate operator++(int);
	CDate& operator--();
	CDate operator--(int);
	CDate operator+(unsigned days) const;
	CDate operator-(unsigned days) const;
	int operator-(const CDate& other) const;
	CDate& operator+=(unsigned days);
	CDate& operator-=(unsigned days);
	bool operator==(const CDate& other) const;
	bool operator!=(const CDate& other) const;
	bool operator<(const CDate& other) const;
	bool operator>(const CDate& other) const;
	bool operator<=(const CDate& other) const;
	bool operator>=(const CDate& other) const;

	void GetDateComponents(unsigned& days, unsigned& year, Month& month) const;

	// static
	bool IsValidDateComponents(unsigned day, Month month, unsigned year) const;

private:
	unsigned DaysInMonth(Month month, unsigned year) const;
	bool IsLeapYear(unsigned year) const;
	unsigned GetYearFromDays(unsigned& days) const;
	Month GetMonthFromDays(unsigned& days, unsigned& year) const;

	unsigned m_daysSince1970 = 0;
	bool isValidInitialization = true;
};

std::istream& operator>>(std::istream& is, CDate& date);
std::ostream& operator<<(std::ostream& os, const CDate& date);