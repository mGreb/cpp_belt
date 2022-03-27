#include <iostream>
#include <string>
#include <map>
#include <vector>

// comment out before sending!
enum class Lang {
	DE, FR, IT
};

// comment out before sending!
struct Region {
	std::string std_name;
	std::string parent_std_name;
	std::map<Lang, std::string> names;
	int64_t population;
};

typedef std::tuple<std::string, std::string, std::map<Lang, std::string>, int64_t> RegionTuple;

RegionTuple CalcID(const Region &r) {
	return std::make_tuple(r.std_name, r.parent_std_name, r.names, r.population);
}

int FindMaxRepetitionCount(const std::vector<Region>& regions) {
	if (regions.empty())
		return 0;
	
	std::map<RegionTuple, int> m;
	for (const auto &r : regions) {
		const auto id = CalcID(r);
		if (m.count(id) == 0)
			m[id] = 1;
		else
			++m.at(id);
	}
	
	int max_rep_count = 0;
	for (const auto &[_, value] : m)
		max_rep_count = std::max(max_rep_count, value);
	return max_rep_count;
}

int main() {
	std::cout << FindMaxRepetitionCount({
		                               {
			                               "Moscow",
			                               "Russia",
			                               {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
			                               89
		                               }, {
			                               "Russia",
			                               "Eurasia",
			                               {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
			                               89
		                               }, {
			                               "Moscow",
			                               "Russia",
			                               {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
			                               89
		                               }, {
			                               "Moscow",
			                               "Russia",
			                               {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
			                               89
		                               }, {
			                               "Russia",
			                               "Eurasia",
			                               {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
			                               89
		                               },
	                               }) << std::endl;
	
	std::cout << FindMaxRepetitionCount({
		                               {
			                               "Moscow",
			                               "Russia",
			                               {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
			                               89
		                               }, {
			                               "Russia",
			                               "Eurasia",
			                               {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
			                               89
		                               }, {
			                               "Moscow",
			                               "Russia",
			                               {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}},
			                               89
		                               }, {
			                               "Moscow",
			                               "Toulouse",
			                               {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
			                               89
		                               }, {
			                               "Moscow",
			                               "Russia",
			                               {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
			                               31
		                               },
	                               }) << std::endl;
	
	return 0;
}
