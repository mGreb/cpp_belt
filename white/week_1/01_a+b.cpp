#include <iostream>

int main()
{
	int a = 0, b = 0;
	
	std::cin >> a;
	std::cin >> b;
	
	const int c = a + b;
	
	std::cout << c;
	
	return 0;
}
