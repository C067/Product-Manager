//Callum Dodge
//100229178
//July 21, 2018

#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include "iProduct.h"
#include "ErrorState.h"

namespace AMA {

	#define max_sku_length 7
	#define max_unit_length 10
	#define max_name_length 75
	#define TAX_RATE 0.13

	class Product : public iProduct {
		private:

			//Data Members
			char m_type;
			char m_sku[max_sku_length +1];
			char m_unit[max_unit_length+ 1];
			char m_name[max_name_length+ 1];
			char *address;
			int m_quantity;
			int m_quantity_need;
			double m_cost;
			bool m_tax;

			void SES(); //Assign a Safe Empty State to the current object.

		protected:
			ErrorState error;

			void name(const char*); //Allocate enough memory for the name of the Product.
			
			const char* name() const; //Return the Name of the Product
			const char* sku() const; //Return the Sku of the Product
			const char* unit() const; //Return the Unit of the Product
			bool taxed() const; //Return if the Product needs to be taxed
			double price() const; //Return the Price of the Product
			double cost() const; //Return the total Cost of the Product
			void message(const char*); //Return the ErrorMessage of the Product
			bool isClear() const; //Return is the state of the Product. Returns True or False if the 
								  //Product is in a Safe Empty State

		public:
			//Constructors
			/*Product();
			Product(const char*, const char*, const char *);
 			*/Product(char type = 'N');
			Product(const char* n_sku, const char* n_name, const char* n_unit, int n_qty = 0, bool isTaxed = false, double n_price = 0.00, int n_qtyNeed = 0);
			//Copy Constructor
			Product(const Product&);
			//Copy Assignment Operator
			Product& operator=(const Product&);
			//Destructor
			~Product();

			std::fstream& store(std::fstream&file, bool newline = true) const; //Store a record of a Product to a File
			std::fstream& load(std::fstream& file); //Load a Record of a Product from a File
			std::ostream& write(std::ostream& os, bool linear) const; //Write a record of a Product to the ostream
			std::istream& read(std::istream& is); //Read the Inputed values from the istream

			//Operator Overloads
			bool operator==(const char*) const; 
			bool operator>(const char*) const;
			bool operator>(const iProduct&) const;
			int operator+=(int);

			//Member Functions
			double total_cost() const; //Calculate the total cost of the Product
			void quantity(int); //Reset the current Quantity on Hand with the passed Parameters
			bool isEmpty() const; //Compare to see if the current Product was in a Safe Empty State
			int qtyNeeded() const; //Return the current Quantity Needed from the Product
			int quantity() const; //Return the current Quantity from the Product

	};
	std::ostream& operator<<(std::ostream&, const iProduct&);
	std::istream& operator>>(std::istream&, iProduct&);

	double operator+=(double&, const iProduct&);
}


#endif //PRODUCT_H