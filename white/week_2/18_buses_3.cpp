#include <string>
#include <map>
#include <set>
#include <vector>
#include <iostream>

std::map<std::set<std::string>, int> buses;

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

/*
5
2 Marushkino Kokoshkino
1 Kokoshkino
2 Marushkino Kokoshkino
2 Kokoshkino Marushkino
2 Kokoshkino Kokoshkino

New bus 1
New bus 2
Already exists for 1
Already exists for 1
Already exists for 2
*/

int main()
{
	int n = 0;
	std::cin >> n;
	
	int bus_num = 0;
	
	for (int i = 0; i < n; ++i) {
		int stops_num = get_int();
		std::set<std::string> stops;
		for (int j = 0; j < stops_num; ++j)
			stops.insert(get_string());
		
		if (buses.find(stops) == buses.end()) {
			++bus_num;
			buses[stops] = bus_num;
			std::cout << "New bus " << bus_num << std::endl;
		} else
			std::cout << "Already exists for " << buses[stops] << std::endl;
	}
	
	return 0;
}
