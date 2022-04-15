#pragma once

// user includes
#include "date.h"
// system includes
#include <map>
#include <set>
#include <algorithm>


class DbContainer {
public:
	std::vector<std::string>& operator[](const Date &date);
	
	void add(const Date &date, const std::string &event);
	
	template <class Predicate>
	int erase_if(Predicate pred)
	{
		auto map_iter = vec_map.begin();
		int removed_count = 0;
		while (map_iter != vec_map.end())  // go through all elements of map
		{
			const Date &date = map_iter->first;
			auto &events = map_iter->second;
			auto new_end = std::stable_partition(events.begin(), events.end(),
										[&pred, &date](const std::string &s){return !pred(date, s);});
			if (new_end != events.end())
			{
				removed_count += events.end() - new_end;
				events.resize(new_end - events.begin());
				
				if (events.empty())  // if no events left, delete date from both containers
				{
					set_map.erase(date);
					map_iter = vec_map.erase(map_iter);
				}
				else  // if some events left, populate set from scratch
				{
					set_map[date] = std::set(events.begin(), events.end());  // is this slow?
					++map_iter;
				}
			}
			else
			{
				++map_iter;
			}
		}
		
		return removed_count;
	}
	
	auto upper_bound(const Date &date) const
	{
		return vec_map.upper_bound(date);
	}
	
	
	auto begin() const
	{
		return vec_map.begin();
	}
	
	
	auto end() const
	{
		return vec_map.end();
	}
	
private:
	std::map<Date, std::vector<std::string>> vec_map;
	std::map<Date, std::set<std::string>> set_map;
	
	template <class T, class V>
	bool contains(const T &t, const V &d) const
	{
		return t.count(d) != 0;
	}
};
