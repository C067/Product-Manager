//Callum Dodge
//100229178
//July 10, 2018

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "ErrorState.h"
#include <cstring>

using namespace std;

namespace AMA {

	//Constructors
	ErrorState::ErrorState(const char * errorMessage) {

		//Checks to see if the message is cleared.
		if (errorMessage == nullptr) {
			n_message = nullptr;
		}
		else {
			n_message = nullptr;
			message(errorMessage);
		}
	}

	//Deletes the object when it goes out of scope.
	ErrorState::~ErrorState() {
		if (!isClear()) {
			delete[] n_message;
		}
	}

	//Deallocates the current message and clears any data.
	void ErrorState::clear() {
		delete[] n_message;
		n_message = nullptr;
	}

	//Compares to see if the data member has any messages stored. If yes return true, if no return false.
	bool ErrorState::isClear() const {
		bool result = true;

		if (n_message == nullptr) {
			result = true;
		}
		else {
			result = false;
		}

		return result;
	}

	//Deallocates the current message, allocates the new message and then store the message
	//into the data member.
	void ErrorState::message(const char* str) {

		if (n_message != nullptr) {
			delete[] n_message;
			n_message = nullptr;
		}

		n_message = new char[strlen(str) + 1];
		strcpy(n_message, str);

	}

	//Returns the Message
	const char* ErrorState::message() const {
		return n_message;
	}


	ErrorState& ErrorState::operator= (const char * errorMessage) {
		this->clear();
		this->n_message = nullptr;
		return *this;
	}

	//Displays the message to the screen.
	std::ostream& operator<<(std::ostream& ostr, const ErrorState& em) {
		if (!em.isClear()) {
			ostr << em.n_message;
		}
	
		return ostr;
	}



}