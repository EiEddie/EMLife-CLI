#ifndef EMLIFE_EML_EXCEPTION_H
#define EMLIFE_EML_EXCEPTION_H
enum ExceptionType {
	ERROR,
	WARNING
};

class ItemTooMuch: public std::bad_exception {
public:
	const char* what() const noexcept override {
		return "Too many diamonds and coins in total.";
	}
	
	ExceptionType type() const noexcept {
		return WARNING;
	}
};
#endif //EMLIFE_EML_EXCEPTION_H
