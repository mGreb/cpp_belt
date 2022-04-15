// user includes
#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "test_runner.h"
#include "db_tests.h"
#include "event.h"
// system includes
#include <iostream>
#include <stdexcept>
#include <string>


void TestAll()
{
	TestRunner tr;
	tr.RunTest(TestCompareDate, "TestCompareDate");
	tr.RunTest(TestParseEvent, "TestParseEvent");
	tr.RunTest(TestParseCondition, "TestParseCondition");
	
	tr.RunTest(TestAdd, "TestAdd");
	tr.RunTest(TestDel, "TestDel");
	tr.RunTest(TestPrint, "TestPrint");
	tr.RunTest(TestFind, "TestFind");
	tr.RunTest(TestLast, "TestLast");
	tr.RunTest(TestGeneral, "TestGeneral");
	tr.RunTest(TestEventComparisonNode, "TestEventComparisonNode");
	
	
	tr.RunTest(TestsMyCustom, "TestsMyCustom");
	tr.RunTest(TestDatabase, "TestDatabase");
}


int main()
{
	TestAll();
	return 0;
	
	Database db;
	
	for (std::string line; std::getline(std::cin, line); ) {
		std::istringstream is(line);
		
		std::string command;
		is >> command;
		if (command == "Add") {
			const auto date = ParseDate(is);
			const auto event = ParseEvent(is);
			db.Add(date, event);
		} else if (command == "Print") {
			db.Print(std::cout);
		} else if (command == "Del") {
			auto condition = ParseCondition(is);
			auto predicate = [condition](const Date& date, const std::string& event) {
				return condition->Evaluate(date, event);
			};
			const int count = db.RemoveIf(predicate);
			std::cout << "Removed " << count << " entries" << std::endl;
		} else if (command == "Find") {
			auto condition = ParseCondition(is);
			auto predicate = [condition](const Date& date, const std::string& event) {
				return condition->Evaluate(date, event);
			};
			const auto entries = db.FindIf(predicate);
			for (const auto& entry : entries) {
				std::cout << entry << std::endl;
			}
			std::cout << "Found " << entries.size() << " entries" << std::endl;
		} else if (command == "Last") {
			try {
				std::cout << db.Last(ParseDate(is)) << std::endl;
			} catch (std::invalid_argument&) {
				std::cout << "No entries" << std::endl;
			}
		} else if (command.empty()) {
			continue;
		} else {
			throw std::logic_error("Unknown command: " + command);
		}
	}
	
	return 0;
}
