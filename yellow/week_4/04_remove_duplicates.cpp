#include <vector>
#include <string>
#include <set>
#include <iostream>
#include <algorithm>

template <typename T>
void RemoveDuplicates_bad(std::vector<T>& elements) {
	// place uniques into set
	std::set<T> temp;
	for (const auto &element : elements)
		temp.insert(element);
	
	// place set into vector
	elements.clear();
	for (const auto &t : temp)
		elements.template emplace_back(t);
}

template <typename DataType>
void RemoveDuplicates(std::vector<DataType>& elements) {
	std::sort(begin(elements), end(elements));
	elements.erase(
			std::unique(begin(elements), end(elements)),
			elements.end());
}

int main() {
	std::vector<int> v1 = {6, 4, 7, 6, 4, 4, 0, 1};
	RemoveDuplicates(v1);
	for (int x : v1) {
		std::cout << x << " ";
	}
	std::cout << std::endl;
	
	std::vector<std::string> v2 = {"C", "C++", "C++", "C", "C++"};
	RemoveDuplicates(v2);
	for (const std::string& s : v2) {
		std::cout << s << " ";
	}
	std::cout << std::endl;
	return 0;
}
