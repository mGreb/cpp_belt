//
// Created by mgreb on 01.10.2021.
//

#include "bus_manager.h"

void BusManager::AddBus(const std::string& bus, const std::vector<std::string>& stops) {
	buses_to_stops[bus] = stops;
	for (const std::string& stop : stops)
		stops_to_buses[stop].push_back(bus);
}

BusesForStopResponse BusManager::GetBusesForStop(const std::string& stop) const {
	BusesForStopResponse response;
	if (stops_to_buses.count(stop) != 0)
		for (const std::string& bus : stops_to_buses.at(stop))
			response.data.push_back(bus);
	return response;
}

StopsForBusResponse BusManager::GetStopsForBus(const std::string& bus) const {
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

AllBusesResponse BusManager::GetAllBuses() const {
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
