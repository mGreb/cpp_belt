#include <string>
#include <stdexcept>
#include <exception>
#include <iostream>
#include <sstream>
#include <numeric>
#include <iostream>

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

int main() {
	try {
		Rational r(1, 0);
		std::cout << "Doesn't throw in case of zero denominator" << std::endl;
		return 1;
	} catch (std::invalid_argument&) {
	}
	
	try {
		auto x = Rational(1, 2) / Rational(0, 1);
		std::cout << "Doesn't throw in case of division by zero" << std::endl;
		return 2;
	} catch (std::domain_error&) {
	}
	
	std::cout << "OK" << std::endl;
	return 0;
}