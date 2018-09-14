
#include <iostream>
#include "Mangement.h"
#include "Product.h"
#include <fstream>

using namespace std;
using namespace AMA;

namespace ProductMang {

	void Manager::ProductMangementSystem() {

		bool quit = false;

		while (quit != true) {
			MangementTitle();
			cout << endl;

			cout << "1. Display Products" << endl;
			cout << "2. Add a Product" << endl;
			cout << "3. Delete a Product" << endl;
			cout << "0. Exit" << endl << endl;

			cout << "Please select one of the options: ";
			int input;
			cin >> input;
			cout << endl;

			switch (input) {
			case 1:
				displayProduct();
				break;
			case 2:
				addProduct();
				break;
			case 3:
				break;
			}

		}
	}

	void Manager::ProductTitle() {
		cout << "+-----------------------------------------------------------+" << endl <<
			"|                                                           |" << endl <<
			"|                    Product Listing                        |" << endl <<
			"|                                                           |" << endl <<
			"+-----------------------------------------------------------+" << endl;
	}

	void Manager::ProductFooter() {
		cout << "Number of Products: " << counter;
	}

	void Manager::MangementTitle() {
		cout << "+-----------------------------------------------------------+" << endl <<
			"|                                                           |" << endl <<
			"|               Product Mangement System                    |" << endl <<
			"|                                                           |" << endl <<
			"+-----------------------------------------------------------+" << endl;
	}

	void Manager::displayProduct() {
		ProductTitle();
		cout << endl;

		OpenProductFile();

		cout << endl;

		ProductFooter();
		cout << endl << endl;
	}

	void Manager::OpenProductFile() {
		fstream productFile;
		Product newPro;

		productFile.open("product.txt", ios::in);
		productFile.ignore(2);

		newPro.load(productFile);
		cout << newPro << endl;

		productFile.clear();
		productFile.close();

	}

	void Manager::addProduct() {
		fstream productFile("product.txt", ios::app);

		cout << "Adding New Product - Activated" << endl;
		cout << "------------------------------" << endl;

		Product newPro;
		cin >> newPro;
		counter++;

		newPro.store(productFile);
		productFile.close();
		cout << endl;
	}
}
