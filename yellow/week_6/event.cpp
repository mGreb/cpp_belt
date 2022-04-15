#include "event.h"

// user includes
#include "test_runner.h"
// system includes
#include <vector>


std::string ParseEvent(std::istream& is)
{
	std::string s;
	bool first_non_space_reached = false;
	while (!is.eof()) {
		const char c = is.get();
		if (c != ' ')
			first_non_space_reached = true;
		if (c == '\n')
			return s;
		if (first_non_space_reached && c > 0)
			s.push_back(c);
	}
	return s;
}


void TestParseEvent()
{
	{
		std::istringstream is("event");
		AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
	}
	{
		std::istringstream is(" ");
		AssertEqual(ParseEvent(is), "", "String of space");
	}
	{
		std::istringstream is("   sport event ");
		AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
	}
	{
		std::istringstream is("  first event  \n  second event");
		std::vector<std::string> events;
		events.push_back(ParseEvent(is));
		events.push_back(ParseEvent(is));
		AssertEqual(events, std::vector<std::string>{"first event  ", "second event"}, "Parse multiple events");
	}
}
