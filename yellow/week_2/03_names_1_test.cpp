#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

// comment this class before sending!
class Person {
public:
	void ChangeFirstName(int year, const std::string &first_name) {
		data[year].first = first_name;
	}
	void ChangeLastName(int year, const std::string &last_name) {
		data[year].second = last_name;
	}
	std::string GetFullName(int year) {
		std::string first, last;
		for (const auto &p : data) {
			if (p.first > year)
				break;
			first = !p.second.first.empty() ? p.second.first : first;
			last = !p.second.second.empty() ? p.second.second : last;
		}
		if (first.empty() && last.empty())
			return "Incognito";
		if (!first.empty() && last.empty())
			return first + " with unknown last name";
		if (first.empty() && !last.empty())
			return last + " with unknown first name";
		return first + " " + last;
	}
private:
	std::map<int, std::pair<std::string, std::string>> data;
};

template <class T>
std::ostream& operator << (std::ostream& os, const std::vector<T>& s) {
	os << "{";
	bool first = true;
	for (const auto& x : s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template <class T>
std::ostream& operator << (std::ostream& os, const std::set<T>& s) {
	os << "{";
	bool first = true;
	for (const auto& x : s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template <class K, class V>
std::ostream& operator << (std::ostream& os, const std::map<K, V>& m) {
	os << "{";
	bool first = true;
	for (const auto& kv : m) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << kv.first << ": " << kv.second;
	}
	return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const std::string& hint = {}) {
	if (t != u) {
		std::ostringstream os;
		os << "Assertion failed: " << t << " != " << u;
		if (!hint.empty()) {
			os << " hint: " << hint;
		}
		throw std::runtime_error(os.str());
	}
}

void Assert(bool b, const std::string& hint) {
	AssertEqual(b, true, hint);
}

class TestRunner {
public:
	template <class TestFunc>
	void RunTest(TestFunc func, const std::string& test_name) {
		try {
			func();
			std::cerr << test_name << " OK" << std::endl;
		} catch (std::exception& e) {
			++fail_count;
			std::cerr << test_name << " fail: " << e.what() << std::endl;
		} catch (...) {
			++fail_count;
			std::cerr << "Unknown exception caught" << std::endl;
		}
	}

	~TestRunner() {
		if (fail_count > 0) {
			std::cerr << fail_count << " unit tests failed. Terminate" << std::endl;
			exit(1);
		}
	}

private:
	int fail_count = 0;
};

void TestPersonEmpty() {
	Person person;
	AssertEqual(person.GetFullName(1900), "Incognito", "test empty person");
}

void TestPersonFirstName() {
	Person person;
	person.ChangeFirstName(1901, "Polina");
	AssertEqual(person.GetFullName(1902), "Polina with unknown last name", "test f/n 1");
	AssertEqual(person.GetFullName(1900), "Incognito", "test f/n 2");
}

void TestPersonLastName() {
	Person person;
	person.ChangeLastName(1901, "Sergeeva");
	AssertEqual(person.GetFullName(1902), "Sergeeva with unknown first name", "test l/n 1");
	AssertEqual(person.GetFullName(1900), "Incognito", "test l/n 2");
}

void TestPerson() {
	TestPersonEmpty();
	TestPersonFirstName();
	TestPersonLastName();
}

int main() {
	TestRunner runner;
	runner.RunTest(TestPerson, "all tests");
	return 0;
}
