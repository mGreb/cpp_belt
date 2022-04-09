#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <tuple>

bool is_leap_year(int y) {
	const bool mod4 = y % 4 == 0;
	const bool mod100 = y % 100 == 0;
	const bool mod400 = y % 400 == 0;
	return mod400 || (mod4 && !mod100);
}

const std::array<std::array<char, 12>, 2> days_months =
		{{
			{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
			{31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
		}};

const std::array<int, 2> days_year ={ 365, 366 };

std::vector<std::tuple<int, int, double>> earnings;

void earn(int days1, int days2, double sum) {
	const double earn_per_day = sum / (days2 - days1 + 1);
	earnings.emplace_back(days1, days2, earn_per_day);
}

int days_in_intersected_intervals(const std::pair<int, int> &a, const std::pair<int, int> &b) {
	const int left = std::max(a.first, b.first);
	const int right = std::min(a.second, b.second);
	const int len = right - left + 1;
	return  len > 0 ? len : 0;
}

double compute_income(int days1, int days2) {
	double result = 0;
	for (const auto &elem : earnings) {
		const int paid_days = days_in_intersected_intervals({days1, days2},
							  {std::get<0>(elem), std::get<1>(elem)});
		result += paid_days * std::get<2>(elem);
	}
	return result;
}

int date_to_days(int year, int month, int day) {
	int days = day;
	for (int i = 2000; i < year; ++i)
		days += days_year[is_leap_year(i)];
	bool is_leap = is_leap_year(year);
	for (int i = 0; i < month-1; ++i)
		days += days_months[is_leap][i];
	return days;
}
/*
5
Earn 2000-01-02 2000-01-06 20
ComputeIncome 2000-01-01 2001-01-01
ComputeIncome 2000-01-01 2000-01-03
Earn 2000-01-03 2000-01-03 10
ComputeIncome 2000-01-01 2001-01-01
*/

/*
20
8
30
*/

int main() {
	int n = 0;
	std::cin >> n;
	
	for (int i = 0; i < n; ++i) {
		std::string command;
		int year1, month1, day1, year2, month2, day2;
		std::cin >> command >> year1 >> month1 >> day1 >> year2 >> month2 >> day2;
		month1 *= -1; month2 *= -1; day1 *= -1; day2 *= -1;
		const int day_num1 = date_to_days(year1, month1, day1);
		const int day_num2 = date_to_days(year2, month2, day2);
		if (command == "Earn") {
			int sum;
			std::cin >> sum;
			earn(day_num1, day_num2, sum);
		}
		if (command == "ComputeIncome") {
			std::cout.precision(25);
			std::cout << compute_income(day_num1, day_num2) << std:: endl;
		}
	}
	return 0;
}
