#ifndef MANGEMENT_H
#define MANGEMENT_H

#include "Perishable.h"

using namespace AMA;

namespace ProductMang {

	class Manager : public Perishable {

	public:
		int counter = 0;

		void ProductMangementSystem();
		void ProductTitle();
		void ProductFooter();

		void MangementTitle();

		void displayProduct();
		void OpenProductFile();

		void addProduct();

	};
}

#endif // !MANGEMENT_H

