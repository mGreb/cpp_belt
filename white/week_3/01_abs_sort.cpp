#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>

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
	std::vector<double> v(n);
	
	for (int i = 0; i < n; ++i)
		std::cin >> v[i];
	
	std::sort(v.begin(), v.end(), [](double x, double y) {return fabs(x) < fabs(y);});
	
	for (int i = 0; i < n; ++i)
		std::cout << v[i] << " ";
	
	return 0;
}
