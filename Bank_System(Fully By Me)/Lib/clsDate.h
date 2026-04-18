#pragma once
#pragma warning(disable : 4996)

#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include <iomanip>

#include "clsString.h";



class clsDate
{
private:

	short _Day = 1;
	short _Month = 1;
	short _Year = 1900;

public:

	clsDate()
	{
		time_t t = time(0);
		tm* now = localtime(&t);

		_Day = now->tm_mday;
		_Month = now->tm_mon + 1;
		_Year = now->tm_year + 1900;
	}

	clsDate(std::string Date)
	{
		std::vector <std::string> vDate = clsString::Split(Date, "/");

		_Day = std::stoi(vDate.at(0));
		_Month = std::stoi(vDate.at(1));
		_Year = std::stoi(vDate.at(2));
	}

	clsDate(short Day, short Month, short Year)
	{
		_Day = Day;
		_Month = Month;
		_Year = Year;
	}

	clsDate(short DayOrder, short Year)
	{
		clsDate Date = GetDateFromDayOrderInYear(DayOrder, Year);

		_Day = Date.Day;
		_Month = Date.Month;
		_Year = Date.Year;
	}

	void SetDay(short Day)
	{
		_Day = Day;
	}

	short GetDay()
	{
		return _Day;
	}

	_declspec(property(get = GetDay, put = SetDay)) short Day;

	void SetMonth(short Month)
	{
		_Month = Month;
	}

	short GetMonth()
	{
		return _Month;
	}

	_declspec(property(get = GetMonth, put = SetMonth)) short Month;

	void SetYear(short Year)
	{
		_Year = Year;
	}

	short GetYear()
	{
		return _Year;
	}

	_declspec(property(get = GetYear, put = SetYear)) short Year;

	void Print()
	{
		std::cout << _Day << "/" << _Month << "/" << _Year << std::endl;
	}

	static clsDate GetSystemDate()
	{
		time_t t = time(0);
		tm* now = localtime(&t);
		short Day, Month, Year;

		Day = now->tm_mday;
		Month = now->tm_mon + 1;
		Year = now->tm_year + 1900;

		return clsDate(Day, Month, Year);
	}

	static std::string GetSystemDateString()
	{
		return DateToString(GetSystemDate());
	}

	static std::string GetSystemDateTimeString()
	{
		time_t t = time(0);
		tm* now = localtime(&t);
		std::string Date = DateToString(clsDate());
		short Hour, Minute, Second;

		Hour = now->tm_hour;
		Minute = now->tm_min;
		Second = now->tm_sec;

		return Date + " - " + std::to_string(Hour) + ":" + std::to_string(Minute) + ":" + std::to_string(Second);
	}

	static bool IsValideDate(clsDate Date)
	{
		if (Date.Day < 1 || Date.Day > 31)
			return false;

		if (Date.Month < 1 || Date.Month > 12)
			return false;

		if (Date.Month == 2)
		{
			if (isLeapYear(Date.Year))
			{
				if (Date.Day > 29)
					return false;
			}
			else
			{
				if (Date.Day > 28)
					return false;
			}
		}

		short DaysInMonth = NumberOfDaysInMonth(Date.Month, Date.Year);

		if (Date.Day > DaysInMonth)
			return false;

		return true;
	}

	bool IsValideDate()
	{
		return IsValideDate(*this);
	}

	static std::string DateToString( clsDate Date)
	{
		return std::to_string(Date.Day) + "/" + std::to_string(Date.Month) + "/" + std::to_string(Date.Year);
	}

	std::string DateToString()
	{
		return DateToString(*this);
	}

	static bool isLeapYear(short Year)
	{
		return ((Year % 4 == 0 && Year % 100 != 0) || Year % 400 == 0);
	}

	bool isLeapYear()
	{
		return isLeapYear(_Year);
	}

