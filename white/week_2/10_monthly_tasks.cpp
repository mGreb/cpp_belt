#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

void add(
	std::vector<std::vector<std::vector<std::string>>> &list,
	int month, int day, const std::string &task
) {
	list[month][day].push_back(task);
}

void dump(
	std::vector<std::vector<std::vector<std::string>>> &list,
	int month, int day
) {
	std::cout << list[month][day].size() << " ";
	for(const std::string &task: list[month][day])
		std::cout << task << " ";
	std::cout << std::endl;
}

void next(
	std::vector<std::vector<std::vector<std::string>>> &list,
	int &month
) {
	int curr_month = month;
	int next_month = month + 1 > 11 ? 0 : month + 1;
	
	int curr_size = list[curr_month].size();
	int next_size = list[next_month].size();
	
	int min_size = std::min(curr_size, next_size);
	for (int i = 0; i < min_size; ++i)
		list[next_month][i] = list[curr_month][i];
	
	if (curr_size > next_size)
		for (int i = next_size; i < curr_size; ++i)
			for (int j = 0; j < list[curr_month][i].size(); ++j)
				list[next_month].back().push_back(list[curr_month][i][j]);
	
	if (curr_size < next_size)
		for (int i = curr_size; i < next_size; ++i)
			list[next_month][i].clear();
	
	month = next_month;
}

/*
12
ADD 5 Salary
ADD 31 Walk
ADD 30 WalkPreparations
NEXT
DUMP 5
DUMP 28
NEXT
DUMP 31
DUMP 30
DUMP 28
ADD 28 Payment
DUMP 28
*/

/*
1 Salary
2 WalkPreparations Walk
0
0
2 WalkPreparations Walk
3 WalkPreparations Walk Payment
*/

int main()
{
	std::vector<std::vector<std::vector<std::string>>> list(12);
	
	std::vector<int> days_in_month = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	for (int i = 0; i < list.size(); ++i)
		list[i].resize(days_in_month[i]);
	
	int ops;
	std::cin >> ops;
	
	int month = 0;
	
	for (int i = 0; i < ops; ++i) {
		std::string command; std::cin >> command;
		
		if (command == "ADD") {
			int day; std::cin >> day;
			std::string task; std::cin >> task;
			add(list, month, day - 1, task);
		}
		
		if (command == "NEXT")
			next(list, month);
		
		if (command == "DUMP") {
			int day; std::cin >> day;
			dump(list, month, day - 1);
		}
	}
	
	return 0;
}
