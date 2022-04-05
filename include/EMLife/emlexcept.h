#ifndef EMLIFE_EMLEXCEPT_H
#define EMLIFE_EMLEXCEPT_H
enum ExceptionType {
	ERROR,
	WARNING
};


class CoinTooMuch: public std::bad_exception {
private:
	int coin_count;
	
public:
	explicit CoinTooMuch(int coin_count):
	coin_count(coin_count) {}
	
	const char* what() const noexcept override {
		return "Too many coins in total.";
	}
	
	ExceptionType type() const noexcept {
		return WARNING;
	}
	
	inline int GetCoinCount() const {
		return coin_count;
	}
};


class DiamondTooMuch: public std::bad_exception {
public:
	const char* what() const noexcept override {
		return "Too many diamonds in total.";
	}
	
	ExceptionType type() const noexcept {
		return ERROR;
	}
};
#endif //EMLIFE_EMLEXCEPT_H
