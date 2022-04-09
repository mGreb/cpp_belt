#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <utility>

class Person {
public:
	void ChangeFirstName(int year, const std::string &first_name) {
		data[year].first = first_name;
	}
	void ChangeLastName(int year, const std::string &last_name) {
		data[year].second = last_name;
	}
	[[nodiscard]] std::string GetFullName(int year) const {
		const auto &n = GetCurrentName(year);
		return FormatName(n);
	}
	std::string GetFullNameWithHistory(int year) {
		std::vector<std::string> firsts = {""}, lasts = {""};
		for (const auto &d : data) {
			if (d.first > year)
				break;
			if (!d.second.first.empty() && d.second.first != firsts.back())
				firsts.emplace_back(d.second.first);
			if (!d.second.second.empty() && d.second.second != lasts.back())
				lasts.emplace_back(d.second.second);
		}
		std::pair<std::string, std::string> name = {firsts.back(), lasts.back()};
		if (firsts.size() > 2) {
			name.first += " (";
			for (int i = firsts.size() - 2; i > 1; --i)
				name.first += firsts[i] + ", ";
			name.first += firsts[1] + ")";
		}
		if (lasts.size() > 2) {
			name.second += " (";
			for (int i = lasts.size() - 2; i > 1; --i)
				name.second += lasts[i] + ", ";
			name.second += lasts[1] + ")";
		}
		return FormatName(name);
	}
private:
	std::map<int, std::pair<std::string, std::string>, std::less<>> data;
	
	[[nodiscard]] std::pair<std::string, std::string> GetCurrentName(int year) const {
		std::string first, last;
		for (const auto &p : data) {
			if (p.first > year)
				break;
			first = !p.second.first.empty() ? p.second.first : first;
			last = !p.second.second.empty() ? p.second.second : last;
		}
		return {first, last};
	}
	
	static std::string FormatName(const std::pair<std::string, std::string> &n) {
		if (n.first.empty() && n.second.empty())
			return "Incognito";
		if (!n.first.empty() && n.second.empty())
			return n.first + " with unknown last name";
		if (n.first.empty() && !n.second.empty())
			return n.second + " with unknown first name";
		return n.first + " " + n.second;
	}
};

int main()
{
	Person person;
	
	person.ChangeFirstName(1965, "Polina");
	person.ChangeLastName(1967, "Sergeeva");
	for (int year : {1900, 1965, 1990}) {
		std::cout << person.GetFullNameWithHistory(year) << std::endl;
	}
	
	person.ChangeFirstName(1970, "Appolinaria");
	for (int year : {1969, 1970}) {
		std::cout << person.GetFullNameWithHistory(year) << std::endl;
	}
	
	person.ChangeLastName(1968, "Volkova");
	for (int year : {1969, 1970}) {
		std::cout << person.GetFullNameWithHistory(year) << std::endl;
	}
	
	person.ChangeFirstName(1990, "Polina");
	person.ChangeLastName(1990, "Volkova-Sergeeva");
	std::cout << person.GetFullNameWithHistory(1990) << std::endl;
	
	person.ChangeFirstName(1966, "Pauline");
	std::cout << person.GetFullNameWithHistory(1966) << std::endl;
	
	person.ChangeLastName(1960, "Sergeeva");
	for (int year : {1960, 1967}) {
		std::cout << person.GetFullNameWithHistory(year) << std::endl;
	}
	
	person.ChangeLastName(1961, "Ivanova");
	std::cout << person.GetFullNameWithHistory(1967) << std::endl;
	
	return 0;
}
