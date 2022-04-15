#pragma once

// system includes
#include <string>
#include <vector>
#include <iomanip>
#include <tuple>

class Date {
public:
	// конструктор выбрасывает исключение, если его аргументы некорректны
	Date(int new_year, int new_month, int new_day);
	
	[[nodiscard]] int GetYear()  const { return data[0]; }
	[[nodiscard]] int GetMonth() const { return data[1]; }
	[[nodiscard]] int GetDay()   const { return data[2]; }
	
	std::array<int, 3> data;
};

// определить сравнение для дат необходимо для использования их в качестве ключей словаря
bool operator<(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);
bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);

// даты будут по умолчанию выводиться в нужном формате
std::ostream& operator<<(std::ostream& stream, const Date& date);

Date ParseDate(std::istream& date_stream);


void TestCompareDate();