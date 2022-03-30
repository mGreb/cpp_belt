#include "phone_number.h"
#include "test_runner.h"

#include <cassert>

void test1 () {
	PhoneNumber n("+7-495-111-22-33");
	assert(n.GetCountryCode() == "7");
	assert(n.GetCityCode() == "495");
	assert(n.GetLocalNumber() == "111-22-33");
	assert(n.GetInternationalNumber() == "+7-495-111-22-33");
}

void test2 () {
	PhoneNumber n("+7-495-1112233");
	assert(n.GetCountryCode() == "7");
	assert(n.GetCityCode() == "495");
	assert(n.GetLocalNumber() == "1112233");
	assert(n.GetInternationalNumber() == "+7-495-1112233");
}

void test3 () {
	PhoneNumber n("+323-22-460002");
	assert(n.GetCountryCode() == "323");
	assert(n.GetCityCode() == "22");
	assert(n.GetLocalNumber() == "460002");
	assert(n.GetInternationalNumber() == "+323-22-460002");
}

void test4 () {
	PhoneNumber n("+1-2-coursera-cpp");
	assert(n.GetCountryCode() == "1");
	assert(n.GetCityCode() == "2");
	assert(n.GetLocalNumber() == "coursera-cpp");
	assert(n.GetInternationalNumber() == "+1-2-coursera-cpp");
}

void test5 () {
	PhoneNumber n("1-2-333");
}

void test6 () {
	PhoneNumber n("+7-1233");
}

int main () {
	TestRunner r;
	r.RunTest(test1, "1");
	r.RunTest(test2, "2");
	r.RunTest(test3, "3");
	r.RunTest(test4, "4");
	r.RunTest(test5, "5");
	r.RunTest(test6, "6");
	
	return 0;
}
