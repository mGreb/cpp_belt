#include "db_tests.h"

// user includes
#include "database.h"
#include "test_runner.h"
#include "condition_parser.h"
#include "event.h"
// system includes


std::string Entry(const Date& date, const std::string& event) {
	std::ostringstream ostream;
	ostream << date << " " << event;
	return ostream.str();
}


void AddEventFromString(Database &db, const std::string &s)
{
	std::istringstream is(s);
	const auto date = ParseDate(is);
	const auto event = ParseEvent(is);
	db.Add(date, event);
}


std::ostringstream FindIfFromString(const Database &db, const std::string &s)
{
	std::istringstream is(s);
	auto condition = ParseCondition(is);
	auto predicate = [condition](const Date& date, const std::string& event) {
		return condition->Evaluate(date, event);
	};
	
	const auto entries = db.FindIf(predicate);
	std::ostringstream os;
	for (const auto& entry : entries)
		os << entry << std::endl;
	os << "Found " << entries.size() << " entries" << std::endl;
	
	return os;
}


int RemoveIfFromString(Database &db, const std::string &s)
{
	std::istringstream is(s);
	auto condition = ParseCondition(is);
	auto predicate = [condition](const Date& date, const std::string& event) {
		return condition->Evaluate(date, event);
	};
	
	return db.RemoveIf(predicate);
}


int DoRemove (Database& db, const std::string& str) {
	std::istringstream is (str);
	auto condition = ParseCondition(is);
	auto predicate = [condition](const Date &date, const std::string &event) {
		return condition->Evaluate(date, event);
	};
	return db.RemoveIf(predicate);
}


std::string DoFind (const Database& db, const std::string& str) {
	std::istringstream is (str);
	auto condition = ParseCondition(is);
	auto predicate = [condition](const Date &date, const std::string &event) {
		return condition->Evaluate(date, event);
	};
	const auto entries = db.FindIf(predicate);
	std::ostringstream os;
	for (const auto& entry : entries) {
		os << entry << std::endl;
	}
	os << entries.size();
	return os.str();
}


void TestAdd()
{
	Database db;
	
	AddEventFromString(db, "2017-01-01 Holiday");
	AddEventFromString(db, "2017-03-08 Holiday");
	AddEventFromString(db, "2017-01-01 New Year");
	AddEventFromString(db, "2017-01-01 New Year");
	
	std::ostringstream os;
	db.Print(os);
	AssertEqual(os.str(), "2017-01-01 Holiday\n2017-01-01 New Year\n2017-03-08 Holiday\n", "Test Add 1");
}


void TestDel()
{
	Database db;
	
	AddEventFromString(db, "2017-06-01 1st of June");
	AddEventFromString(db, "2017-07-08 8th of July");
	AddEventFromString(db, "2017-07-08 Someone's birthday");
	
	const int count = RemoveIfFromString(db, "date == 2017-07-08");
	
	AssertEqual(count, 2, "Test Del 1");
}


void TestPrint()
{
	Database db;
	
	AddEventFromString(db, "2017-01-01 Holiday");
	AddEventFromString(db, "2017-03-08 Holiday");
	AddEventFromString(db, "2017-01-01 New Year");
	AddEventFromString(db, "2017-01-01 New Year");
	
	std::ostringstream os;
	db.Print(os);
	AssertEqual(os.str(), "2017-01-01 Holiday\n2017-01-01 New Year\n2017-03-08 Holiday\n", "Test Add 1");
}


void TestFind()
{
	Database db;
	
	AddEventFromString(db, "2017-01-01 Holiday");
	AddEventFromString(db, "2017-03-08 Holiday");
	AddEventFromString(db, "2017-01-01 New Year");
	
	std::ostringstream os = FindIfFromString(db, "event != \"working day\"");
	
	AddEventFromString(db, "2017-05-09 Holiday");
	
	AssertEqual(os.str(), "2017-01-01 Holiday\n2017-01-01 New Year\n2017-03-08 Holiday\nFound 3 entries\n", "Test Find 1");
	
	os = FindIfFromString(db, "");
	AssertEqual(os.str(), "2017-01-01 Holiday\n2017-01-01 New Year\n2017-03-08 Holiday\n2017-05-09 Holiday\nFound 4 entries\n", "Test Find 2");
}


