#include <string>
#include <iostream>
#include <set>
#include <map>

std::set<std::string> BuildMapValuesSet(const std::map<int, std::string>& m) {
	std::set<std::string> unique_strings;
	for (const auto &item : m)
		unique_strings.insert(item.second);
	return unique_strings;
}

#define MAIN  // comment before sending submission

#ifdef MAIN
int main() {
	
	std::map<int, std::string> m = {{1, "odd"}, {2, "even"},
								 {3, "odd"}, {4, "even"}, {5, "odd"}};
	std::set<std::string> values = BuildMapValuesSet(m);
	
	for (const std::string& value : values)
		std::cout << value << std::endl;
	
	return 0;
}
#endif
