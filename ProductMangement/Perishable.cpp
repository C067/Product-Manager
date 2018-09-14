//Callum Dodge
//100229178
//July 30, 2018


#include <iostream>
#include <fstream>
#include <iomanip>
#include "Perishable.h"
#include "Date.h"

using namespace std;

namespace AMA {
	
	//Zero-Argument Constructor
	//Calling/Passing a Type over to the Product Constructor
	//Sets all data members into a Safe Empty State
	Perishable::Perishable() : Product('P'){}

	//Storing an expiry date to the file
	std::fstream& Perishable::store(std::fstream& file, bool newLine) const {
		
		//Call the Storing Function from the Product
		Product::store(file, false);
		//Append the expiry date to the file sperated by a comma
		file << "," << expiry() << endl;

		//return the file
		return file;

	}

	std::fstream& Perishable::load(std::fstream& file) {

		//Call the loading function from Product
		Product::load(file);

		//read the expiry date from the file
		expDate.read(file);  
		file.ignore();
		return file;
	}

	//Outputs the Perishable Produt to the screen. 
	std::ostream& Perishable::write(std::ostream& os, bool linear) const {
		
		//Calls the write function from Product
		Product::write(os, linear);

		//If there is not an error message stored, append the expriy date
		//to the screen. Followed or not followed by a new line if the
		//information can fit in one line.
		if (error.isClear()) {
			if (linear == true) {
				os << expiry();
			}
			else {
				os << " Expiry date: " << expiry();
			}
		}

		//Return the ostream
		return os;
	}

	//Get the user to input all other information about the Product 
	//and then ask the user to enter a expiry date for the Perishable 
	//Product.
	std::istream& Perishable::read(std::istream& is) {
		Date tempDate;

		//Call the read function from Product
		Product::read(is);

		//Compare to see if there is any error message stored in the 
		//Error object.
		if (error.isClear()) {
			
			//Ask the user to enter the expiry date.
			cout << " Expiry date (YYYY/MM/DD): ";
			is >> tempDate;

			//Check to see if any errors occured from the inputed expiry date
			errorCheck(tempDate, is);
		}
		return is;
	}

	const Date& Perishable::expiry() const {
		return expDate;
	}

	//Compare to see if any errors occured from the inputed expiry date
	std::istream& Perishable::errorCheck(const Date& tempDate, std::istream& is) {

		//If the date entry error is triggered 
		//Set the message and failbit
		if (tempDate.errCode() == CIN_FAILED) {
			error.message("Invalid Date Entry");
			is.setstate(std::ios::failbit);
		}
		//If the year entry error is triggered 
		else if (tempDate.errCode() == YEAR_ERROR) {
			message("Invalid Year in Date Entry");
			is.setstate(std::ios::failbit);
		}
		//If the month entry error is triggered 
		else if (tempDate.errCode() == MON_ERROR) {
			message("Invalid Month in Date Entry");
			is.setstate(std::ios::failbit);

		}
		//If the day entry error is triggered 
		else if (tempDate.errCode() == DAY_ERROR) {
			message("Invalid Day in Date Entry");
			is.setstate(std::ios::failbit);
		}
		//If there isn't any errors, clear the error message and
		//pass the expiry date to the object
		else {
			error.clear();
			expDate = tempDate;
		}

		//Return the istream
		return is;
	}
}
