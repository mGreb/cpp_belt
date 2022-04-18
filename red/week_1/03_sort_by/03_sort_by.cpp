#include "airline_ticket.h"
#include "test_runner.h"

#include <algorithm>
#include <numeric>

bool operator<(const Date &left, const Date &right)
{
	return std::array<int, 3>{left.year, left.month, left.day} <
		   std::array<int, 3>{right.year, right.month, right.day};
}

bool operator==(const Date &left, const Date &right)
{
	return std::array<int, 3>{left.year, left.month, left.day} ==
		   std::array<int, 3>{right.year, right.month, right.day};
}

std::ostream& operator<<(std::ostream &os, const Date &date)
{
	os << date.year << "." << date.month << "." << date.day;
	return os;
}

bool operator<(const Time &left, const Time &right)
{
	return std::array<int, 2>{left.hours, left.minutes} <
		   std::array<int, 2>{right.hours, right.minutes};
}

#define SORT_BY(field)                                       \
	[](const AirlineTicket& lhs, const AirlineTicket& rhs) { \
		return lhs.field < rhs.field;                        \
	}


void SortTickets(std::vector<AirlineTicket>& tixs) {
	stable_sort(begin(tixs), end(tixs), [](const AirlineTicket& lhs, const AirlineTicket& rhs) {
		return lhs.to < rhs.to;
	});
	stable_sort(begin(tixs), end(tixs), [](const AirlineTicket& lhs, const AirlineTicket& rhs) {
		return lhs.departure_time < rhs.departure_time;
	});
	stable_sort(begin(tixs), end(tixs), [](const AirlineTicket& lhs, const AirlineTicket& rhs) {
		return lhs.price < rhs.price;
	});
}

template <typename Predicate>
void sort(std::vector<AirlineTicket>::iterator it1,
		  std::vector<AirlineTicket>::iterator it2, Predicate pred)
{
	stable_sort(it1, it2, pred);
}

void TestSortBy() {
  std::vector<AirlineTicket> tixs = {
    {"VKO", "AER", "Utair",     {2018, 2, 28}, {17, 40}, {2018, 2, 28}, {20,  0}, 1200},
    {"AER", "VKO", "Utair",     {2018, 3,  5}, {14, 15}, {2018, 3,  5}, {16, 30}, 1700},
    {"AER", "SVO", "Aeroflot",  {2018, 3,  5}, {18, 30}, {2018, 3,  5}, {20, 30}, 2300},
    {"PMI", "DME", "Iberia",    {2018, 2,  8}, {23, 00}, {2018, 2,  9}, { 3, 30}, 9000},
    {"CDG", "SVO", "AirFrance", {2018, 3,  1}, {13, 00}, {2018, 3,  1}, {17, 30}, 8000},
  };

  sort(begin(tixs), end(tixs), SORT_BY(price));
  ASSERT_EQUAL(tixs.front().price, 1200);
  ASSERT_EQUAL(tixs.back().price, 9000);

  sort(begin(tixs), end(tixs), SORT_BY(from));
  ASSERT_EQUAL(tixs.front().from, "AER");
  ASSERT_EQUAL(tixs.back().from, "VKO");

  sort(begin(tixs), end(tixs), SORT_BY(arrival_date));
  ASSERT_EQUAL(tixs.front().arrival_date, (Date{2018, 2, 9}));
  ASSERT_EQUAL(tixs.back().arrival_date, (Date{2018, 3, 5}));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSortBy);
}
