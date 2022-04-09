#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <numeric>
#include <chrono>

void earn(unsigned long day, double amount, std::vector<double> &earnings_by_day) {
	earnings_by_day[day] = amount;
}

double compute_income(unsigned long day1, unsigned long day2, std::vector<double> &earnings_by_day_part_sum) {
	double m2 = earnings_by_day_part_sum.at(day2);
	double m1 = 0;
	if (day1 > 0)
		m1 = earnings_by_day_part_sum.at(day1-1);
	return m2 - m1;
}

time_t as_timestamp(int year, int month, int day) noexcept {
	tm t;
	t.tm_sec  = 0;
	t.tm_min  = 0;
	t.tm_hour = 0;
	t.tm_mday = day;
	t.tm_mon  = month - 1;
	t.tm_year = year - 1900;
	t.tm_isdst = 0;
	return mktime(&t);
}

static constexpr int SECONDS_IN_DAY = 60 * 60 * 24;
static const time_t START_DATE = as_timestamp(1700, 1, 1);
static const time_t   END_DATE = as_timestamp(2100, 1, 1);
static const size_t  DAY_COUNT = (END_DATE - START_DATE) / SECONDS_IN_DAY;

unsigned long date_to_days(int year, int month, int day) {
	time_t timestamp = as_timestamp(year, month, day);
	return (timestamp - START_DATE) / SECONDS_IN_DAY;
}

/*
3
2000-01-02 20
2000-01-06 10
2000-01-03 10
2
2000-01-01 2000-01-02
2000-01-02 2000-01-06
*/

/*
20
40
*/

int main() {
	
	std::vector<double>          earnings_by_day(DAY_COUNT);
	std::vector<double> earnings_by_day_part_sum(DAY_COUNT);
	
	int n = 0;
	std::cin >> n;
	
	for (int i = 0; i < n; ++i) {
		int year, month, day;
		int sum;
		std::cin >> year >> month >> day >> sum;
		month *= -1; day *= -1;
		const unsigned long day_num = date_to_days(year, month, day);
		earn(day_num, sum, earnings_by_day);
	}
	
	std::partial_sum(begin(earnings_by_day), end(earnings_by_day), begin(earnings_by_day_part_sum));
	
	std::cin >> n;
	for (int i = 0; i < n; ++i) {
		int year1, month1, day1, year2, month2, day2;
		std::cin >> year1 >> month1 >> day1 >> year2 >> month2 >> day2;
		month1 *= -1; month2 *= -1; day1 *= -1; day2 *= -1;
		const unsigned long day_num1 = date_to_days(year1, month1, day1);
		const unsigned long day_num2 = date_to_days(year2, month2, day2);
		std::cout.precision(25);
		std::cout << compute_income(day_num1, day_num2, earnings_by_day_part_sum) << std:: endl;
	}
	
	return 0;
}
