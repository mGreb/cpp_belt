#include <iostream>
#include <cmath>

int Factorial(int x) {
	if (x < 0)
		return 1;
	
	int result = 1;
	for (int i = 1; i <= x; ++i)
		result *= i;
	return result;
}

int main()
{
	int a = Factorial(1);
	int b = Factorial(-2);
	int c = Factorial(4);
	
	return 0;
}
