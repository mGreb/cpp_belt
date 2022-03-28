#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

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

int GetDistinctRealRootCount(double a, double b, double c) {
	if (a == 0 && b == 0 && c == 0) return 0;
	if (a == 0 && b == 0 && c != 0) return 0;
	if (a == 0 && b != 0 && c == 0) return 1;
	if (a == 0 && b != 0 && c != 0) return 1;
	if (a != 0 && b == 0 && c == 0) return 1;
	if (a != 0 && b == 0 && c != 0) {
		if (a * c < 0)
			return 2;
		else
			return 0;
	}
	if (a != 0 && b != 0 && c == 0) return 2;
	if (a != 0 && b != 0 && c != 0) {
		const double d = b * b - 4 * a * c;
		if (d  > 0) return 2;
		if (d  < 0) return 0;
		if (d == 0) return 1;
	}
	return 0;
}

void TestRealRootCount() {
	AssertEqual(GetDistinctRealRootCount(0, 0, 0), 0, "0 0 0");
	AssertEqual(GetDistinctRealRootCount(0, 0, 1), 0, "0 0 1");
	AssertEqual(GetDistinctRealRootCount(0, 1, 0), 1, "0 1 0");
	AssertEqual(GetDistinctRealRootCount(0, 1, 1), 1, "0 1 1");
	AssertEqual(GetDistinctRealRootCount(1, 0, 0), 1, "1 0 0");
	
	AssertEqual(GetDistinctRealRootCount(1, 0, 1), 0, "1 0 1");
	AssertEqual(GetDistinctRealRootCount(1, 0, -1), 2, "1 0 -1");
	
	AssertEqual(GetDistinctRealRootCount(1, 1, 0), 2, "1 1 0");
	
	AssertEqual(GetDistinctRealRootCount(1, 10, 1), 2, "1 10 1");
	AssertEqual(GetDistinctRealRootCount(10, 1, 10), 0, "10 1 10");
	AssertEqual(GetDistinctRealRootCount(1, 2, 1), 1, "1 2 1");
}

int main() {
	TestRunner runner;
	runner.RunTest(TestRealRootCount, "all tests");
	return 0;
}
