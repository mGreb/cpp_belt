#include <string>
#include <stdexcept>
#include <iostream>

void EnsureEqual(const std::string &s1, const std::string &s2) {
	if (s1 != s2)
		throw std::runtime_error(s1 + " != " + s2);
}

int main() {
	try {
		EnsureEqual("C++ White", "C++ White");
		EnsureEqual("C++ White", "C++ Yellow");
	} catch (std::runtime_error& e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}