	static short NumberOfDaysInMonth(short Month, short Year)
	{
		if (Month == 0)
			return 0;

		short NumberOfDaysInMonths[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

		return (Month == 2) ? (isLeapYear(Year) ? 29 : 28) : NumberOfDaysInMonths[Month - 1];

	}

	short NumberOfDaysInMonth()
	{
		return NumberOfDaysInMonth(_Month, _Year);
	}

	static clsDate GetDateFromDayOrderInYear(short DayOrderInYear, short Year)
	{
		clsDate Date;
		short RemainingDays = DayOrderInYear;
		short MonthDays = 0;

		Date.Year = Year;
		Date.Month = 1;

		while (true)
		{
			MonthDays = NumberOfDaysInMonth(Date.Month, Year);

			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				Date.Month++;
			}
			else
			{
				Date.Day = RemainingDays;
				break;
			}
		}
		return Date;
	}

	void GetDateFromDayOrderInYear(short DayOrderInYear)
	{
		*this = GetDateFromDayOrderInYear(DayOrderInYear, _Year);
	}

	static short DayOfWeekOrder(short Day, short Month, short Year)
	{
		short a = 0, y = 0, m = 0;

		a = (14 - Month) / 12;
		y = Year - a;
		m = Month + 12 * a - 2;

		return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
	}

	short DayOfWeekOrder()
	{
		return DayOfWeekOrder(_Day, _Month, _Year);
	}

