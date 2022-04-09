#include <string>
#include <iostream>
#include <set>

std::string get_string() {
	std::string s;
	std::cin >> s;
	return s;
}

int get_int() {
	int s;
	std::cin >> s;
	return s;
}

int main()
{
	int n = 0;
	std::cin >> n;
	
	std::set<std::string> unique_strings;
	
	for (int i = 0; i < n; ++i) {
		std::string s = get_string();
		unique_strings.insert(s);
	}
	
	std::cout << unique_strings.size() << std::endl;
	
	return 0;
}
