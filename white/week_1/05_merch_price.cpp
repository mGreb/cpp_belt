#include <iostream>
#include <cmath>

int main()
{
	double n = 0., a = 0., b = 0., x = 0., y = 0.;
	std::cin >> n >> a >> b >> x >> y;
	
	x /= 100.;
	y /= 100.;
	
	if (n > b) {
		std::cout << n - n * y;
		return 0;
	}
	
	if (n > a) {
		std::cout << n - n * x;
		return 0;
	}
	
	std::cout << n;
	
	return 0;
}
