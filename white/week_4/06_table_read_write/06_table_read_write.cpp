#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>

int main() {
	std::ifstream input("input.txt");
	int n, m;
	input >> n >> m;
	input.ignore(1);
	for (int i = 0; i < n; ++i) {
		std::vector<int> line(m);
		for (int j = 0; j < m; ++j) {
			input >> line[j];
			input.ignore(1);
		}
		for (int j = 0; j < m-1; ++j)
			std::cout << std::setw(10) << line[j] << " ";
		std::cout << std::setw(10) << line[m-1];
		if (i != n-1)
			std::cout << std::endl;
	}
	return 0;
}
