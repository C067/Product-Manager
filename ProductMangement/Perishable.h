//Callum Dodge
//100229178
//July 30, 2018

#ifndef PERISHABLE_H
#define PERISHABLE_H

#include "Date.h"
#include "Product.h"
#include <iostream>
#include <fstream>

namespace AMA {

	class Perishable : public Product {

	private:
		//Date object holding the expiring date of a Perishable Product
		Date expDate;

		std::istream& errorCheck(const Date&, std::istream &); //Compare to see if there are any errors in the 
								//Date Object. Apply the specific error message if there is.
	public:
		Perishable();

		std::fstream& store(std::fstream& file, bool newline =true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);

		const Date& expiry() const;
		
	};


}



#endif //PERISHABLE_H