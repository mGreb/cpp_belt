#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <numeric>

// comment out this class before sending!
class Rational {
public:
	Rational() {numerator = 0; denominator = 1;}
	Rational(long int numerator_, long int denominator_)
			: numerator(numerator_), denominator(denominator_) {
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
	
	[[nodiscard]] std::array<long int, 2> Get() const {
		return {numerator, denominator};
	}
	
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

std::istringstream& operator>>(std::istringstream &i, Rational &r) {

	long int a = 0, b = 1;
	char c;

	i >> a >> c >> b;

	if (!i.fail() && c == '/')
		r = Rational(a, b);

	return i;
}

template <class T>
std::ostream& operator << (std::ostream& os, const std::array<T, 2>& a) {
	return os << "{" << a[0] << ", " << a[1] << "}";
}

template <class T>
std::ostream& operator << (std::ostream& os, const std::vector<T>& s) {
	os << "{";
	bool first = true;
	for (const auto& x : s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template <class T>
std::ostream& operator << (std::ostream& os, const std::set<T>& s) {
	os << "{";
	bool first = true;
	for (const auto& x : s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template <class K, class V>
std::ostream& operator << (std::ostream& os, const std::map<K, V>& m) {
	os << "{";
	bool first = true;
	for (const auto& kv : m) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << kv.first << ": " << kv.second;
	}
	return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const std::string& hint = {}) {
	if (t != u) {
		std::ostringstream os;
		os << "Assertion failed: " << t << " != " << u;
		if (!hint.empty()) {
			os << " hint: " << hint;
		}
		throw std::runtime_error(os.str());
	}
}

void Assert(bool b, const std::string& hint) {
	AssertEqual(b, true, hint);
}

class TestRunner {
public:
	template <class TestFunc>
	void RunTest(TestFunc func, const std::string& test_name) {
		try {
			func();
			std::cerr << test_name << " OK" << std::endl;
		} catch (std::exception& e) {
			++fail_count;
			std::cerr << test_name << " fail: " << e.what() << std::endl;
		} catch (...) {
			++fail_count;
			std::cerr << "Unknown exception caught" << std::endl;
		}
	}

	~TestRunner() {
		if (fail_count > 0) {
			std::cerr << fail_count << " unit tests failed. Terminate" << std::endl;
			exit(1);
		}
	}

private:
	int fail_count = 0;
};

typedef std::array<long int, 2> arr_li_2;

arr_li_2 Get(Rational r) {
	return {r.Numerator(), r.Denominator()};
}

void Test() {

	AssertEqual(Get(Rational(  0,  10)), arr_li_2{0, 1}, "Rational(  0,  10) != 0/1");
	AssertEqual(Get(Rational(  0, -10)), arr_li_2{0, 1}, "Rational(  0, -10) != 0/1");
	AssertEqual(Get(Rational(-10, -10)), arr_li_2{1, 1}, "Rational(-10, -10) != 1/1");
	
	AssertEqual(Get(Rational( 3, 10)), arr_li_2{ 3, 10}, "Rational( 3, 10) !=  3/10");
	AssertEqual(Get(Rational( 8, 12)), arr_li_2{ 2, 3}, "Rational( 8, 12) !=  2/ 3");
	
	AssertEqual(Get(Rational(-4,  6)), arr_li_2{-2, 3}, "Rational(-4, 6) != -2/3");
	AssertEqual(Get(Rational( 4, -6)), arr_li_2{-2, 3}, "Rational(4, -6) != -2/3");
	
	AssertEqual(Get(Rational(0, 15)), arr_li_2{0, 1}, "Rational(0, 15) != 0/1");
	
	AssertEqual(Get(Rational()), arr_li_2{0, 1}, "Rational() != 0/1");
	
	AssertEqual(Get(Rational(4, 6)), Get(Rational(2, 3)), "4/6 != 2/3");
	
//	Rational c = Rational(2, 3) + Rational(4, 3);
//	AssertEqual(Get(c), Get(Rational(2, 1)), "2/3 + 4/3 != 2");
	
//	AssertEqual(Get(Rational(5, 7) - Rational(2, 9)), Get(Rational(31, 63)), "5/7 - 2/9 != 31/63");
	
//	AssertEqual(Get(Rational( 2, 3) * Rational(4, 3)), Get(Rational( 8, 9)), " 2/3 * 4/3 !=  8/9");
//	AssertEqual(Get(Rational(-2, 3) * Rational(4, 3)), Get(Rational(-8, 9)), "-2/3 * 4/3 != -8/9");
	
	/*{
		Rational a(5, 4);
		Rational b(15, 8);
		Rational c = a / b;
		bool equal = c == Rational(2, 3);
		AssertEqual(equal, true, "5/4 / 15/8 != 2/3");
	}*/
	
	/*{
		const set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
		
		AssertEqual(rs.size(), 3, "Wrong amount of items in the set");
		
		vector<Rational> v;
		for (auto x : rs)
			v.push_back(x);
		
		AssertEqual(v, vector<Rational>{{1, 25}, {1, 2}, {3, 4}},
			  "Rationals comparison works incorrectly");
	}*/
	
	/*{
		map<Rational, int> count;
		++count[{1, 2}];
		++count[{1, 2}];
		++count[{2, 3}];
		
		AssertEqual(count.size(), 2, "Wrong amount of items in the map");
	}*/
}

int main() {
	TestRunner runner;
	
	runner.RunTest(Test, "all tests");
	
	return 0;
}
