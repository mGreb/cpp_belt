#include <set>
#include <string>
#include <vector>
#include <iostream>

template <typename T>
std::vector<T> FindGreaterElements(const std::set<T>& elements, const T& border) {
	if (elements.empty())
		return {};
	
	auto it = elements.begin();
	
	for (; it != elements.end(); ++it)
		if (*it > border)
			break;
	
	return {it, elements.end()};
}

int main() {
	std::vector<int> vec = {1, 5, 7, 8};
	for (auto x : {vec.begin(), vec.end()}) {
		std::cout << *x << " ";
	}
	std::cout << std::endl;
	
	for (int x : FindGreaterElements(std::set<int>{1, 5, 7, 8}, 5)) {
		std::cout << x << " ";
	}
	std::cout << std::endl;

	for (int x : FindGreaterElements(std::set<int>{1, 5, 7, 8}, 6)) {
		std::cout << x << " ";
	}
	std::cout << std::endl;

	std::string to_find = "Python";
	std::cout << FindGreaterElements(std::set<std::string>{"C", "C++"}, to_find).size() << std::endl;
	return 0;
}
