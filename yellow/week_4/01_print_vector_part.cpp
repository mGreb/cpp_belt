#include <vector>
#include <iostream>
#include <algorithm>

void PrintVectorPart(const std::vector<int>& numbers) {
	if (numbers.empty())
		return;
	auto it = numbers.begin();
	while (*it >= 0 && it != numbers.end())
		it++;
	while (it != numbers.begin()) {
		it--;
		std::cout << *it << " ";
	}
}

void PrintVectorPartYA(const std::vector<int>& numbers) {
	auto negative_it = std::find_if(
			numbers.begin(), numbers.end(),
			[](int number) {
				return number < 0;
			}
	);

	for (auto it = negative_it; it != numbers.begin(); ) {
		std::cout << *(--it) << " ";
	}
}

int main() {
	PrintVectorPart({6, 1, 8, -5, 4});
	std::cout << std::endl;
	PrintVectorPart({-6, 1, 8, -5, 4});  // ничего не выведется
	std::cout << std::endl;
	PrintVectorPart({6, 1, 8, 5, 4});
	std::cout << std::endl;
	PrintVectorPart({});
	std::cout << std::endl;
	PrintVectorPart({6, 1, 8, 5, -4});
	std::cout << std::endl;
	return 0;
}
