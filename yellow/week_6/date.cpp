#include "date.h"

// user includes
#include "comparison.h"
#include "test_runner.h"
// system includes
#include <sstream>
#include <stdexcept>

Date::Date(int new_year, int new_month, int new_day) {
	data[0] = new_year;
	
	if (new_month > 12 || new_month < 1) {
		throw std::logic_error("Month value is invalid: " + std::to_string(new_month));
	}
	data[1] = new_month;
	
	if (new_day > 31 || new_day < 1) {
		throw std::logic_error("Day value is invalid: " + std::to_string(new_day));
	}
	data[2] = new_day;
}


bool operator<(const Date& lhs, const Date& rhs) {
	return lhs.data < rhs.data;
}


bool operator<=(const Date& lhs, const Date& rhs) {
	return lhs.data <= rhs.data;
}


bool operator>(const Date& lhs, const Date& rhs) {
	return lhs.data > rhs.data;
}


bool operator>=(const Date& lhs, const Date& rhs) {
	return lhs.data >= rhs.data;
}


bool operator==(const Date& lhs, const Date& rhs) {
	return lhs.data == rhs.data;
}


bool operator!=(const Date& lhs, const Date& rhs) {
	return lhs.data != rhs.data;
}


std::ostream& operator<<(std::ostream& stream, const Date& date) {
	stream << std::setw(4) << std::setfill('0') << date.GetYear() <<
		   "-" << std::setw(2) << std::setfill('0') << date.GetMonth() <<
		   "-" << std::setw(2) << std::setfill('0') << date.GetDay();
	return stream;
}


Date ParseDate(std::istream &date_stream)
{
	int year = 0;
	date_stream >> year;
	date_stream.ignore(1);  // ignore '-'
	
	int month = 0;
	date_stream >> month;
	date_stream.ignore(1);
	
	int day = 0;
	date_stream >> day;
	
	return Date(year, month, day);
}


void TestCompareDate()
{
	{
		Date d1(2017, 1, 1), d2(2018, 1, 1);
		AssertEqual(d1 < d2, true, "date compare 1");
	}
	{
		Date d1(2017, 1, 1), d2(2017, 1, 1);
		AssertEqual(d1 == d2, true, "date compare 2");
	}
	{
		Date d1(2017, 1, 1), d2(2017, 1, 1);
		AssertEqual(d1 <= d2, true, "date compare 3");
	}
	{
		Date d1(2016, 8, 11), d2(2017, 1, 1);
		AssertEqual(d1 <= d2, true, "date compare 4");
	}
	{
		Date d1(2017, 1, 1), d2(2017, 1, 1);
		AssertEqual(d1 >= d2, true, "date compare 5");
	}
	{
		Date d1(2017, 1, 1), d11(2017, 1, 1), d2(2017, 7, 1);
		AssertEqual(d1 >= d11, true, "date compare 6");
		AssertEqual(d1 < d2, true, "date compare 6");
	}
}
