#include <fstream>
#include <iostream>
#include <iomanip>

int main() {
	std::ifstream input("input.txt");
	if (input.is_open()) {
		double val;
		std::cout << std::fixed << std::setprecision(3);
		while(input >> val)
			std::cout << val << std::endl;
	}
	return 0;
}
