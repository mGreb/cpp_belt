#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>

std::map<std::string, std::vector<std::string>> buses;
std::vector<std::string> buses_in_order;

void all_buses() {
	if (buses.empty())
		std::cout << "No buses" << std::endl;
	else {
		for (const auto &b : buses) {
			std::cout << "Bus " << b.first << ": ";
			for (const auto &s : b.second)
				std::cout << s << " ";
			std::cout << std::endl;
		}
	}
}

std::vector<std::string> buses_for_stop_calc(const std::string &stop) {
	std::vector<std::string> buses_for_stop;
	for (const auto &b : buses_in_order) {
		const auto &it = std::find(buses[b].begin(), buses[b].end(), stop);
		if (it != buses[b].end())
			buses_for_stop.emplace_back(b);
	}
	
	return buses_for_stop;
}

void buses_for_stop(const std::string &stop) {
	const std::vector<std::string> buses_for_stop = buses_for_stop_calc(stop);
	
	if (!buses_for_stop.empty())
		for (const auto &b : buses_for_stop)
			std::cout << b << " ";
	else
		std::cout << "No stop";
	std::cout << std::endl;
}

void stops_for_bus(const std::string &bus) {
	if (buses.find(bus) == buses.end()) {
		std::cout << "No bus" << std::endl;
		return;
	}
	
	const std::vector<std::string> &stops = buses[bus];
	for (const auto &stop : stops) {
		const auto &buses_for_stop = buses_for_stop_calc(stop);
		if (buses_for_stop.size() == 1)
			std::cout << "Stop " << stop << ": no interchange";
		else{
			std::cout << "Stop " << stop << ": ";
			for (const auto &b : buses_for_stop) {
				if (b != bus)
					std::cout << b << " ";
			}
		}
		std::cout << std::endl;
	}
}

void new_bus(const std::string &bus, const std::vector<std::string> &stops) {
	buses_in_order.push_back(bus);
	buses[bus] = stops;
}

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
10
ALL_BUSES
BUSES_FOR_STOP Marushkino
STOPS_FOR_BUS 32K
NEW_BUS 32 3 Tolstopaltsevo Marushkino Vnukovo
NEW_BUS 32K 6 Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo Skolkovo
BUSES_FOR_STOP Vnukovo
NEW_BUS 950 6 Kokoshkino Marushkino Vnukovo Peredelkino Solntsevo Troparyovo
NEW_BUS 272 4 Vnukovo Moskovsky Rumyantsevo Troparyovo
STOPS_FOR_BUS 272
ALL_BUSES

No buses
No stop
No bus
32 32K
Stop Vnukovo: 32 32K 950
Stop Moskovsky: no interchange
Stop Rumyantsevo: no interchange
Stop Troparyovo: 950
Bus 272: Vnukovo Moskovsky Rumyantsevo Troparyovo
Bus 32: Tolstopaltsevo Marushkino Vnukovo
Bus 32K: Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo Skolkovo
Bus 950: Kokoshkino Marushkino Vnukovo Peredelkino Solntsevo Troparyovo
*/

int main()
{
	int n = 0;
	std::cin >> n;
	
	for (int i = 0; i < n; ++i) {
		std::string command = get_string();
		
		if (command == "ALL_BUSES")
			all_buses();
		if (command == "STOPS_FOR_BUS") {
			std::string bus = get_string();
			stops_for_bus(bus);
		}
		if (command == "BUSES_FOR_STOP") {
			std::string stop = get_string();;
			buses_for_stop(stop);
		}
		if (command == "NEW_BUS") {
			std::string bus = get_string();
			int stop_count = get_int();
			std::vector<std::string> stops(stop_count);
			for (int j = 0; j < stop_count; ++j)
				stops[j] = get_string();
			new_bus(bus, stops);
		}
	}
	
	return 0;
}
