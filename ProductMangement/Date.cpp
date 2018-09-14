// Final Project Milestone 1
//
// Version 1.0
// Date: July 10, 2018
// Author: Callum Dodge
// Description
// Date.cpp + Date.h
//		- To see if the date of a product is valid. If not, an error code is given to the system 
//		  putting the object into a Safe Empty State.
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////
#include "Date.h"

namespace AMA {

	// number of days in month mon_ and year year_
	//
	int Date::mdays(int mon, int year)const {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int month = mon >= 1 && mon <= 12 ? mon : 13;
		month--;
		return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}

	//Setting the ErrorCode from the inputed date entered by the user.
	void Date::errCode(int errorCode) {
		EC = errorCode;
	}

	//Constructors
	Date::Date() {
		//Safe Empty State
		year = 0;
		month = 0;
		day = 0;

		errCode(NO_ERROR);
	}

	Date::Date(int n_year, int n_month, int n_day) {

		//Compare to see if the year, month and day is correct and vaild. If it is,
		//NO_ERROR is given as the ErrorCode. An ErrorCode is given if the date is not valid.
		if (n_year >= min_year && n_year <= max_year) {
			year = n_year;
			errCode(NO_ERROR);

			if (n_month > 0 && n_month < 13) {
				month = n_month;
				errCode(NO_ERROR);

				int max_day = mdays(month, year);

				if (n_day > 0 && n_day < max_day) {
					day = n_day;
					errCode(NO_ERROR);
				}
				else {
					SES();
					errCode(DAY_ERROR);
				}
			}
			else {
				SES();
				errCode(MON_ERROR);
			}
		}
		else {
			SES();
			errCode(YEAR_ERROR);
		}
	}

	//Compare if the current date is the same as another date. 
	bool Date::operator==(const Date& rhs) const {
		bool result = true;
		
		if (year == rhs.year && month == rhs.month && day == rhs.day) {
			result = true;
		}
		else {
			result = false;
		}

		return result;
	}

	//Compare if the current date is the not same as another date. 
	bool Date::operator!=(const Date& rhs) const {
		bool result = true;

		if (!(operator==(rhs))) {
			result = true;
		}
		else {
			result = false;
		}
		
		return result;
	}

	//Compare if the current date is less then another date. 
	bool Date::operator<(const Date& rhs) const {
		bool result = true;
		
		if (year <= rhs.year && month <= rhs.month && day <= rhs.day) {
			result = true;
		}
		else {
			result = false;
		}

		return result;
	}

	//Compare if the current date is greater then another date. 
	bool Date::operator>(const Date& rhs) const {
		bool result = true;
		
		if (!(operator<(rhs))) {
			result = true;
		}
		else {
			result = false;
		}

		return result;
	}

	//Compare if the current date is less then or equals another date. 
	bool Date::operator<=(const Date& rhs) const {
		bool result = true;
		
		if (year <= rhs.year && month <= rhs.month && day <= rhs.day) {
			result = true;
		}
		else {
			result = false;
		}

		return result;
	}

	//Compare if the current date is greater then or equals another date. 
	bool Date::operator>=(const Date& rhs) const {
		bool result = true;
		
		if (year >= rhs.year && month>= rhs.month && day >= rhs.day) {
			result = true;
		}
		else {
			result = false;
		}

		return result;
	}

	int Date::errCode() const {
		//Return the ErrorCode Stored.
		return EC;
	}

	bool Date::bad() const {
		bool result = true;
		
		//Compare to see if the ErrorCode Stored is anything but NO_ERROR. If this is true,
		//The date is invalid. 
		if (errCode() != 0) {
			result = true;
		}
		else {
			result = false;
		}

		return result;
	}

	//Read the input from the user and compare to see if the date is valid. If the date is valid,
	//Store the value into the Data Member. If not, set all Data Members to a Safe Empty State 
	//And apply the appropriate error.
	std::istream & Date::read(std::istream & istr)
	{
		char S_D;

		istr.clear();

		istr >> year >> S_D >> month >> S_D >> day;

		if (istr.fail() == true) {
			errCode(CIN_FAILED);
			SES();
		}
		else if (min_year > year || max_year < year) {
			errCode(YEAR_ERROR);
			SES();
		}
		else if (month <= 0 || month >= 13 ) {
			errCode(MON_ERROR);
			SES();
		}
		else if (day < 0 || day > mdays(month, year)) {
			errCode(DAY_ERROR);
			SES();
		}
		istr.clear();

		return istr;
		
	}

	//Write the Current Date to the screen in correct format.
	std::ostream & Date::write(std::ostream& ostr) const {
		
		ostr << year << "/";

		if (month < 10) {
			ostr << "0" << month << "/";
		}
		else {
			ostr << month << "/";
		}
		
		if (day < 10) {
			ostr << "0" << day;
		}
		else {
			ostr << day;
		}

		return ostr;
	}

	//Overload the istream operator >> and return the inputed value from the read function.
	std::istream& operator>>(std::istream& istr, Date& rhs) {
		return rhs.read(istr);
	}

	//Overload the ostream operator << and return the display value from the write function.
	std::ostream& operator<<(std::ostream& ostr, const Date& rhs) {
		return rhs.write(ostr);
	}

	//Safe Empty State
	void Date::SES() {
		year = 0;
		month = 0;
		day = 0;
	}
	
}
