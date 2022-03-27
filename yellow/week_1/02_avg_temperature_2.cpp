#include <iostream>
#include <vector>

int main() {
	int n = 0;
	std::cin >> n;
	std::vector<int> v(n);
	long int sum_v = 0;
	for (int i = 0; i < n; ++i) {
		int t = 0;
		std::cin >> t;
		sum_v += t;
		v[i] = t;
	}
	
	long int avg = sum_v / n;
	
	std::vector<int> days_above_avg;
	for (int i = 0; i < n; ++i)
		if (v[i] > avg)
			days_above_avg.push_back(i);
	
	std:: cout << days_above_avg.size() << std::endl;
	for (int i = 0; i < days_above_avg.size(); ++i)
		std::cout << days_above_avg[i] << " ";
	
	return 0;
}
