//
// Created by mgreb on 01.10.2021.
//

#ifndef YELLOW_QUERY_H
#define YELLOW_QUERY_H

#include <vector>
#include <string>

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

std::istream& operator >> (std::istream& is, Query& q);

#endif //YELLOW_QUERY_H
