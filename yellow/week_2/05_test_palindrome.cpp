#include <iostream>
#include <set>
#include <map>
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

bool IsPalindrome(const std::string& s) {
	if (s.empty())
		return true;
	size_t start = 0, end = s.size() - 1;
	while (start < end) {
		if (s[start] != s[end])
			return false;
		++start;
		--end;
	}
	return true;
}

void Test() {
	AssertEqual(IsPalindrome(""), true, "empty");
	AssertEqual(IsPalindrome("x"), true, "x");
	AssertEqual(IsPalindrome(" "), true, "_");
	AssertEqual(IsPalindrome("  "), true, "__");
	AssertEqual(IsPalindrome("   "), true, "___");
	AssertEqual(IsPalindrome("aa"), true, "aa");
	AssertEqual(IsPalindrome("aA"), false, "aA");
	AssertEqual(IsPalindrome("ab"), false, "ab");
	AssertEqual(IsPalindrome("aba"), true, "aba");
	AssertEqual(IsPalindrome("abac"), false, "abac");
	AssertEqual(IsPalindrome(" aba "), true, "_aba_");
	AssertEqual(IsPalindrome(" aa"), false, "_aa");
	AssertEqual(IsPalindrome("  a "), false, "__a_");
	AssertEqual(IsPalindrome("aa "), false, "aa_");
	AssertEqual(IsPalindrome("123454321"), true, "123454321");
	AssertEqual(IsPalindrome("madam"), true, "madam");
	AssertEqual(IsPalindrome("level"), true, "level");
	AssertEqual(IsPalindrome("leval"), false, "leval");
	AssertEqual(IsPalindrome("wasitacaroracatisaw"), true, "wasitacaroracatisaw");
	AssertEqual(IsPalindrome("wasitacarqracatisaw"), true, "wasitacarqracatisaw");
	AssertEqual(IsPalindrome("abcdefghijklmnopqrstuvwxyzzyxwvutsrqponmlkjihgfedcba"), true);
	AssertEqual(IsPalindrome("abcdefghijklnopqrstuvwxyzzyxwvutsrqponmlkjihgfedcba"), false);
	AssertEqual(IsPalindrome("\t\n  \n\t"), true);
	AssertEqual(IsPalindrome(""), true, "empty string is a palindrome");
	AssertEqual(IsPalindrome("a"), true, "one letter string is a palindrome");
	AssertEqual(IsPalindrome("abba"), true, "abba is a palindrome");
	AssertEqual(IsPalindrome("abXba"), true, "abXba is a palindrome");
	AssertEqual(IsPalindrome("a b X b a"), true, "`a b X b a` is a palindrome");
	AssertEqual(IsPalindrome("  ABBA  "), true, "`  ABBA  ` is a palindrome");
	AssertEqual(IsPalindrome("XabbaY"), false, "XabbaY is not a palindrome");
	AssertEqual(IsPalindrome("abXYba"), false, "abXYba is not a palindrome");
	AssertEqual(IsPalindrome("Xabba"), false , "Xabba is not a palindrome");
	AssertEqual(IsPalindrome("abbaX"), false, "abbaX is not a palindrome");
	AssertEqual(IsPalindrome("was it a car or a cat i saw"), false, "`was it a car or a cat i saw` is not a palindrome because spaces do not match");
	AssertEqual(IsPalindrome("ABBA   "), false, "`ABBA   ` is not a palindrome");
	AssertEqual(IsPalindrome("  ABBA"), false, "`  ABBA` is not a palindrome");
}

int main() {
	TestRunner runner;
	runner.RunTest(Test, "all tests");
	return 0;
}
