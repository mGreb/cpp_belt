#include <iostream>
#include <cmath>

int main()
{
	double a = 0.0, b = 0.0, c = 0.0;
	std::cin >> a >> b >> c;
	
	if (a != 0 && b == 0 && c == 0) {
		std::cout << 0;
		return 0;
	}
	
	if (a == 0 && b != 0 && c == 0) {
		std::cout << 0;
		return 0;
	}
	
	if (a == 0 && b == 0 && c != 0)
		return 0;
	
	if (a == 0 && b != 0 && c != 0) {
		std::cout << - c / b;
		return 0;
	}
	
	const double d = b * b - 4.0 * a * c;
	
	if (d < 0.0)
		return 0;
	
	if (d == 0.0) {
		std::cout << - b / 2.0 / a;
		return 0;
	}
	
	const double x1 = (- b + sqrt(d)) / 2.0 / a;
	const double x2 = (- b - sqrt(d)) / 2.0 / a;
	std::cout << x1 << " " << x2;
	
	return 0;
}
