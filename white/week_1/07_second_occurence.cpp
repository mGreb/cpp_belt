#include <iostream>

int main()
{
	std::string a;
	std::cin >> a;
	
	bool f_found = false;
	int index = -1;
	
	for (int i = 0; i < a.size(); ++i) {
		
		if (a[i] == 'f' && !f_found) {
			f_found = true;
			continue;
		}
		
		if (a[i] == 'f' && f_found) {
			index = i;
			break;
		}
	}
	
	if (!f_found) {
		std::cout << -2;
		return 0;
	}
	
	if (index == -1) {
		std::cout << -1;
		return 0;
	}
	
	std::cout << index;
	
	return 0;
}
