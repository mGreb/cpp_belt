#include <iostream>
#include <cmath>

int main()
{
	int a = 0, b = 0;
	std::cin >> a >> b;
	
	if (b == 0) {
		std::cout << "Impossible";
		return 0;
	}
	
	std::cout << a / b;
	
	return 0;
}
