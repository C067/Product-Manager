//Callum Dodge
//100229178
//July 10, 2018

#ifndef ERRORSTATE_H
#define ERRORSTATE_H

namespace AMA {

	class ErrorState {

		//Data Member
		char * n_message;

	public:
		//Constructors
		explicit ErrorState(const char* errorMessage = nullptr);
		ErrorState(const ErrorState& em) = delete;

		//Destructor
		virtual ~ErrorState();
		
		//Member Functions
		void clear();
		bool isClear() const;
		void message(const char* str);
		const char* message() const;

		//Operators
		ErrorState& operator=(const ErrorState& em) = delete;
		ErrorState& operator=(const char * errorMessage);
		friend std::ostream& operator<<(std::ostream& ostr, const ErrorState& em);
	};
	std::ostream& operator<<(std::ostream& ostr, const ErrorState& em);

}


#endif // !ERRORSTATE_H

