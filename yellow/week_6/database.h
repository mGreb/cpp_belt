#pragma once

// user includes
#include "date.h"
#include "db_container.h"
// system includes
#include <string>
#include <map>
#include <set>

class Database {
public:
	
	void Add(const Date& date, const std::string& event);
	
	void Print(std::ostream& stream) const;
	
	[[nodiscard]] std::string Last(const Date &date) const;
	
	template <class Predicate>
	int RemoveIf(Predicate pred)
	{
		return storage.erase_if(pred);
	}
	
	template <class Predicate>
	std::vector<std::string> FindIf(Predicate pred) const
	{
		std::vector<std::string> res;
		
		auto map_it = storage.begin();
		while (map_it != storage.end())
		{
			const Date &date = map_it->first;
			const auto &events = map_it->second;
			for (const auto &event : events)
				if (pred(date, event))
				{
					std::ostringstream os;
					os << date << " " << event;
					res.emplace_back(os.str());
				}
			++map_it;
		}
		
		return res;
	}
	
private:
	DbContainer storage;
};
