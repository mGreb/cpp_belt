#include <string>
#include <map>
#include <iostream>

std::map<std::string, std::string> countries_capitals;

void dump() {
	if (countries_capitals.empty())
		printf("There are no countries in the world");
	for (const auto &a: countries_capitals)
		printf("%s/%s ", a.first.c_str(), a.second.c_str());
	std::cout << std::endl;
}

void about(const std::string &country) {
	if (countries_capitals.find(country) == countries_capitals.end())
		printf("Country %s doesn't exist\n", country.c_str());
	else
		printf("Country %s has capital %s\n", country.c_str(), countries_capitals[country].c_str());
}

void change_capital(const std::string &country, const std::string &capital) {
	const auto &it = countries_capitals.find(country);
	if (it == countries_capitals.end()) {
		countries_capitals[country] = capital;
		printf("Introduce new country %s with capital %s\n", country.c_str(), capital.c_str());
	} else {
		if (countries_capitals[country] == capital)
			printf("Country %s hasn't changed its capital\n", country.c_str());
		else {
			printf("Country %s has changed its capital from %s to %s\n",
			       country.c_str(), countries_capitals[country].c_str(), capital.c_str());
			countries_capitals[country] = capital;
		}
	}
}

void rename_country(const std::string &old_name, const std::string &new_name) {
	const auto &end = countries_capitals.end();
	const bool old_exists = countries_capitals.find(old_name) != end;
	const bool new_exists = countries_capitals.find(new_name) != end;
	
	if (!old_exists || new_exists || (old_exists && old_name == new_name)) {
		printf("Incorrect rename, skip\n");
		return;
	}
	
	if (old_exists) {
		printf("Country %s with capital %s has been renamed to %s\n",
		       old_name.c_str(), countries_capitals[old_name].c_str(), new_name.c_str());
		std::string old_capital = countries_capitals[old_name];
		countries_capitals[new_name] = old_capital;
		countries_capitals.erase(old_name);
	}
}

/*
6
CHANGE_CAPITAL RussianEmpire Petrograd
RENAME RussianEmpire RussianRepublic
ABOUT RussianRepublic
RENAME RussianRepublic USSR
CHANGE_CAPITAL USSR Moscow
DUMP
*/

/*
Introduce new country RussianEmpire with capital Petrograd
Country RussianEmpire with capital Petrograd has been renamed to RussianRepublic
Country RussianRepublic has capital Petrograd
Country RussianRepublic with capital Petrograd has been renamed to USSR
Country USSR has changed its capital from Petrograd to Moscow
USSR/Moscow
*/

/*
24
RENAME FakeCountry FarFarAway
ABOUT FarFarAway
DUMP
CHANGE_CAPITAL TsardomOfRussia Moscow
CHANGE_CAPITAL TsardomOfRussia Moscow
CHANGE_CAPITAL ColonialBrazil Salvador
CHANGE_CAPITAL TsardomOfRussia SaintPetersburg
RENAME TsardomOfRussia RussianEmpire
CHANGE_CAPITAL RussianEmpire Moscow
CHANGE_CAPITAL RussianEmpire SaintPetersburg
CHANGE_CAPITAL ColonialBrazil RioDeJaneiro
DUMP
RENAME ColonialBrazil EmpireOfBrazil
ABOUT RussianEmpire
RENAME EmpireOfBrazil UnitedStatesOfBrazil
CHANGE_CAPITAL RussianEmpire Petrograd
RENAME RussianEmpire RussianRepublic
RENAME RussianRepublic USSR
CHANGE_CAPITAL USSR Moscow
CHANGE_CAPITAL UnitedStatesOfBrazil Brasilia
RENAME UnitedStatesOfBrazil FederativeRepublicOfBrazil
ABOUT RussianEmpire
DUMP
RENAME USSR USSR
*/

/*
Incorrect rename, skip
Country FarFarAway doesn't exist
There are no countries in the world
Introduce new country TsardomOfRussia with capital Moscow
Country TsardomOfRussia hasn't changed its capital
Introduce new country ColonialBrazil with capital Salvador
Country TsardomOfRussia has changed its capital from Moscow to SaintPetersburg
Country TsardomOfRussia with capital SaintPetersburg has been renamed to RussianEmpire
Country RussianEmpire has changed its capital from SaintPetersburg to Moscow
Country RussianEmpire has changed its capital from Moscow to SaintPetersburg
Country ColonialBrazil has changed its capital from Salvador to RioDeJaneiro
ColonialBrazil/RioDeJaneiro RussianEmpire/SaintPetersburg
Country ColonialBrazil with capital RioDeJaneiro has been renamed to EmpireOfBrazil
Country RussianEmpire has capital SaintPetersburg
Country EmpireOfBrazil with capital RioDeJaneiro has been renamed to UnitedStatesOfBrazil
Country RussianEmpire has changed its capital from SaintPetersburg to Petrograd
Country RussianEmpire with capital Petrograd has been renamed to RussianRepublic
Country RussianRepublic with capital Petrograd has been renamed to USSR
Country USSR has changed its capital from Petrograd to Moscow
Country UnitedStatesOfBrazil has changed its capital from RioDeJaneiro to Brasilia
Country UnitedStatesOfBrazil with capital Brasilia has been renamed to FederativeRepublicOfBrazil
Country RussianEmpire doesn't exist
FederativeRepublicOfBrazil/Brasilia USSR/Moscow
Incorrect rename, skip
*/

int main()
{
	int n = 0;
	std::cin >> n;
	
	for (int i = 0; i < n; ++i) {
		std::string command;
		std::cin >> command;
		
		if (command == "DUMP")
			dump();
		
		if (command == "ABOUT") {
			std::string country; std::cin >> country;
			about(country);
		}
		
		if (command == "CHANGE_CAPITAL") {
			std::string country; std::cin >> country;
			std::string capital; std::cin >> capital;
			change_capital(country, capital);
		}
		
		if (command == "RENAME") {
			std::string old_name; std::cin >> old_name;
			std::string new_name; std::cin >> new_name;
			rename_country(old_name, new_name);
		}
	}
	
	return 0;
}
