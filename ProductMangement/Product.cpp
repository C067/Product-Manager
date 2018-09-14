//Callum Dodge
//100229178
//July 21, 2018

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include "Product.h"
#include "ErrorState.h"


using namespace std;

namespace AMA {

	//Private Function:: This Function sets all data members into a Safe Empty State
	void Product::SES()
	{
		m_sku[0] = '\0';
		m_unit[0] = '\0';
		m_name[0] = '\0';
		m_quantity = 0;
		m_quantity_need = 0;
		m_cost = 0;
		m_tax = false;
	}

	//Purpose is to allocate new memory for the name of the product. 
	void Product::name(const char * n_name) {
		//Check to see if the parameter is not empty or null. 
		if (n_name != nullptr || n_name != '\0') {

			if (address != nullptr) {
				address = nullptr;
			}

			//Allocate new memory of the given name and assign it to variable address.
			address = new char[strlen(n_name) + 1];
			strncpy(address, n_name, strlen(n_name));
			address[strlen(n_name)] = '\0';

			//Pass over the new created memory to the data member m_name.
			//This will be the name of the newy created Product.
			strncpy(m_name, address, strlen(address));
			m_name[strlen(n_name)] = '\0';

		}
		//If the parameter is null or empty assign the address to be null as well.
		else {
			address = nullptr;
		}

	}
	//Returns the name stored in the Product
	const char * Product::name() const {
		return m_name;
	}
	//Returns the Sku stored in the Product
	const char * Product::sku() const {
		return m_sku;
	}
	//Returns the type of Unit given to the Product
	const char * Product::unit() const {
		return m_unit;
	}
	//Returns the current bool value of tax
	bool Product::taxed() const {
		return m_tax;
	}
	//Returns the current price of the Product
	double Product::price() const {
		return m_cost;
	}
	//Returns the total cost of the Product.
	double Product::cost() const {
		double total;
		//If the Product needs to be taxed. Calculate and return the taxed value of 
		//the Product
		if (taxed()) {
			total = price() + (m_cost *TAX_RATE);
		}
		//Else, return the current Price of the Product
		else {
			total = price();
		}

		return total;
	}

	//If an error has occured when implmenting data. Print the error message 
	//stored in the ErrorState Object.
	void Product::message(const char* n_message) {
		error.message(n_message);
	}
	//Compare to see if the message in the ErrorState object has been cleared.
	//Return True or False if it has or not.
	bool Product::isClear() const {
		return error.isClear();
	}

	//One Argument Constructor
	Product::Product(char type) {
		m_type = type;
		SES();
	}

	//Seven Arguement Constructor
	Product::Product(const char* n_sku, const char* n_name, const char* n_unit, int n_qty, bool isTaxed, double n_price, int n_qtyNeed) {

		// Copy/Pass over the values from the parameters into the data members.
		strncpy(m_sku, n_sku, max_sku_length);
		m_sku[max_sku_length] = '\0';

		//Name Function :: Allocates specific memory space to the name data member.
		name(n_name);

		strncpy(m_unit, n_unit, max_unit_length);
		m_unit[max_unit_length] = '\0';

		m_quantity = n_qty;
		m_quantity_need = n_qtyNeed;
		m_tax = isTaxed;
		m_cost = n_price;

	}

	//Copy Constructor:: Takes a reference to an object and copies over their values 
	//into the current object.
	Product::Product(const Product &pro) {
		// Copy/Pass over the values from the object's data members into the current's data members.
		strcpy(m_sku, pro.m_sku);

		//Name Function :: Allocates specific memory space to the name data member.
		name(pro.m_name);

		strcpy(m_unit, pro.m_unit);

		m_quantity = pro.m_quantity;
		m_tax = pro.m_tax;
		m_cost = pro.m_cost;
		m_quantity_need = pro.m_quantity_need;

	}

