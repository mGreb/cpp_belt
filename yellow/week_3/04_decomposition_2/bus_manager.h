//
// Created by mgreb on 01.10.2021.
//

#ifndef YELLOW_BUS_MANAGER_H
#define YELLOW_BUS_MANAGER_H

#include <string>
#include <vector>
#include <map>

#include "responses.h"

class BusManager {
	std::map<std::string, std::vector<std::string>> buses_to_stops, stops_to_buses;
public:
	void AddBus(const std::string& bus, const std::vector<std::string>& stops);

	BusesForStopResponse GetBusesForStop(const std::string& stop) const;

	StopsForBusResponse GetStopsForBus(const std::string& bus) const;

	AllBusesResponse GetAllBuses() const;
};

#endif //YELLOW_BUS_MANAGER_H
