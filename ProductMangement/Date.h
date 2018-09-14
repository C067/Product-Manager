// Final Project Milestone 1
//
// Version 1.0
// Date July 10,2018
// Author Callum Dodge
// Description
//
//
//
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////
#ifndef AMA_DATE_H
#define AMA_DATE_H

#include <iostream>

namespace AMA {

	const int min_year = 2000;
	const int max_year = 2030;

	//ErrorCodes
	#define NO_ERROR 0
	#define CIN_FAILED 1
	#define YEAR_ERROR 2
	#define MON_ERROR 3
	#define DAY_ERROR 4	

	class Date {
	//Data Members
	private:
		int year;
		int month;
		int day;
		int EC;

		//Private Member Functions
		int mdays(int, int)const;
		void errCode(int errorCode);
		void SES();

	public:
		//Constructors
		Date();
		Date(int, int, int);

		//Operator Functions
		bool operator==(const Date& rhs) const;
		bool operator!=(const Date& rhs) const;
		bool operator<(const Date& rhs) const;
		bool operator>(const Date& rhs) const;
		bool operator<=(const Date& rhs) const;
		bool operator>=(const Date& rhs) const;

		//Public Member Functions
		int errCode() const;
		bool bad() const;

		std::istream& read(std::istream& istr);
		std::ostream& write(std::ostream& ostr) const;
	};

	std::istream& operator>>(std::istream&, Date&);
	std::ostream& operator<<(std::ostream&, const Date&);
  

}
#endif