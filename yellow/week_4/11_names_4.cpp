#include <string>
#include <iostream>
#include <map>
#include <utility>

class Person {
public:
	void ChangeFirstName(int year, const std::string &first_name) {
		first_names[year] = first_name;
	}
	void ChangeLastName(int year, const std::string &last_name) {
		last_names[year] = last_name;
	}
	static std::string FindNameByYear(const std::map<int, std::string> &names, int year) {
		auto iter_after = names.upper_bound(year);
		std::string name;
		if (iter_after != names.begin())
			name = (--iter_after)->second;
		
		return name;
	}
	std::string GetFullName(int year) {
		std::string first = FindNameByYear(first_names, year);
		std::string last = FindNameByYear(last_names, year);
		
		if (first.empty() && last.empty())
			return "Incognito";
		if (!first.empty() && last.empty())
			return first + " with unknown last name";
		if (first.empty() && !last.empty())
			return last + " with unknown first name";
		return first + " " + last;
	}
private:
	std::map<int, std::string> first_names;
	std::map<int, std::string> last_names;
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
