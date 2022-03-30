//
// Created by mgreb on 01.10.2021.
//

#ifndef YELLOW_RESPONSES_H
#define YELLOW_RESPONSES_H

#include <string>
#include <vector>
#include <iostream>

struct BusesForStopResponse {
	std::vector<std::string> data;
};

std::ostream& operator << (std::ostream& os, const BusesForStopResponse& r);

struct StopsForBusResponse {
	std::vector<std::string> data;
};

std::ostream& operator << (std::ostream& os, const StopsForBusResponse& r);

struct AllBusesResponse {
	std::vector<std::string> data;
};

std::ostream& operator << (std::ostream& os, const AllBusesResponse& r);

#endif //YELLOW_RESPONSES_H
