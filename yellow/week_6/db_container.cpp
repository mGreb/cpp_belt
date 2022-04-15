#include "db_container.h"


std::vector<std::string>& DbContainer::operator[](const Date &d)
{
	return vec_map[d];
}


void DbContainer::add(const Date &date, const std::string &event)
{
	const bool date_exists = contains(vec_map, date);
	
	if (!date_exists)  // if no date exists
	{
		set_map[date].insert(event);
		vec_map[date].emplace_back(event);
	}
	else
	{
		if (!contains(set_map[date], event))  // and no event in date
		{
			set_map[date].insert(event);
			vec_map[date].emplace_back(event);
		}
	}
}
