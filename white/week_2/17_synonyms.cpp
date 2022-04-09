#include <string>
#include <iostream>
#include <set>
#include <map>

std::map<std::string, std::set<std::string>> dict;

void add(const std::string &w1, const std::string &w2) {
	dict[w1].insert(w2);
	dict[w2].insert(w1);
}

void count(const std::string &w) {
	std::cout << dict[w].size() << std::endl;
}

void check(const std::string &w1, const std::string &w2) {
	if (dict[w1].find(w2) != dict[w1].end())
		std::cout << "YES" << std::endl;
	else
		std::cout << "NO" << std::endl;
}

/*
8
ADD program code
COUNT cipher
 ADD code cipher
COUNT code
COUNT program
CHECK code program
CHECK program cipher
CHECK cpp java

0
2
1
YES
NO
NO
*/

int main()
{
	int n = 0; std::cin >> n;
	
	for (int i = 0; i < n; ++i) {
		std::string command; std::cin >> command;
		if (command == "ADD") {
			std::string w1; std::cin >> w1;
			std::string w2; std::cin >> w2;
			add(w1, w2);
		}
		if (command == "COUNT") {
			std::string w; std::cin >> w;
			count(w);
		}
		if (command == "CHECK") {
			std::string w1; std::cin >> w1;
			std::string w2; std::cin >> w2;
			check(w1, w2);
		}
	}
	
	return 0;
}