	static short DayOfWeekOrder(clsDate Date)
	{
		short a = 0, y = 0, m = 0;

		a = (14 - Date.Month) / 12;
		y = Date.Year - a;
		m = Date.Month + 12 * a - 2;

		return (Date.Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
	}

	short DayOfWeedOrder()
	{
		return DayOfWeekOrder(*this);
	}

	static std::string DayShortName(short DayOfWeekOrder)
	{
		std::string arrDayNames[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

		return arrDayNames[DayOfWeekOrder];
	}

	std::string DayShortName()
	{
		return DayShortName(DayOfWeekOrder());
	}

	static std::string MonthShortName(short NumberOfMonth)
	{
		std::string arrMonths[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun",
			"Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

		return arrMonths[NumberOfMonth - 1];
	}

	std::string MonthShortName()
	{
		return MonthShortName(_Month);
	}

	static void PrintMonthCalendar(short Month, short Year)
	{
		short Current = DayOfWeekOrder(1, Month, Year);
		short NumberOfDays = NumberOfDaysInMonth(Month, Year);

		printf("\n  _______________%s_______________\n\n", MonthShortName(Month).c_str());
		printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

		int i;

		for (i = 0; i < Current; i++)
			printf("     ");

		for (int j = 1; j <= NumberOfDays; j++)
		{
			printf("%5d", j);

			if (++i == 7)
			{
				i = 0;
				printf("\n");
			}
		}
		printf("\n  _________________________________\n");
	}

	void PrintMonthCalendar()
	{
		PrintMonthCalendar(_Month, _Year);
	}

	static void PrintYearCalendar(short Year)
	{
		printf("\n\n  ________________________________\n");
		printf("\n           Calendar - %d\n", Year);
		printf("  ________________________________\n\n");

		for (int i = 1; i <= 12; i++)
		{
			PrintMonthCalendar(i, Year);
			std::cout << std::endl;
		}
	}

	void PrintYearCalendar()
	{
		PrintYearCalendar(_Year);
	}

	static short NumberOfDaysFromTheBeginningOfTheYear(short Day, short Month, short Year)
	{
		short TotalDays = 0;

		for (int i = 1; i <= Month - 1; i++)
		{
			TotalDays += NumberOfDaysInMonth(i, Year);
		}

		TotalDays += Day;

		return TotalDays;
	}

	short NumberOfDaysFromTheBeginningOfTheYear()
	{
		return NumberOfDaysFromTheBeginningOfTheYear(_Day, _Month, _Year);
	}

	static clsDate DateAddDays(short Days, clsDate Date)
	{

		short RemainingDays = Days + NumberOfDaysFromTheBeginningOfTheYear(Date.Day, Date.Month, Date.Year);
		short MonthDays = 0;

		Date.Month = 1;

		while (true)
		{
			MonthDays = NumberOfDaysInMonth(Date.Month, Date.Year);

			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				Date.Month++;

				if (Date.Month > 12)
				{
					Date.Month = 1;
					Date.Year++;
				}
			}
			else
			{
				Date.Day = RemainingDays;
				break;
			}
		}
		return Date;
	}

	void DateAddDays(short Days)
	{
		*this = DateAddDays(Days, *this);
	}

	static bool isDate1BeforeDate2(clsDate Date1, clsDate Date2)
	{
		return (Date1.Year < Date2.Year) ? true : ((Date1.Year == Date2.Year) ? ((Date1.Month < Date2.Month) ? true : (Date1.Month == Date2.Month) ? (Date1.Day < Date2.Day) : false) : false);
	}

	bool isDate1BeforeDate2(clsDate Date)
	{
		return isDate1BeforeDate2(*this, Date);
	}

	static bool isDate1AfterDate2(clsDate Date1, clsDate Date2)
	{
		return (!isDate1BeforeDate2(Date1, Date2) && !isDate1EqualDate2(Date1, Date2));
	}

	bool isDate1AfterDate2(clsDate Date)
	{
		return isDate1AfterDate2(*this, Date);
	}

	static bool isDate1EqualDate2(clsDate Date1, clsDate Date2)
	{
		return (Date1.Year == Date2.Year) ? ((Date1.Month == Date2.Month) ? ((Date1.Day == Date2.Day) ? true : false) : false) : false;
	}

	bool isDate1EqualDate2(clsDate Date)
	{
		return isDate1EqualDate2(*this, Date);
	}

	static bool isLastDayInMonth(clsDate Date)
	{
		return (Date.Day == NumberOfDaysInMonth(Date.Month, Date.Year));
	}

	bool isLastDayInMonth()
	{
		return isLastDayInMonth(*this);
	}

	static bool isLastMonthInYear(short Month)
	{
		return (Month == 12);
	}

	bool isLastMonthInYear()
	{
		return isLastMonthInYear(_Month);
	}

	static clsDate AddOneDay(clsDate Date)
	{
		if (isLastDayInMonth(Date))
		{
			if (isLastMonthInYear(Date.Month))
			{
				Date.Day = 1;
				Date.Month = 1;
				Date.Year++;
			}
			else
			{
				Date.Day = 1;
				Date.Month++;
			}
		}
		else
			Date.Day++;

		return Date;
	}

	void AddOneDay()
	{
		*this = AddOneDay(*this);
	}

	static void SwapDates(clsDate& Date1, clsDate& Date2)
	{
		clsDate TempDate;

		TempDate.Day = Date1.Day;
		TempDate.Month = Date1.Month;
		TempDate.Year = Date1.Year;

		Date1.Day = Date2.Day;
		Date1.Month = Date2.Month;
		Date1.Year = Date2.Year;

		Date2.Day = TempDate.Day;
		Date2.Month = TempDate.Month;
		Date2.Year = TempDate.Year;
	}

	void SwapDates(clsDate& Date)
	{
		SwapDates(*this, Date);
	}

	static int GetDifferenceInDays(clsDate Date1, clsDate Date2, bool IncludeEndDay = false)
	{
		int Days = 0;
		short SwapFlagValue = 1;

		if (!isDate1BeforeDate2(Date1, Date2))
		{
			SwapDates(Date1, Date2);
			SwapFlagValue = -1;
		}

		while (isDate1BeforeDate2(Date1, Date2))
		{
			Days++;
			Date1 = AddOneDay(Date1);
		}

		return IncludeEndDay ? ++Days * SwapFlagValue : Days * SwapFlagValue;
	}

	int GetDifferenceInDays(clsDate Date, bool IncludeEndDay = false)
	{
		return GetDifferenceInDays(*this, Date, IncludeEndDay);
	}

	static short CalculateMyAgeInDays(clsDate DateOfBirth)
	{
		clsDate CurrentDate = GetSystemDate();

		return GetDifferenceInDays(DateOfBirth, CurrentDate);
	}

	static clsDate IncreaseDateByXDays(clsDate& Date, short Days)
	{
		for (int i = 1; i <= Days; i++)
		{
			Date = AddOneDay(Date);
		}

		return Date;
	}

	void IncreaseDateByXDays(short Days)
	{
		IncreaseDateByXDays(*this, Days);
	}

	static clsDate IncreaseDateByOneWeek(clsDate& Date)
	{
		for (int i = 1; i <= 7; i++)
		{
			Date = AddOneDay(Date);
		}

		return Date;
	}

	void IncreaseDateByOneWeek()
	{
		IncreaseDateByOneWeek(*this);
	}

	static clsDate IncreaseDateByXWeeks(clsDate& Date, short Weeks)
	{
		for (int i = 1; i <= Weeks; i++)
		{
			Date = IncreaseDateByOneWeek(Date);
		}

		return Date;
	}

	void IncreaseDateByXWeeks(short Weeks)
	{
		IncreaseDateByXWeeks(*this, Weeks);
	}

	static clsDate IncreaseDateByOneMonth(clsDate& Date)
	{
		if (Date.Month == 12)
		{
			Date.Month = 1;
			Date.Year++;
		}
		else
			Date.Month++;

		short NumberOfDaysInCurrentMonth = NumberOfDaysInMonth(Date.Month, Date.Year);

		if (Date.Day > NumberOfDaysInCurrentMonth)
			Date.Day = NumberOfDaysInCurrentMonth;

		return Date;
	}

	void IncreaseDateByOneMonth()
	{
		IncreaseDateByOneMonth(*this);
	}

	static clsDate IncreaseDateByXMonths(clsDate& Date, short Months)
	{
		for (int i = 1; i <= Months; i++)
		{
			Date = IncreaseDateByOneMonth(Date);
		}

		return Date;
	}

	void IncreaseDateByXMonths(short Months)
	{
		IncreaseDateByXMonths(*this, Months);
	}

	// From here.
	static clsDate IncreaseDateByOneYear(clsDate& Date)
	{
		Date.Year++;
		return Date;
	}

	void IncreaseDateByOneYear()
	{
		IncreaseDateByOneYear(*this);
	}

	static clsDate IncreaseDateByXYears(clsDate& Date, short Years)
	{
		for (int i = 1; i <= Years; i++)
		{
			Date = IncreaseDateByOneYear(Date);
		}

		return Date;
	}

	void IncreaseDateByXYears(short Years)
	{
		IncreaseDateByXYears(*this, Years);
	}

	static clsDate IncreaseDateByXYearsFaster(clsDate& Date, short Years)
	{
		Date.Year += Years;
		return Date;
	}

	void IncreaseDateByXYearsFaster(short Years)
	{
		IncreaseDateByXYearsFaster(*this, Years);
	}

	static clsDate IncreaseDateByOneDecade(clsDate& Date)
	{
		Date.Year += 10;
		return Date;
	}

	void IncreaseDateByOneDecade()
	{
		IncreaseDateByOneDecade(*this);
	}

	static clsDate IncreaseDateByXDecades(clsDate& Date, short Decades)
	{
		for (int i = 1; i <= Decades * 10; i++)
		{
			Date = IncreaseDateByOneYear(Date);
		}

		return Date;
	}

	void IncreaseDateByXDecades(short Decades)
	{
		IncreaseDateByXDecades(*this, Decades);
	}

	static clsDate IncreaseDateByXDecadesFaster(clsDate& Date, short Decades)
	{
		Date.Year += 10 * Decades;
		return Date;
	}

	void IncreaseDateByXDecadesFaster(short Decades)
	{
		IncreaseDateByXDecadesFaster(*this, Decades);
	}

	static clsDate IncreaseDateByOneCentury(clsDate& Date)
	{
		Date.Year += 100;
		return Date;
	}

	void IncreaseDateByOneCentury()
	{
		IncreaseDateByOneCentury(*this);
	}

	static clsDate IncreaseDateByOneMillennium(clsDate& Date)
	{
		Date.Year += 1000;
		return Date;
	}

	void IncreaseDateByOneMillennium()
	{
		IncreaseDateByOneMillennium(*this);
	}

	static clsDate DecreaseDateByOneDay(clsDate& Date)
	{
		if (Date.Day == 1)
		{
			if (Date.Month == 1)
			{
				Date.Day = 31;
				Date.Month = 12;
				Date.Year--;
			}
			else
			{
				Date.Month--;
				Date.Day = NumberOfDaysInMonth(Date.Month, Date.Year);
			}
		}
		else
			Date.Day--;

		return Date;
	}

	void DecreaseDateByOneDay()
	{
		DecreaseDateByOneDay(*this);
	}

	static clsDate DecreaseDateByXDays(short Days, clsDate& Date)
	{
		for (int i = 1; i <= Days; i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}

		return Date;
	}

	void DecreaseDateByXDays(short Days)
	{
		DecreaseDateByXDays(Days, *this);
	}

	static clsDate DecreaseDateByOneWeek(clsDate& Date)
	{
		for (int i = 1; i <= 7; i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}

		return Date;
	}

	void DecreaseDateByOneWeek()
	{
		DecreaseDateByOneWeek(*this);
	}

	static clsDate DecreaseDateByXWeeks(short Weeks, clsDate& Date)
	{
		for (int i = 1; i <= Weeks; i++)
		{
			Date = DecreaseDateByOneWeek(Date);
		}

		return Date;
	}

	void DecreaseDateByXWeeks(short Weeks)
	{
		DecreaseDateByXWeeks(Weeks, *this);
	}

	static clsDate DecreaseDateByOneMonth(clsDate& Date)
	{
		if (Date.Month == 1)
		{
			Date.Month = 12;
			Date.Year--;
		}
		else
			Date.Month--;

		short NumberOfDaysInCurrentMonth = NumberOfDaysInMonth(Date.Month, Date.Year);

		if (Date.Day > NumberOfDaysInCurrentMonth)
			Date.Day = NumberOfDaysInCurrentMonth;

		return Date;
	}

	void DecreaseDateByOneMonth()
	{
		DecreaseDateByOneMonth(*this);
	}

	static clsDate DecreaseDateByXMonths(short Months, clsDate& Date)
	{
		for (int i = 1; i <= Months; i++)
		{
			Date = DecreaseDateByOneMonth(Date);
		}

		return Date;
	}

	void DecreaseDateByXMonths(short Months)
	{
		DecreaseDateByXMonths(Months, *this);
	}

	static clsDate DecreaseDateByOneYear(clsDate& Date)
	{
		Date.Year--;
		return Date;
	}

	void DecreaseDateByOneYear()
	{
		DecreaseDateByOneYear(*this);
	}

	static clsDate DecreaseDateByXYears(short Years, clsDate& Date)
	{
		for (int i = 1; i <= Years; i++)
		{
			Date = DecreaseDateByOneYear(Date);
		}

		return Date;
	}

	void DecreaseDateByXYears(short Years)
	{
		DecreaseDateByXYears(Years, *this);
	}

	static clsDate DecreaseDateByXYearsFaster(short Years, clsDate& Date)
	{
		Date.Year -= Years;
		return Date;
	}

	void DecreaseDateByXYearsFaster(short Years)
	{
		DecreaseDateByXYearsFaster(Years, *this);
	}

	static clsDate DecreaseDateByOneDecade(clsDate& Date)
	{
		Date.Year -= 10;
		return Date;
	}

	void DecreaseDateByOneDecade()
	{
		DecreaseDateByOneDecade(*this);
	}

	static clsDate DecreaseDateByXDecades(short Decades, clsDate& Date)
	{
		for (int i = 1; i <= Decades * 10; i++)
		{
			Date = DecreaseDateByOneYear(Date);
		}

		return Date;
	}

	void DecreaseDateByXDecades(short Decades)
	{
		DecreaseDateByXDecades(Decades, *this);
	}

	static clsDate DecreaseDateByXDecadesFaster(short Decades, clsDate& Date)
	{
		Date.Year -= Decades * 10;
		return Date;
	}

	void DecreaseDateByXDecadesFaster(short Decades)
	{
		DecreaseDateByXDecadesFaster(Decades, *this);
	}

	static clsDate DecreaseDateByOneCentury(clsDate& Date)
	{
		Date.Year -= 100;
		return Date;
	}

	void DecreaseDateByOneCentury()
	{
		DecreaseDateByOneCentury(*this);
	}

	static clsDate DecreaseDateByOneMillennium(clsDate& Date)
	{
		Date.Year -= 1000;
		return Date;
	}

	void DecreaseDateByOneMillennium()
	{
		DecreaseDateByOneMillennium(*this);
	}

	static bool isEndOfWeek(clsDate Date)
	{
		return DayOfWeekOrder(Date.Day, Date.Month, Date.Year) == 6;
	}

	bool isEndOfWeek()
	{
		return isEndOfWeek(*this);
	}

	static bool isWeekEnd(clsDate Date)
	{
		short DayIndex = DayOfWeekOrder(Date);

		return (DayIndex == 6 || DayIndex == 5);
	}

	bool isWeekEnd()
	{
		return isWeekEnd(*this);
	}

	static bool isBusinessDay(clsDate Date)
	{
		return !isWeekEnd(Date);
	}

	bool isBusinessDay()
	{
		return isBusinessDay(*this);
	}

	static short DaysUntilEndOfWeek(clsDate Date)	{
		return 6 - DayOfWeekOrder(Date);
	}

	short DaysUntilEndOfWeek()
	{
		return DaysUntilEndOfWeek(*this);
	}

	static short DaysUntilEndOfMonth(clsDate Date)
	{
		clsDate EndOfMonthDate;

		EndOfMonthDate.Day = NumberOfDaysInMonth(Date.Month, Date.Year);
		EndOfMonthDate.Month = Date.Month;
		EndOfMonthDate.Year = Date.Year;

		return GetDifferenceInDays(Date, EndOfMonthDate, true);
	}

	short DaysUntilEndOfMonth()
	{
		return DaysUntilEndOfMonth(*this);
	}

	static short DaysUntilEndOfYear(clsDate Date)
	{
		clsDate EndOfYearDate;

		EndOfYearDate.Day = 31;
		EndOfYearDate.Month = 12;
		EndOfYearDate.Year = Date.Year;

		return GetDifferenceInDays(Date, EndOfYearDate, true);
	}

	short DaysUntilEndOfYear()
	{
		return DaysUntilEndOfYear(*this);
	}

	static short CalculateBusinessDays(clsDate DateFrom, clsDate DateTo)
	{
		short DaysCount = 0;

		while (isDate1BeforeDate2(DateFrom, DateTo))
		{
			if (isBusinessDay(DateFrom))
				DaysCount++;

			DateFrom = AddOneDay(DateFrom);
		}

		return DaysCount;
	}

	 static short CalculateVacationDays(clsDate DateFrom, clsDate DateTo)
	{
		 return CalculateBusinessDays(DateFrom, DateTo);
	}

	 static clsDate CalculateVacationReturnDate(clsDate FromDate, short VacationDays)
	 {
		 short WeekEndCounter = 0;

		 while (isWeekEnd(FromDate))
			 FromDate = AddOneDay(FromDate);

		 for (int i = 1; i <= VacationDays + WeekEndCounter; i++)
		 {
			 if (isWeekEnd(FromDate))
				 WeekEndCounter;

			 FromDate = AddOneDay(FromDate);
		 }

		 while (isWeekEnd(FromDate))
			 FromDate = AddOneDay(FromDate);

		 return FromDate;
	 }

	 enum enDateCompare { Before = -1, Equal = 0, After = 1 };

	 static enDateCompare CompareDates(clsDate Date1, clsDate Date2)
	 {
		 if (isDate1BeforeDate2(Date1, Date2))
			 return enDateCompare::Before;

		 if (isDate1EqualDate2(Date1, Date2))
			 return enDateCompare::Equal;

		 return enDateCompare::After;
	 }

	 enDateCompare CompareDates(clsDate Date1)
	 {
		 return CompareDates(*this, Date1);
	 }

};

