#ifndef DATE_H_
#define DATE_H_

#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

const int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const int daysInMonthLeap[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const string months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
const string monthsShort[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
const string weekdays[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

class Date
{
	int month, day, year;
public:
	Date(int month, int day, int year) : month(month), day(day), year(year) {}
	
	Date(const Date&) = default;
	
	Date() { month = 1; day = 1; year = 1900; }
	
	static bool isLeapYear(int year) { return (year % 4 == 0 && year % 100 != 0 || year % 400 == 0); }
	
	static int getDaysInMonth(int month, int year) { if(isLeapYear(year)) return daysInMonthLeap[month - 1]; else return daysInMonth[month - 1]; }
	
	static Date getRandomDate(int year) { int month = rand() % 12 + 1; int day = rand() % getDaysInMonth(month, year) + 1; return Date(month, day, year); }
	
	Date getAnniversary(int n) { if(isLeapYear(year) && month == 2 && day == 29 && !isLeapYear(year + n)) return Date(3, 1, year + n); return Date(month, day, year + n); }
	
	int getMonth() { return month; }
	
	int getDay() { return day; }
	
	int getYear() { return year; }
	
	void setMonth(int m) { month = m; if(day > getDaysInMonth(month, year)) day = getDaysInMonth(month, year); }
	
	void setDay(int d) { day = d; }
	
	void setYear(int y) { year = y; }
	
	int getDayOfWeek()
	{
		int m = month, d = day, y = year;
		static int t[] = { 0, 3, 2, 5, 0, 3,
                       5, 1, 4, 6, 2, 4 }; 
   		 y -= m < 3;
   		 return ( y + y / 4 - y / 100 + 
             y / 400+ t[m - 1] + d) % 7; 
	}
	
	Date operator ++()
	{
		day++;
		if(day > getDaysInMonth(month, year))
		{
			month++;
			day = 1;
			if(month > 12)
			{
				month = 1;
				year++;
			}
		}
		return *this;
	}
	
	Date operator --()
	{
		day--;
		if(day < 1)
		{
			month--;
			if(month < 1)
			{
				month = 12;
				year--;
			}
			day = getDaysInMonth(month, year);
		}
		return *this;
	}
	
	Date operator ++(int)
	{
		Date copy = *this;
		day++;
		if(day > getDaysInMonth(month, year))
		{
			month++;
			day = 1;
			if(month > 12)
			{
				month = 1;
				year++;
			}
		}
		return copy;
	}
	
	Date operator --(int)
	{
		Date copy = *this;
		day--;
		if(day < 1)
		{
			month--;
			if(month < 1)
			{
				month = 12;
				year--;
			}
			day = getDaysInMonth(month, year);
		}
		return copy;
	}
	
	
	Date operator +(int days)
	{
		Date result = *this;
		for(int i = 0; i < days; i++)
			++result;
		return result;
	}
	
	Date operator -(int days)
	{
		Date result = *this;
		for(int i = 0; i < days; i++)
			--result;
		return result;
	}
	
	Date& operator +=(int days)
	{
		for(int i = 0; i < days; i++)
			++*this;
		return *this;
	}
	
	bool operator ==(Date d) { return month == d.month && day == d.day && year == d.year; }
	
	bool operator !=(Date d) { return !(*this == d); }
	
	bool operator <(Date d)
	{
		if(year != d.year)
			return year < d.year;
		else if(month != d.month)
			return month < d.month;
		else
			return day < d.day;
	}
	
	bool operator >(Date d) { return !(*this < d || *this == d); }
	
	bool operator <=(Date d) { return !(*this > d); }
	
	bool operator >=(Date d) { return !(*this < d); }
	
	int operator -(Date d)
	{
		int days = 0;
		while(d != *this)
		{
			if(d < *this)
			{
				days++;
				d++;
			}
			else
			{
				days--;
				d--;
			}
		}
		return days;
	}
	
	static Date fromMonthAndWeekday(int num, int weekday, int month, int year)
	{
		Date result(month, 1, year);
		while(result.getDayOfWeek() != weekday)
			result++;
		for(int i = 1; i < num; i++)
			result += 7;
		return result;
	}
	
	string toString() { return to_string(month) + "/" + to_string(day) + "/" + to_string(year); }
	
	string toShortString() { return to_string(month) + "/" + to_string(day) + "/" + (year % 100 < 10 ? "0" : "") + to_string(year % 100); }
	
	string toAbbrString(bool useBritishFormat = true)
	{
		if (useBritishFormat)
			return to_string(day) + " " + monthsShort[month - 1] + " " + to_string(year);
		else
		return monthsShort[month - 1] + " " + to_string(day) + ", " + to_string(year);
	}
	
	string toLongString(bool useBritishFormat = true)
	{
		if (useBritishFormat)
			return to_string(day) + " " + months[month - 1] + " " + to_string(year);
		else
			return months[month - 1] + " " + to_string(day) + ", " + to_string(year);
	}
	
	string toFullString(bool useBritishFormat = true)
	{
	//	return to_string(year) + "Äê" + to_string(month) + "ÔÂ" + to_string(day) + "ÈÕ" + weekdays[getDayOfWeek()];
		if(useBritishFormat)
			return weekdays[getDayOfWeek()] + " " + to_string(day) + " " + months[month - 1] + " " + to_string(year);
		else
			return weekdays[getDayOfWeek()] + ", " +  months[month - 1] + " " + to_string(day) + ", " + to_string(year);
	}
};

#endif // DATE_H_
