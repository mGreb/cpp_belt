#include <string>
#include <vector>
#include <iostream>

int avg_val(const std::vector<int> &x) {
	int avg = 0;
	for (const int &a: x)
		avg += a;
	return avg / x.size();
}

int main()
{
	int n;
	std::cin >> n;
	
	std::vector<int> days(n);
	for (int &d: days)
		std::cin >> d;
	
	const int avg = avg_val(days);
	int cnt = 0;
	std::vector<int> hot_days;
	for (int i = 0; i < days.size(); ++i)
		if (days[i] > avg) {
			++cnt;
			hot_days.push_back(i);
		}
	
	std::cout << cnt << std::endl;
	for (const int &day: hot_days)
		std::cout << day << " ";
	
	return 0;
}
