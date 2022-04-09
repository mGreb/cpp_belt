#include <algorithm>
#include <numeric>
#include <vector>
#include <iostream>

template <typename RandomIt>
void MergeSort2(RandomIt range_begin, RandomIt range_end) {  // two-way merge sort
	
	if (range_end - range_begin < 2)
		return;
	
	std::vector<typename RandomIt::value_type> elements(range_begin, range_end);
	auto middle_it = begin(elements) + elements.size() / 2;
	MergeSort2(begin(elements), middle_it);
	MergeSort2(middle_it, end(elements));
	
	std::merge(begin(elements), middle_it, middle_it, end(elements), range_begin);
	
//	auto middle_it = range_begin + (range_end - range_begin) / 2;
//	MergeSort(range_begin, middle_it);
//	MergeSort(middle_it, range_end);
//	std::inplace_merge(range_begin, middle_it, range_end);
}

template <typename RandomIt>
void MergeSort3(RandomIt range_begin, RandomIt range_end) {  // three-way merge sort

	if (range_end - range_begin < 2)
		return;

	std::vector<typename RandomIt::value_type> elements(range_begin, range_end);
	
	auto one_third = begin(elements) + elements.size() / 3;
	auto two_third = begin(elements) + elements.size() / 3 * 2;
	
	MergeSort3(begin(elements), one_third);
	MergeSort3(one_third, two_third);
	MergeSort3(two_third, end(elements));

	std::vector<typename RandomIt::value_type> temp;
	std::merge(begin(elements), one_third, one_third, two_third, back_inserter(temp));
	std::merge(begin(temp), end(temp), two_third, end(elements), range_begin);
}

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {  // comment and un-comment here
//	MergeSort2(range_begin, range_end);
	MergeSort3(range_begin, range_end);
}

int main() {
	std::vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 8};
	MergeSort(begin(v), end(v));
	for (int x : v) {
		std::cout << x << " ";
	}
	std::cout << std::endl;
	
	return 0;
}