	//Copy Assignment Constructor :: Copies the data members from the referenced objects and stores
	//them into the current Object.
	Product& Product::operator=(const Product & pro) {
		//Compares to see if the current object does not equal referenced object. If it does
		//no assignment needs to be carried out.
		if (this != &pro) {

			// Copy/Pass over the values from the object's data members into the current's data members.
			strcpy(m_sku, pro.m_sku);
			//Name Function :: Allocates specific memory space to the name data member.
			name(pro.m_name);
			strcpy(m_unit, pro.m_unit);

			m_quantity = pro.m_quantity;
			m_tax = pro.m_tax;
			m_cost = pro.m_cost;
			m_quantity_need = pro.m_quantity_need;

		}
		//Return the current object
		return *this;
	}

	Product::~Product() {
		//Deallocates memory stored in the address.
		delete[] address;
	}

	//Purpose:: To store information into a file. 
	std::fstream& Product::store(std::fstream& file, bool newLine) const {

		//Stores the data members of the current object into a file.
		file << m_type << ',' << m_sku << ',' << m_name << ',' << m_unit << ',' << m_tax << ',' << m_cost << ',' << m_quantity << ',' << m_quantity_need;

		//If there is a new line, append a new line.
		if (newLine == true) {
			file << endl;
		}

		return file;
	}

	std::fstream& Product::load(std::fstream& file) {
		char tempSku[max_sku_length + 1];
		char tempName[max_name_length + 1];
		char tempUnit[max_unit_length + 1];
		double tempPrice;
		bool tempTaxed;
		int tempQty;
		int tempQtyNeed;

		//Comparison to see if the file is open. 
		if (file.is_open()) {
			//If the file is open, append the contents in the file to the screen. 

			file.getline(tempSku, max_sku_length + 1, ',');
			tempSku[strlen(tempSku)] = '\0';
			file.getline(tempName, 21, ',');
			tempName[strlen(tempName)] = '\0';
			file.getline(tempUnit, 11, ',');
			tempUnit[strlen(tempUnit)] = '\0';
			file >> tempTaxed;
			file.ignore();
			file >> tempPrice;
			file.ignore();
			file >> tempQty;
			file.ignore();
			file >> tempQtyNeed;
			file.ignore();

			Product pro = Product(tempSku, tempName, tempUnit, tempQty, tempTaxed, tempPrice, tempQtyNeed);
			*this = pro;

		}

		return file;
	}

	std::ostream& Product::write(std::ostream& os, bool linear) const {

		//Compare to see if all of the Product information can fit on one line. 
		if (error.isClear()) {
			if (linear == true) {

				//If yes, append the Product Information to the screen in a specific format. 
				os << setw(max_sku_length) << left << sku() << '|'
					<< setw(20) << left << name() << '|'
					<< setw(7) << right << fixed << setprecision(2) << cost() << '|'
					<< setw(4) << right << quantity() << '|'
					<< setw(10) << left << unit() << '|'
					<< setw(4) << right << qtyNeeded() << '|';
			}
			else {

				//If no, append the Product Information to the screen on seperate lines. 
				os << " Sku: " << sku() << std::endl;
				os << " Name (no spaces): " << name() << std::endl;
				os << " Price: " << price() << std::endl;
				os << " Price after tax: ";
				if (taxed()) {
					os << cost() << std::endl;
				}
				else {
					os << " N/A" << std::endl;
				}
				os << " Quantity on Hand: " << quantity() << " " << unit() << std::endl;
				os << " Quantity needed: " << qtyNeeded() << "";	
				std::cin.ignore(1000, '\n');
			}
		}
	
		else {
			cout << error;
		}

		return os;
	}

