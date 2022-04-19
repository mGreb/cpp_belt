#include "airline_ticket.h"
#include "test_runner.h"


#define UPDATE_FIELD(ticket, field, values) {  \
	auto it = values.find(#field);             \
	if (it != values.end())                    \
	{                                          \
		std::istringstream is(it->second);     \
		is >> ticket.field;                    \
	}                                          \
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

std::ostream& operator<<(std::ostream &os, const Time &time)
{
	os << time.hours << ":" << time.minutes;
	return os;
}

std::istream& operator>>(std::istream &os, Time &time)
{
	os >> time.hours;
	os.ignore(1);
	os >> time.minutes;
	return os;
}

std::istream& operator>>(std::istream &os, Date &date)
{
	os >> date.year;
	os.ignore(1);
	os >> date.month;
	os.ignore(1);
	os >> date.day;
	return os;
}

bool operator==(const Time &left, const Time &right)
{
	return std::array<int, 2>{left.hours, left.minutes} ==
		   std::array<int, 2>{right.hours, right.minutes};
}

void TestUpdate() {
  AirlineTicket t;
  t.price = 0;

  const std::map<std::string, std::string> updates1 = {
    {"departure_date", "2018-2-28"},
    {"departure_time", "17:40"},
  };
  UPDATE_FIELD(t, departure_date, updates1);
  UPDATE_FIELD(t, departure_time, updates1);
  UPDATE_FIELD(t, price, updates1);

  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
  ASSERT_EQUAL(t.price, 0);

  const std::map<std::string, std::string> updates2 = {
    {"price", "12550"},
    {"arrival_time", "20:33"},
  };
  UPDATE_FIELD(t, departure_date, updates2);
  UPDATE_FIELD(t, departure_time, updates2);
  UPDATE_FIELD(t, arrival_time, updates2);
  UPDATE_FIELD(t, price, updates2);

  // updates2 не содержит ключей "departure_date" и "departure_time", поэтому
  // значения этих полей не должны измениться
  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
  ASSERT_EQUAL(t.price, 12550);
  ASSERT_EQUAL(t.arrival_time, (Time{20, 33}));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestUpdate);
}
