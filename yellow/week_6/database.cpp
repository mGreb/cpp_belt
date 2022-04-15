#include "database.h"


void Database::Add(const Date& date, const std::string& event) {
	storage.add(date, event);
}


void Database::Print(std::ostream& stream) const {
	for (const auto& item : storage) {
		for (const std::string& event : item.second) {
			stream << item.first << " " << event << std::endl;
		}
	}
}


std::string Database::Last(const Date &date) const
{
	auto map_it = storage.upper_bound(date);
	if (map_it == storage.begin())
		if (date != map_it->first)
			throw std::invalid_argument("");
	--map_it;
	std::ostringstream os;
	os << map_it->first << " " << map_it->second.back();
	return os.str();
}
