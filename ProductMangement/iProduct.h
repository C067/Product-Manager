//Callum Dodge
//100229178
//July 22, 2018

#ifndef IPRODUCT_H
#define IPRODUCT_H

#include <iostream>
#include <fstream>

namespace AMA {

	class iProduct {

	public:

		//Compare if a newline should be implemented or not then store the record.
		virtual std::fstream& store(std::fstream& file, bool newLine = true) const = 0; 

		//Load the records contained in a file.
		virtual std::fstream& load(std::fstream& file) = 0;

		//Write the contents of a record of a Product to the ostream.
		virtual std::ostream& write(std::ostream& os, bool linear) const = 0;

		//Read the contents from the istream input and store the Product.
		virtual std::istream& read(std::istream& is) = 0;

		//Returns True if the inputed string is identical to the Sku.
		virtual bool operator==(const char*) const = 0;

		//Calculate the Total Cost
		virtual double total_cost() const = 0;

		//Return the name stored in the product
		virtual const char* name() const = 0;

		//Replace the quantity needed value with the passed value. 
		virtual void quantity(int) = 0;

		//Return the Quantity Needed of a Product
		virtual int qtyNeeded() const = 0;

		//Return the Quantity On Hand of a Product
		virtual int quantity() const = 0;

		//Add the current quantity to updating number
		virtual int operator+=(int) = 0;

		//Return True if the name is greater than the passed object
		virtual bool operator>(const iProduct&) const = 0;
	};

	//Insert the reference object into the ostream
	std::ostream& operator<< (std::ostream&, const iProduct&);

	//Extract the iProduct record for the referenced object from the istream.
	std::istream& operator>> (std::istream&, iProduct&);

	//Add the Total Cost of an object to the referenced double. 
	double operator+=(double&, const iProduct&);

	//Create a Product
	iProduct* CreateProduct();

	//Create a Perishable
	iProduct* CreatePerishable();
}

#endif //IPRODUCT_H