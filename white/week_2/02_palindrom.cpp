#include <iostream>
#include <string>
#include <cmath>

bool IsPalindrom(const std::string &s) {
	int sz = s.size();
	for (int i = 0; i < floor(sz / 2); ++i)
		if (s[i] != s[sz - i - 1])
			return false;
	return true;
}

int main()
{
	bool a = IsPalindrom("madam");
	bool b = IsPalindrom("gentleman");
	bool c = IsPalindrom("X");
	
	return 0;
}