	//Ask the user to enter the Product Information and store the input stream into 
	//the variables.
	std::istream & Product::read(std::istream & is) {
		char result = ' ';
		char n_sku[max_sku_length + 1];
		char n_unit[max_unit_length + 1];
		char n_name[max_name_length + 1];
		bool tax;
		double price = 0.00;
		int qty = 0;
		int qty_need = 0;

		//Ask the user to enter the Sku
		std::cout << " Sku: ";
		is >> n_sku;

		//Ask the user to enter the Name of the Product
		std::cout << " Name (no spaces): ";
		is >> n_name;

		//Ask the user to enter the Unit of the Product
		std::cout << " Unit: ";
		is >> n_unit;

		//Ask the user to enter if the Product needs to be taxed.
		std::cout << " Taxed? (y/n): ";
		std::cin >> result;

		if (result == 'y' || result == 'Y') {
			tax = true;
		}
		else if (result == 'n' || result == 'N') {
			tax = false;
		}
		//Display the error message.
		else {

			error.message("Only (Y)es or (N)o are acceptable");
			is.setstate(std::ios::failbit);
		}

		//Ask the user to enter the Price of the Product.
		if (!is.fail()) {
			std::cout << " Price: ";
			is >> price;

			//Display the Error Message
			if (is.fail()) {
				is.setstate(std::ios::failbit);
				error.message("Invalid Price Entry");
			}

		}

		//Ask the user to enter the Quantity of the Product on hand.
		if (!is.fail()) {
			std::cout << " Quantity on hand: ";
			is >> qty;

			//Display the Error Message
			if (is.fail()) {
				error.message("Invalid Quantity Entry");
			}

		}

		//Ask the user to enter the Quantity of the Product needed.
		if (!is.fail()) {
			std::cout << " Quantity needed: ";
			is >> qty_need;

			//Display the Error Message
			if (is.fail()) {
				error.message("Invalid Quantity Needed Entry");
			}

		}

		//If the Product information was entered successfully store the product into
		//the data members using the constructor and the copy constructor.
		if (!is.fail()) {
			error.clear();
			Product pro = Product(n_sku, n_name, n_unit, qty, tax, price, qty_need);
			*this = pro;
		}

		//Return the input stream
		return is;
	}

	//Compare to see if the Sku of each Product is the same. Return 
	// True if it is. 
	bool Product::operator==(const char* n_sku) const {
		bool result = true;

		if (n_sku == sku()) {
			result = true;
		}
		else {
			result = false;
		}

		return result;
	}

	//Calculate the total cost of the Product. 
	//Price of the Product * current tax rate.
	double Product::total_cost() const {
		double tax = price() * TAX_RATE;
		double taxedProduct = tax + price();
		double total = quantity() * taxedProduct;

		return total;
	}

	//Accepts a quanity in hand value and replaces the current data member 
	//with the one received.
	void Product::quantity(int n_quantity) {
		m_quantity = n_quantity;
	}

	//Compare to see if current Product is empty. Return true if it is. 
	bool Product::isEmpty() const {
		bool result = true;

		if (m_sku == nullptr && m_name == nullptr && m_unit == nullptr && m_quantity < 0 && m_cost < 0 && m_quantity_need < 0) {
			result = true;
		}
		else {
			result = false;
		}

		return result;
	}

	//Return the current Quantity Needed value. 
	int Product::qtyNeeded() const {
		return m_quantity_need;
	}

	//Return the current Quantity on Hand value. 
	int Product::quantity() const {
		return m_quantity;
	}

	//Compare to see if the current Sku is greater than 
	//the received value. Return true if it is. 
	bool Product::operator>(const char * n_sku) const {
		bool result = true;

		if (sku() > n_sku) {
			result = true;
		}
		else {
			result = false;
		}

		return result;
	}

	//Compare to see if the length of the current Product's name 
	//is greater than the name of the received Product. Return True if it is. 
	bool Product::operator>(const iProduct& pro) const {
		bool result = true;

		if (strlen(name()) > strlen(pro.name())) {
			result = true;
		}
		else {
			result = false;
		}

		return result;
	}

	//Take the receiving value and add it towards the current quantity.
	int Product::operator+=(int number) {

		if (number > 0) {
			m_quantity += number;
		}

		return m_quantity;
	}

	//Overload the operator (<<) and write a record into the Product object using ostream.
	std::ostream& operator<<(std::ostream& os, const iProduct& pro) {
		return pro.write(os, true);
	}

	//Overload the operator (>>) and read the input from the Product Object. 
	std::istream& operator>>(std::istream& is, iProduct& pro) {
		return pro.read(is);
	}

	//Take the receiving number and it towards the total cost of the Product.
	double operator+=(double& number, const iProduct& pro) {
		return number + pro.total_cost();
	}
}
