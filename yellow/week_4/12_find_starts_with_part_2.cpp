#include <utility>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>

#include <memory>

template <typename RandomIt>
std::pair<RandomIt, RandomIt> FindStartsWith(
		RandomIt range_begin, RandomIt range_end, const std::string &prefix) {
	
	static constexpr auto lambda1 = [](const std::string &s1, const std::string &s2){
		for (int i = 0; i < s1.size(); ++i) {
			if (s1[i] < s2[i])
				return true;
			if (s1[i] > s2[i])
				return false;
		}
		return false;
	};
	
	std::string prefix1 = prefix;
	prefix1.back() -= 1;
	RandomIt it1 = std::upper_bound(range_begin, range_end, prefix1, lambda1);
	RandomIt it2 = std::upper_bound(range_begin, range_end, prefix, lambda1);
	
	return {it1, it2};
}

int main() {
	
	
	char str[] = "abcdef";
	char str2[] = "abc" "def";
	char *str1 = "abcdef";
	
	short* s = (short*)str;
	printf("%d", s+1);
	
	struct A {
		int &i;
		A(int i_):i(i_){}
	};
	
	int x = 0;
	std::shared_ptr<A> a = std::make_shared<A>(x);
	std::cout << a->i;
	
	const std::vector<std::string> sorted_strings = {"moscow", "motovilikha", "murmansk"};
	
	const auto mo_result =
			FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
	for (auto it = mo_result.first; it != mo_result.second; ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	
	const auto mt_result =
			FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
	std::cout << (mt_result.first - begin(sorted_strings)) << " " <<
		 (mt_result.second - begin(sorted_strings)) << std::endl;
	
	const auto na_result =
			FindStartsWith(begin(sorted_strings), sorted_strings.end(), "na");
	std::cout << (na_result.first - begin(sorted_strings)) << " " <<
		 (na_result.second - begin(sorted_strings)) << std::endl;
	
	return 0;
}
