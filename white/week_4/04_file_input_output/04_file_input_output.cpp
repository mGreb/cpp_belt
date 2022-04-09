#include <fstream>
#include <iostream>

int main() {
	std::ifstream input("input.txt");
	if (input.is_open()) {
		std::string line;
		std::ostream &output = std::cout;  // first variant
//		std::ofstream output("output.txt");  // second variant
		while (std::getline(input, line))
			output << line << std::endl;
	}
	return 0;
}
