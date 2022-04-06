#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

std::vector<std::string> SplitIntoWords(const std::string& s) {
	std::vector<std::string> res;
	auto it1 = s.begin();
	while (true) {
		auto it2 = std::find(it1, s.end(), ' ');
		res.emplace_back(std::string{it1, it2});
		if (it2 == s.end())
			break;
		it1 = ++it2;
	}
	return res;
}

int main() {
	std::string s = "C Cpp Java Python";
	
	std::vector<std::string> words = SplitIntoWords(s);
	std::cout << words.size() << " ";
	for (auto it = begin(words); it != end(words); ++it) {
		if (it != begin(words)) {
			std::cout << "/";
		}
		std::cout << *it;
	}
	std::cout << std::endl;

	return 0;
}
