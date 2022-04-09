#include <string>
#include <vector>

std::vector<int> Reversed(const std::vector<int>& v) {
	size_t sz = v.size();
	std::vector<int> res(sz);
	for (size_t i = 0; i < sz; ++i)
		res[i] = v[sz - 1 - i];
	return res;
}

int main()
{
	std::vector<int> numbers = {1, 5, 3, 4, 2};
	std::vector<int> numbers1 = Reversed(numbers);
	
	return 0;
}