void TestLast()
{
	Database db;
	
	AddEventFromString(db, "2017-01-01 New Year");
	AddEventFromString(db, "2017-03-08 Holiday");
	AddEventFromString(db, "2017-01-01 Holiday");
	
	try{
		db.Last(Date(2016, 12, 31));
	} catch (std::invalid_argument&) {
		std::cerr << "No entries OK" << std::endl;
	}
//	AssertEqual(res1, "No entries", "Test Last 1");
	const auto res2 = db.Last(Date(2017, 01, 01));
	AssertEqual(res2, "2017-01-01 Holiday", "Test Last 1");
	const auto res3 = db.Last(Date(2017, 06, 01));
	AssertEqual(res3, "2017-03-08 Holiday", "Test Last 1");
	
	AddEventFromString(db, "2017-05-09 Holiday");
}


void TestGeneral()
{
	Database db;
	
	AddEventFromString(db, "2017-11-21 Tuesday");
	AddEventFromString(db, "2017-11-20 Monday");
	AddEventFromString(db, "2017-11-21 Weekly meeting");
	
	std::ostringstream os;
	db.Print(os);
	AssertEqual(os.str(), "2017-11-20 Monday\n2017-11-21 Tuesday\n2017-11-21 Weekly meeting\n", "Test General 1");
	
	os = FindIfFromString(db, "event != \"Weekly meeting\"");
	AssertEqual(os.str(), "2017-11-20 Monday\n2017-11-21 Tuesday\nFound 2 entries\n", "Test General 2");
	
	AssertEqual(db.Last(Date{2017, 11, 30}), "2017-11-21 Weekly meeting", "Test General 3");
	
	const int removed_num = RemoveIfFromString(db, "date > 2017-11-20");
	AssertEqual(removed_num, 2, "Test General 4");
	
	AssertEqual(db.Last(Date{2017, 11, 30}), "2017-11-20 Monday", "Test General 5");
	
	try {
		db.Last(Date{2017, 11, 01});
	} catch (std::invalid_argument&) {
		std::cerr << "No entries OK" << std::endl;
	}
}


