#include <string>
#include <vector>
#include <map>
#include <iostream>

class SortedStrings {
public:
	void AddString(const std::string &s) {
		++data[s];
	}
	std::vector<std::string> GetSortedStrings() {
		std::vector<std::string> res;
		for (const auto &d : data)
			for (int i = 0; i < d.second; ++i)
				res.emplace_back(d.first);
		return res;
	}
private:
	std::map<std::string, int> data;
};

void PrintSortedStrings(SortedStrings& strings) {
	for (const std::string& s : strings.GetSortedStrings()) {
		std::cout << s << " ";
	}
	std::cout << std::endl;
}

int main() {
	SortedStrings strings;
	
	strings.AddString("first");
	strings.AddString("third");
	strings.AddString("second");
	PrintSortedStrings(strings);
	
	strings.AddString("second");
	PrintSortedStrings(strings);
	
	return 0;
}
