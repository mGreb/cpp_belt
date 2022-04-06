#include <algorithm>
#include <numeric>
#include <vector>
#include <iostream>

std::ostream& operator <<(std::ostream &o, const std::vector<int> &v) {
	for (const auto &e : v)
		o << e << " ";
	
	return o;
}

int main() {
	int n;
	std::cin >> n;
	std::vector<int> nums(n);
	
	std::iota(nums.rbegin(), nums.rend(), 1);
	
	do {
		std::cout << nums << '\n';
	} while(std::prev_permutation(nums.begin(), nums.end()));
	
	return 0;
}
