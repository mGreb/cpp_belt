#include "test_runner.h"

#include <string>
#include <vector>
#include <list>
#include <forward_list>
#include <numeric>
#include <iterator>


template<typename ForwardIterator, typename UnaryPredicate>
ForwardIterator max_element_if(ForwardIterator first, ForwardIterator last, UnaryPredicate pred)
{
	if (first == last)  // handling empty inteval
		return last;
	
	ForwardIterator max_elem_it = first;
	
	// find first element with valid pred
	while (max_elem_it != last)
	{
		if (pred(*max_elem_it))
			break;
		++max_elem_it;
	}
	
	// find max element with valid pred, starting from max_elem_it
	for (ForwardIterator it = max_elem_it; it != last; ++it)
	{
		if (it != max_elem_it && pred(*it) && *it > *max_elem_it)
			max_elem_it = it;
	}
	
	return max_elem_it;
}

void TestUniqueMax()
{
	auto IsEven = [](int x) {
		return x % 2 == 0;
	};
	
	const std::list<int> hill{2, 4, 8, 9, 6, 4, 2};
	auto max_iterator = hill.begin();
	advance(max_iterator, 2);
	
	std::vector<int> numbers(10);
	iota(numbers.begin(), numbers.end(), 1);
	
	Assert(
			max_element_if(numbers.begin(), numbers.end(), IsEven) == --numbers.end(),
			"Expect the last element"
			);
	Assert(
			max_element_if(hill.begin(), hill.end(), IsEven) == max_iterator,
			"Expect the maximal even number"
			);
}

void TestSeveralMax()
{
	struct IsCapitalized {
		bool operator()(const std::string &s) {
			return !s.empty() && isupper(s.front());
		}
	};
	
	const std::forward_list<std::string> text{"One", "two", "Three", "One", "Two",
								 "Three", "one", "Two", "three"};
	auto max_iterator = text.begin();
	advance(max_iterator, 4);
	
	Assert(
			max_element_if(text.begin(), text.end(), IsCapitalized()) == max_iterator,
			"Expect the first \"Two\""
			);
}

void TestNoMax()
{
	const std::vector<int> empty;
	const std::string str = "Non-empty string";
	
	auto AlwaysTrue = [](int) {
		return true;
	};
	
	Assert(
			max_element_if(empty.begin(), empty.end(), AlwaysTrue) == empty.end(),
			"Expect end for empty container"
			);
	
	auto AlwaysFalse = [](char) {
		return false;
	};
	
	Assert(
			max_element_if(str.begin(), str.end(), AlwaysFalse) == str.end(),
			"Expect end for AlwaysFalse predicate"
			);
}

void TestFirstMax()
{
	auto IsEven = [](int x) { return x % 2 == 0; };
	{
		const std::vector<int> v = {10, 2, 1, 1, 12};
		Assert(
				max_element_if(v.begin(), v.end(), IsEven) == std::prev(v.end()),
				"Expect end"
		);
	}
	
	{
		const std::vector<int> v = {12, 2, 1, 1, 12};
		Assert(
				max_element_if(v.begin(), v.end(), IsEven) == v.begin(),
				"Expect first"
		);
	}
};

int main() {
  TestRunner tr;
  tr.RunTest(TestUniqueMax, "TestUniqueMax");
  tr.RunTest(TestSeveralMax, "TestSeveralMax");
  tr.RunTest(TestNoMax, "TestNoMax");
  tr.RunTest(TestFirstMax, "TestFirstMax");
  
  return 0;
}