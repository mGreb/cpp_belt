#include <iostream>

int main()
{
	int a, b;
	std::cin >> a >> b;
	
	while (a != 0 && b != 0) {
		if (a > b)
			a = a % b;
		else
			b = b % a;
	}
	
	std::cout << std::max(a, b);
	
	return 0;
}
