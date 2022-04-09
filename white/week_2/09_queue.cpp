#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

enum mood {WORRY, QUIET};

void make_worry(std::vector<mood> &people, int i) {
	people[i] = WORRY;
}

void make_quiet(std::vector<mood> &people, int i) {
	people[i] = QUIET;
}

void come(std::vector<mood> &people, int k) {
	if (k > 0)
		people.resize(people.size() + k, mood::QUIET);
	if (k < 0)
		people.resize(people.size() + k);
}

int count_worry(const std::vector<mood> &people) {
	return std::count(people.begin(), people.end(), mood::WORRY);
}

/*
8
COME 5
WORRY 1
WORRY 4
COME -2
WORRY_COUNT
		COME 3
WORRY 3
WORRY_COUNT
*/

/*
1
2
*/

int main()
{
	int n;
	std::cin >> n;
	
	std::vector<mood> people;
	for (int i = 0; i < n; ++i) {
		std::string command;
		std::cin >> command;
		if (command == "WORRY_COUNT") {
			std:: cout << count_worry(people) << std::endl;
			continue;
		}
		int param;
		std::cin >> param;
		if (command == "COME")
			come(people, param);
		if (command == "WORRY")
			make_worry(people, param);
		if (command == "QUIET")
			make_quiet(people, param);
	}
	
	return 0;
}