void TestsMyCustom()
{
	{
		Database db;
		db.Add({2019, 12, 18}, "Kolya");
		db.Add({2020, 1, 15}, "Katya");
		db.Add({2020, 2, 22}, "Riding");
		db.Add({2019, 12, 9}, "Go home");
		db.Add({2019, 12, 9}, "Read");
		std::ostringstream out;
		db.Print(out);
		AssertEqual("2019-12-09 Go home\n2019-12-09 Read\n2019-12-18 Kolya\n2020-01-15 Katya\n2020-02-22 Riding\n", out.str(), "Order of insertion");
	}
	
	{
		Database db;
		db.Add({2019, 12, 1}, "a");
		db.Add({2019, 12, 1}, "b");
		db.Add({2019, 12, 2}, "c");
		db.Add({2019, 12, 2}, "d");
		db.Add({2019, 12, 3}, "e");
		std::ostringstream out;
		db.Print(out);
		AssertEqual("2019-12-01 a\n2019-12-01 b\n2019-12-02 c\n2019-12-02 d\n2019-12-03 e\n", out.str(), "Order of insertion");
	}
	
	{
		Database db;
		std::istringstream ss("    a");
		const auto event = ParseEvent(ss);
		db.Add({2019, 12, 1}, event);
		std::ostringstream out;
		db.Print(out);
		AssertEqual("2019-12-01 a\n", out.str(), "My test 20");
	}
	
	{
		Database db;
		db.Add({2019, 12, 1}, "a");
		db.Add({2019, 12, 1}, "b");
		db.Add({2019, 12, 2}, "c c");
		db.Add({2019, 12, 2}, "d");
		db.Add({2019, 12, 3}, "e");
		db.Add({2019, 12, 3}, "f");
		std::ostringstream out;
		db.Print(out);
		AssertEqual("2019-12-01 a\n2019-12-01 b\n2019-12-02 c c\n2019-12-02 d\n2019-12-03 e\n2019-12-03 f\n", out.str(), "My test 2");
		AssertEqual(1, DoRemove(db, R"(event == "c" OR event == "d")" ), "My test 3");
		AssertEqual(1, DoRemove(db, R"(event == "e" AND event != "a")" ), "My test 4");
		db.Add({2019, 11, 30}, "a");
		AssertEqual("2019-12-03 f\n1", DoFind(db, R"(date >= 2019-12-3)"), "My test 5");
		AssertEqual(Entry({2019, 12, 3}, "f"), db.Last({2019, 12, 4}), " My test 6");
		
		try
		{
			db.Last({2019, 11, 3});
		}
		catch(std::invalid_argument&)
		{
			std::cerr << "No entries OK" << std::endl;
		}
		
		AssertEqual(Entry({2019, 12, 2}, "c c"), db.Last({2019, 12, 2}), " My test 7");
		
		AssertEqual(Entry({2019, 12, 3}, "f"), db.Last({2019, 12, 4}), " My test 8");
		
		db.Add({2019, 12, 3}, "m");
		AssertEqual(Entry({2019, 12, 3}, "m"), db.Last({2019, 12, 3}), " My test 9");
		
		AssertEqual(1, DoRemove(db, R"(event == "e" AND event != "a" OR event == "m" AND date == 2019-12-3)" ), "My test 10");
		
		std::ostringstream out2;
		db.Print(out2);
		AssertEqual("2019-11-30 a\n2019-12-01 a\n2019-12-01 b\n2019-12-02 c c\n2019-12-03 f\n", out2.str(), "My test 11");
	}
	
	{
		Database db;
		db.Add({2019, 12, 1}, "a");
		db.Add({2019, 12, 1}, "b");
		db.Add({2019, 12, 1}, "a");
		db.Add({2019, 12, 2}, "c");
		db.Add({2019, 12, 2}, "a");
		db.Add({2019, 12, 2}, "a");
		
		AssertEqual(2, DoRemove(db, R"(event == "a")" ), "My test 12");
	}
	
	{
		Database db;
		db.Add({2019, 12, 1}, "a");
		db.Add({2019, 12, 1}, "aa");
		db.Add({2019, 12, 1}, "aaa");
		
		AssertEqual(2, DoRemove(db, R"(event >= "aa")" ), "My test 13");
		
		std::ostringstream out;
		db.Print(out);
		AssertEqual("2019-12-01 a\n", out.str(), "My test 14");
	}
	
	{
		Database db;
		db.Add({2019, 12, 1}, "a");
		db.Add({2019, 12, 1}, "aa");
		db.Add({2019, 12, 1}, "aaa");
		db.Add({2019, 12, 2}, "b");
		db.Add({2019, 12, 2}, "a");
		
		AssertEqual(2, DoRemove(db, R"(event > "aa")" ), "My test 15");
		
		std::ostringstream out;
		db.Print(out);
		AssertEqual("2019-12-01 a\n2019-12-01 aa\n2019-12-02 a\n", out.str(), "My test 16");
	}
	
	{
		Database db;
		db.Add({2019, 12, 1}, "a");
		db.Add({2019, 12, 1}, "aa");
		db.Add({2019, 12, 1}, "aaa");
		db.Add({2019, 12, 2}, "b");
		db.Add({2019, 12, 2}, "a");
		
		AssertEqual(2, DoRemove(db, R"(event < "aa")" ), "My test 17");
		
		std::ostringstream out;
		db.Print(out);
		AssertEqual("2019-12-01 aa\n2019-12-01 aaa\n2019-12-02 b\n", out.str(), "My test 18");
	}
	
	{
		Database db;
		db.Add({2019, 12, 1}, "a");
		db.Add({2019, 12, 1}, "b");
		
		AssertEqual(1, DoRemove(db, R"(event != "b")" ), "My test 19");
		
		db.Add({2019, 12, 1}, "c");
		
		AssertEqual(Entry({2019, 12, 1}, "c"), db.Last({2019, 12, 1}), " My test 20");
		
		db.Add({2019, 12, 1}, "b");
		AssertEqual(Entry({2019, 12, 1}, "c"), db.Last({2019, 12, 1}), " My test 21");
		
		std::ostringstream out;
		db.Print(out);
		AssertEqual("2019-12-01 b\n2019-12-01 c\n", out.str(), "My test 22");
	}
}


