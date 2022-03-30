#include "phone_number.h"

#include <sstream>

PhoneNumber::PhoneNumber(const std::string &international_number) {
	/*size_t pos = 0;
	if (international_number[pos] != '+')
		throw std::invalid_argument("no + at start");
	++pos;
	
	for (; pos < international_number.size(); pos++) {
		if (international_number[pos] == '-') {
			++pos;
			break;
		}
		country_code_.push_back(international_number[pos]);
	}
	
	if (pos == international_number.size() - 1)
		throw std::invalid_argument("bad country_code");
	
	for (; pos < international_number.size(); pos++) {
		if (international_number[pos] == '-') {
			++pos;
			break;
		}
		city_code_.push_back(international_number[pos]);
	}
	
	if (pos == international_number.size() - 1)
		throw std::invalid_argument("bad city_code");
	
	for (; pos < international_number.size(); pos++) {
		local_number_.push_back(international_number[pos]);
	}
	
	if (local_number_.empty())
		throw std::invalid_argument("bad local_number");*/
	
	std::istringstream is(international_number);

	char sign = is.get();
	getline(is, country_code_, '-');
	getline(is, city_code_, '-');
	getline(is, local_number_);

	if (sign != '+' || country_code_.empty() || city_code_.empty() || local_number_.empty()) {
		throw std::invalid_argument("Phone number must begin with '+' symbol and contain 3 parts separated by '-' symbol: " + international_number);
	}
}

std::string PhoneNumber::GetCountryCode() const {
	return country_code_;
}
std::string PhoneNumber::GetCityCode() const {
	return city_code_;
}
std::string PhoneNumber::GetLocalNumber() const {
	return local_number_;
}
std::string PhoneNumber::GetInternationalNumber() const {
	return "+" + GetCountryCode() + "-" + GetCityCode() + "-" + GetLocalNumber();
}
