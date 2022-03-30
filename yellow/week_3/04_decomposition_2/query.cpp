//
// Created by mgreb on 01.10.2021.
//

#include <iostream>

#include "query.h"

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
