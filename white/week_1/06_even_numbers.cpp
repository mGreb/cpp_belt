#include <iostream>
#include <cmath>

int main()
{
	int a = 0, b = 0;
	std::cin >> a >> b;
	
	for (int i = a; i <= b; ++i) {
		if (i % 2 == 0)
			std::cout << i << " ";
	}
	
	return 0;
}
