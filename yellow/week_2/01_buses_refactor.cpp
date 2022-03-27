#include <iostream>
#include <string>
#include <map>
#include <vector>

enum class QueryType {
	NewBus,
	BusesForStop,
	StopsForBus,
	AllBuses
};

struct Query {
	QueryType type;
	std::string bus;
	std::string stop;
	std::vector<std::string> stops;
};

std::istream& operator >> (std::istream& is, Query& q) {
	std::string operation_code;
	is >> operation_code;
	
	if (operation_code == "NEW_BUS") {
		q.type = QueryType::NewBus;
		is >> q.bus;
		int stop_count;
		is >> stop_count;
		q.stops.resize(stop_count);
		for (std::string& stop : q.stops)
			is >> stop;
	}
	
	if (operation_code == "BUSES_FOR_STOP") {
		q.type = QueryType::BusesForStop;
		is >> q.stop;
	}
	
	if (operation_code == "STOPS_FOR_BUS") {
		q.type = QueryType::StopsForBus;
		is >> q.bus;
	}
	
	if (operation_code == "ALL_BUSES") {
		q.type = QueryType::AllBuses;
	}
	
	return is;
}

struct BusesForStopResponse {
	std::vector<std::string> data;
};

std::ostream& operator << (std::ostream& os, const BusesForStopResponse& r) {
	if (r.data.empty())
		os << "No stop";
	else {
		for (int i = 0; i < r.data.size() - 1; ++i)
			os << r.data[i] << " " ;
		os << r.data.back();
	}
	return os;
}

struct StopsForBusResponse {
	std::vector<std::string> data;
};

std::ostream& operator << (std::ostream& os, const StopsForBusResponse& r) {
	for (int i = 0; i < r.data.size() - 1; ++i)
		os << r.data[i] << std::endl;
	os << r.data.back();
	return os;
}

struct AllBusesResponse {
	std::vector<std::string> data;
};

std::ostream& operator << (std::ostream& os, const AllBusesResponse& r) {
	if (r.data.empty())
		os << "No buses";
	else {
		for (int i = 0; i < r.data.size() - 1; ++i)
			os << r.data[i] << std::endl;
		os << r.data.back();
	}
	return os;
}

class BusManager {
	std::map<std::string, std::vector<std::string>> buses_to_stops, stops_to_buses;
public:
	void AddBus(const std::string& bus, const std::vector<std::string>& stops) {
		buses_to_stops[bus] = stops;
		for (const std::string& stop : stops)
			stops_to_buses[stop].push_back(bus);
	}
	
	[[nodiscard]] BusesForStopResponse GetBusesForStop(const std::string& stop) const {
		BusesForStopResponse response;
		if (stops_to_buses.count(stop) != 0)
			for (const std::string& bus : stops_to_buses.at(stop))
				response.data.push_back(bus);
		return response;
	}
	
	[[nodiscard]] StopsForBusResponse GetStopsForBus(const std::string& bus) const {
		StopsForBusResponse response;
		
		if (buses_to_stops.count(bus) == 0)
			response.data.emplace_back("No bus");
		else {
			for (const std::string& stop : buses_to_stops.at(bus)) {
				std::string b = "Stop " + stop + ": ";
				
				if (stops_to_buses.at(stop).size() == 1)
					b.append("no interchange");
				else
					for (const std::string& other_bus : stops_to_buses.at(stop))
						if (bus != other_bus)
							b.append(other_bus + " ");
				
				response.data.push_back(b);
			}
		}
		
		return response;
	}
	
	[[nodiscard]] AllBusesResponse GetAllBuses() const {
		AllBusesResponse response;
		if (!buses_to_stops.empty()) {
			for (const auto& bus_item : buses_to_stops) {
				
				std::string b = {"Bus " + bus_item.first + ": "};
				
				for (const std::string& stop : bus_item.second)
					b.append(stop + " ");
				
				response.data.push_back(b);
			}
		}
		return response;
	}
};

// Не меняя тела функции main, реализуйте функции и классы выше

/* IN:
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
*/

/* OUT:
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

int main() {
	int query_count;
	Query q;
	
	std::cin >> query_count;
	
	BusManager bm;
	for (int i = 0; i < query_count; ++i) {
		std::cin >> q;
		switch (q.type) {
			case QueryType::NewBus:
				bm.AddBus(q.bus, q.stops);
				break;
			case QueryType::BusesForStop:
				std::cout << bm.GetBusesForStop(q.stop) << std::endl;
				break;
			case QueryType::StopsForBus:
				std::cout << bm.GetStopsForBus(q.bus) << std::endl;
				break;
			case QueryType::AllBuses:
				std::cout << bm.GetAllBuses() << std::endl;
				break;
		}
	}
	
	return 0;
}
