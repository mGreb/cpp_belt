#include "test_runner.h"

#include <ostream>

struct Time
{
	int hours = 0;
	int minutes = 0;
};

std::ostream& operator<<(std::ostream &os, const Time &time)
{
	os << time.hours << ":" << time.minutes;
	return os;
}

int foo (int x, int y)
{
	return x + y;
}

#define PRINT_VALUES(out, x, y) out << (x) << "\n" << (y) << "\n"

int main()
{
	TestRunner tr;
	tr.RunTest([] {
		std::ostringstream output;
		PRINT_VALUES(output, 5, "red belt");
		ASSERT_EQUAL(output.str(), "5\nred belt\n");
		}, "PRINT_VALUES usage example");
	tr.RunTest([] {
		std::ostringstream output;
		PRINT_VALUES(output, 5 + 10, 10);
		ASSERT_EQUAL(output.str(), "15\n10\n");
	}, "int add example");
	tr.RunTest([] {
		std::ostringstream output;
		Time t = {10, 11};
		PRINT_VALUES(output, t, 10);
		ASSERT_EQUAL(output.str(), "10:11\n10\n");
	}, "date add example");
	tr.RunTest([] {
		std::ostringstream output;
		PRINT_VALUES(output, foo(2, 3), foo(2,3) + 14);
		ASSERT_EQUAL(output.str(), "5\n19\n");
	}, "function add example");
	
	return 0;
}
