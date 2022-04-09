#include <iostream>
#include <vector>

int main()
{
	int n;
	std::cin >> n;
	
	std::vector<int> binary;
	while (n > 0) {
		binary.push_back(n % 2);
		n /= 2;
	}
	
	for (int i = binary.size() - 1; i >= 0; --i)
		std::cout << binary[i];
	
	return 0;
}
