#include <string>
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
	std::string GetFullName(int year) {
		std::string first, last;
		for (const auto &p : data) {
			if (p.first > year)
				break;
			first = !p.second.first.empty() ? p.second.first : first;
			last = !p.second.second.empty() ? p.second.second : last;
		}
		if (first.empty() && last.empty())
			return "Incognito";
		if (!first.empty() && last.empty())
			return first + " with unknown last name";
		if (first.empty() && !last.empty())
			return last + " with unknown first name";
		return first + " " + last;
	}
private:
	std::map<int, std::pair<std::string, std::string>> data;
};

int main()
{
	Person person;
	
	person.ChangeFirstName(1965, "Polina");
	person.ChangeLastName(1967, "Sergeeva");
	for (int year : {1900, 1965, 1990}) {
		std::cout << person.GetFullName(year) << std::endl;
	}
	
	person.ChangeFirstName(1970, "Appolinaria");
	for (int year : {1969, 1970}) {
		std::cout << person.GetFullName(year) << std::endl;
	}
	
	person.ChangeLastName(1968, "Volkova");
	for (int year : {1969, 1970}) {
		std::cout << person.GetFullName(year) << std::endl;
	}
	
	return 0;
}
