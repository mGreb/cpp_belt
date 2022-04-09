#include <string>
#include <stdexcept>
#include <exception>
#include <iostream>
#include <sstream>
#include <numeric>

class Rational {
public:
	Rational() {numerator = 0; denominator = 1;}
	Rational(long int numerator_, long int denominator_)
		: numerator(numerator_), denominator(denominator_) {
		if (denominator == 0)
			throw std::invalid_argument("Invalid argument");
		const int div = std::gcd(numerator, denominator);
		numerator /= div;
		denominator /= div;
		if (denominator < 0) {
			denominator = -denominator;
			numerator = -numerator;
		}
	}
	[[nodiscard]] long int Numerator() const {return numerator;}
	[[nodiscard]] long int Denominator() const {return denominator;}
	
	Rational operator+(const Rational &r) const {
		const long int a = numerator, b = denominator;
		const long int c = r.numerator, d = r.denominator;
		return Rational(a * d + b * c, b * d);
	}
	Rational operator-(const Rational &r) const {
		const long int a = numerator, b = denominator;
		const long int c = - r.numerator, d = r.denominator;
		return Rational(a * d + b * c, b * d);
	}
	Rational operator*(const Rational &r) const {
		const long int a = numerator, b = denominator;
		const long int c = r.numerator, d = r.denominator;
		return Rational(a * c, b * d);
	}
	Rational operator/(const Rational &r) const {
		const long int a = numerator, b = denominator;
		const long int c = r.numerator, d = r.denominator;
		if (b * c == 0)
			throw std::domain_error("Division by zero");
		return Rational(a * d, b * c);
	}
	bool operator==(const Rational &r) const {
		const long int a = numerator, b = denominator;
		const long int c = r.numerator, d = r.denominator;
		return a == c && b == d;
	}
	bool operator<(const Rational &r) const {
		const long int a = numerator, b = denominator;
		const long int c = r.numerator, d = r.denominator;
		return a * d < c * b;
	}
	bool operator>(const Rational &r) const {
		const long int a = numerator, b = denominator;
		const long int c = r.numerator, d = r.denominator;
		return a * d > c * b;
	}
private:
	long int numerator, denominator;
};

std::ostream& operator<<(std::ostream &o, const Rational &r) {
	o << r.Numerator() << "/" << r.Denominator();
	return o;
}

std::istream& operator>>(std::istream &i, Rational &r) {
	
	long int a = 0, b = 1;
	char c;
	
	i >> a >> c >> b;
	
	if (!i.fail() && c == '/')
		r = Rational(a, b);
	
	return i;
}

/*
stdin		stdout
1/2 + 1/3	5/6
1/2 + 5/0	Invalid argument
4/5 / 0/8	Division by zero
*/

int main() {
	Rational a, b;
	char op;
	
	try {
		std::cin >> a >> op >> b;
		switch (op) {
			case '+' :
				std::cout << a + b;
				break;
			case '-' :
				std::cout << a - b;
				break;
			case '*' :
				std::cout << a * b;
				break;
			case '/' :
				std::cout << a / b;
				break;
			default:
				break;
		}
	} catch (const std::exception & e) {
		std::cout << e.what();
	}
	
	return 0;
}
