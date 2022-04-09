#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <cctype>

int main()
{
	int n = 0;
	std::cin >> n;
	std::vector<std::string> v(n);
	
	for (int i = 0; i < n; ++i)
		std::cin >> v[i];
	
	std::sort(v.begin(), v.end(), 
		   [] (std::string l, std::string r) {
		std::transform(l.begin(), l.end(), l.begin(), tolower);
		std::transform(r.begin(), r.end(), r.begin(), tolower);
		return l < r;
	});
	
	for (int i = 0; i < n; ++i)
		std::cout << v[i] << " ";
	
	return 0;
}