void TestDatabase()
{
	std::istringstream empty_is("");
	auto empty_condition = ParseCondition(empty_is);
	auto empty_predicate = [empty_condition](const Date& date, const std::string& event) {
		return empty_condition->Evaluate(date, event);
	};
	
	// Add 2 - Del 1 - Add deleted again
	{
		Database db;
		Date d(2019, 1, 1);
		db.Add(d, "e1");
		db.Add(d, "e2");
		std::istringstream is(R"(event == "e1")");
		auto condition = ParseCondition(is);
		auto predicate = [condition](const Date& date, const std::string& event) {
			return condition->Evaluate(date, event);
		};
		AssertEqual(db.RemoveIf(predicate), 1, "Db Add2-Del-Add 1");
		db.Add(d, "e1");
		AssertEqual(db.FindIf(empty_predicate).size(), 2, "Db Add2-Del-Add 2");
	}
	
	// Add
	{
		Database db;
		Date d(2019, 1, 1);
		db.Add(d, "e1");
		db.Add(d, "e1");
		std::istringstream is("date == 2019-01-01");
		auto condition = ParseCondition(is);
		auto predicate = [condition](const Date& date, const std::string& event) {
			return condition->Evaluate(date, event);
		};
		AssertEqual(db.FindIf(predicate).size(), 1, "Db Add Duplicates 1");
	}
	
	// Last
	{
		Database db;
		Date d(2019, 1, 1);
		Date d1(2019, 1, 2);
		Date d2(2018, 12, 22);
		db.Add(d1, "e1");
		db.Add(d2, "e2");
		auto res1 = db.Last(d);
		AssertEqual(res1, Entry({2018, 12, 22}, "e2"), "Db Last 1");
		Date d3(2018, 12, 24);
		db.Add(d3, "e3");
		AssertEqual(db.Last(d), Entry({2018, 12, 24}, "e3"), "Db Last 2");
		
		// Get last event for date before first event
		try {
			Date d4(2017, 2, 2);
			db.Last(d4);
			Assert(false, "Db Last 3");
		} catch (std::invalid_argument &e) {
			// Pass
		}
		
		// Delete event and get last
		std::istringstream is("date == 2018-12-24");
		auto condition = ParseCondition(is);
		auto predicate = [condition](const Date& date, const std::string& event) {
			return condition->Evaluate(date, event);
		};
		db.RemoveIf(predicate);
		AssertEqual(db.Last(d), Entry({2018, 12, 22}, "e2"), "Db Last 4");
		
		AssertEqual(db.Last(d1), Entry({2019, 1, 2}, "e1"), "Db Last 5");
		db.Add(d2, "e4");
		AssertEqual(db.Last(d2), Entry({2018, 12, 22}, "e4"), "Db Last 6");
	}
	
	// Del
	{
		Database db;
		db.Add({2019, 1, 1}, "e1");
		db.Add({2019, 1, 1}, "e2");
		db.Add({2018, 1, 7}, "e3");
		db.Add({2018, 1, 7}, "e4");
		std::istringstream is("date == 2018-01-07");
		auto condition = ParseCondition(is);
		auto predicate = [condition](const Date& date, const std::string& event) {
			return condition->Evaluate(date, event);
		};
		AssertEqual(db.RemoveIf(predicate), 2, "Db Del 1");
	}
	{
		Database db;
		db.Add({2019, 1, 1}, "e1");
		db.Add({2019, 1, 1}, "e2");
		db.Add({2018, 1, 7}, "e3");
		db.Add({2018, 1, 7}, "e4");
		std::istringstream is("date >= 2018-01-07 AND date <= 2020-01-01");
		auto condition = ParseCondition(is);
		auto predicate = [condition](const Date& date, const std::string& event) {
			return condition->Evaluate(date, event);
		};
		AssertEqual(db.RemoveIf(predicate), 4, "Db Del 2");
	}
	{
		Database db;
		db.Add({2019, 1, 1}, "e1");
		db.Add({2019, 1, 1}, "e2");
		db.Add({2018, 1, 7}, "e3");
		db.Add({2018, 1, 7}, "e4");
		AssertEqual(db.RemoveIf(empty_predicate), 4, "Db Del 3");
	}
	{
		Database db;
		db.Add({2019, 1, 1}, "e1");
		db.Add({2019, 1, 1}, "e2");
		db.Add({2018, 1, 7}, "e3");
		db.Add({2018, 1, 7}, "e4");
		std::istringstream is(R"(event == "e1")");
		auto condition = ParseCondition(is);
		auto predicate = [condition](const Date& date, const std::string& event) {
			return condition->Evaluate(date, event);
		};
		AssertEqual(db.RemoveIf(predicate), 1, "Db Del 4");
	}
	
	{
		Database db;
		db.Add({2019, 1, 1}, "e1");
		db.Add({2019, 1, 1}, "e2");
		db.Add({2018, 1, 7}, "e3");
		db.Add({2018, 1, 7}, "e4");
		std::istringstream is(R"(event == "e1" OR date == 2019-01-01)");
		auto condition = ParseCondition(is);
		auto predicate = [condition](const Date& date, const std::string& event) {
			return condition->Evaluate(date, event);
		};
		AssertEqual(db.RemoveIf(predicate), 2, "Db Del 5");
	}
	
	// Find
	{
		Database db;
		db.Add({2019, 1, 1}, "e1");
		db.Add({2019, 1, 1}, "e2");
		db.Add({2018, 1, 7}, "e3");
		db.Add({2018, 1, 7}, "e4");
		std::istringstream is("date == 2018-01-07");
		auto condition = ParseCondition(is);
		auto predicate = [condition](const Date& date, const std::string& event) {
			return condition->Evaluate(date, event);
		};
		AssertEqual(db.FindIf(predicate).size(), 2, "Db Find 1");
	}
	{
		Database db;
		db.Add({2019, 1, 1}, "e1");
		db.Add({2019, 1, 1}, "e2");
		db.Add({2018, 1, 7}, "e3");
		db.Add({2018, 1, 7}, "e4");
		std::istringstream is("date >= 2018-01-07 AND date <= 2020-01-01");
		auto condition = ParseCondition(is);
		auto predicate = [condition](const Date& date, const std::string& event) {
			return condition->Evaluate(date, event);
		};
		AssertEqual(db.FindIf(predicate).size(), 4, "Db Find 2");
	}
	{
		Database db;
		db.Add({2019, 1, 1}, "e1");
		db.Add({2019, 1, 1}, "e2");
		db.Add({2018, 1, 7}, "e3");
		db.Add({2018, 1, 7}, "e4");
		AssertEqual(db.FindIf(empty_predicate).size(), 4, "Db Find 3");
	}
	{
		Database db;
		db.Add({2019, 1, 1}, "e1");
		db.Add({2019, 1, 1}, "e2");
		db.Add({2018, 1, 7}, "e3");
		db.Add({2018, 1, 7}, "e4");
		std::istringstream is(R"(event == "e1")");
		auto condition = ParseCondition(is);
		auto predicate = [condition](const Date& date, const std::string& event) {
			return condition->Evaluate(date, event);
		};
		AssertEqual(db.FindIf(predicate).size(), 1, "Db Find 4");
	}
	
	{
		Database db;
		db.Add({2019, 1, 1}, "e1");
		db.Add({2019, 1, 1}, "e2");
		db.Add({2018, 1, 7}, "e3");
		db.Add({2018, 1, 7}, "e4");
		std::istringstream is(R"(event == "e1" OR date == 2019-01-01)");
		auto condition = ParseCondition(is);
		auto predicate = [condition](const Date& date, const std::string& event) {
			return condition->Evaluate(date, event);
		};
		AssertEqual(db.FindIf(predicate).size(), 2, "Db Find 5");
	}
	
	// Add - Del - Add - Del
	{
		Database db;
		db.Add({2019, 1, 1}, "e1");
		db.Add({2019, 1, 1}, "e2");
		AssertEqual(db.RemoveIf(empty_predicate), 2, "Db Add-Del-Add-Del 1");
		
		db.Add({2019, 1, 1}, "e1");
		db.Add({2019, 1, 1}, "e2");
		AssertEqual(db.RemoveIf(empty_predicate), 2, "Db Add-Del-Add-Del 1");
	}
	
	{
		Database db;
		db.Add({2017, 1, 1}, "first");
		db.Add({2017, 1, 1}, "second");
		db.Add({2017, 1, 1}, "third");
		db.Add({2017, 1, 1}, "fourth");
		db.Add({2017, 1, 1}, "five");
		AssertEqual(2, DoRemove(db, R"(event == "second" OR event == "fourth")"), "Remove several");
		std::ostringstream os;
		db.Print(os);
		AssertEqual("2017-01-01 first\n2017-01-01 third\n2017-01-01 five\n", os.str(), "Check print after remove several- 3");
	}
}
