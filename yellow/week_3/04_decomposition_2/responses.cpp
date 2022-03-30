//
// Created by mgreb on 01.10.2021.
//

#include "responses.h"

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

std::ostream& operator << (std::ostream& os, const StopsForBusResponse& r) {
	for (int i = 0; i < r.data.size() - 1; ++i)
		os << r.data[i] << std::endl;
	os << r.data.back();
	return os;
}

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
