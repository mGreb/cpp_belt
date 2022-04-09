#include <string>
#include <map>
#include <iostream>

std::map<char, int> fill_letters_count(const std::string &s) {
	std::map<char, int> m;
	
	// если буква встретилась - создает запись и увеличивает её значение на 1
	for(const auto &c : s)
		++m[c];
	
	return m;
}

bool check_if_anagram(const std::string &w1, const std::string &w2) {
	// если два словаря равны - слова анаграммы
	return fill_letters_count(w1) == fill_letters_count(w2);
}

int main()
{
	int n;
	std::cin >> n;
	
	for (int i = 0; i < n; ++i) {
		std::string w1; std::cin >> w1;
		std::string w2; std::cin >> w2;
		
		bool is_anagram = check_if_anagram(w1, w2);
		if (is_anagram)
			std::cout << "YES" << std::endl;
		else
			std::cout << "NO" << std::endl;
	}
	
	return 0;
}
