#include <iostream>
#include <string>
#include <vector>
#include <cmath>

bool IsPalindrom(const std::string &s) {
	int sz = s.size();
	for (int i = 0; i < floor(sz / 2); ++i)
		if (s[i] != s[sz - i - 1])
			return false;
	return true;
}

std::vector<std::string> PalindromFilter(
	const std::vector<std::string> &w,
	const int min_len
) {
	std::vector<std::string> res;
	for (int i = 0; i < w.size(); ++i)
		if (w[i].size() >= min_len && IsPalindrom(w[i]))
			res.push_back(w[i]);
	return res;
}

int main()
{
	std::vector<std::string> a = PalindromFilter({"abacaba", "aba"}, 5);
	std::vector<std::string> b = PalindromFilter({"abacaba", "aba"}, 2);
	std::vector<std::string> c = PalindromFilter({"weew", "bro", "code"}, 4);
	
	return 0;
}
