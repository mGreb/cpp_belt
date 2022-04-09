#include <iostream>
#include <string>
#include <vector>

struct Student {
	std::string first_name;
	std::string last_name;
	int day_of_birth;
	int month_of_birth;
	int year_of_birth;
};

/*
3
Ivan Ivanov 1 1 1901
Petr Petrox 2 2 1902
Alexander Sidorov 3 3 1903
3
name 1
date 3
mark 5

Ivan Ivanov
3.3.1903
bad request
*/

int main() {
	
	int people_num; std::cin >> people_num;
	std::vector<Student> students;
	for (int i = 0; i < people_num; ++i) {
		std::string first_name; std::cin >> first_name;
		std::string last_name; std::cin >> last_name;
		int day_of_birth; std::cin >> day_of_birth;
		int month_of_birth; std::cin >> month_of_birth;
		int year_of_birth; std::cin >> year_of_birth;
		students.emplace_back(Student{first_name, last_name,
								day_of_birth, month_of_birth, year_of_birth});
	}
	
	int cmd_num; std::cin >> cmd_num;
	for (int i = 0; i < cmd_num; ++i) {
		std::string cmd; std::cin >> cmd;
		int arg; std::cin >> arg; arg -= 1;
		bool arg_is_in_range = arg < students.size();
		if (cmd != "name" && cmd != "date" || !arg_is_in_range) {
			std::cout << "bad request" << std::endl;
			continue;
		}
		if (cmd == "name")
			std::cout << students[arg].first_name << " " << students[arg].last_name << std::endl;
		if (cmd == "date")
			std::cout << students[arg].day_of_birth << "."
			<< students[arg].month_of_birth << "."
			<< students[arg].year_of_birth << std::endl;
	}
	
	return 0;
}
