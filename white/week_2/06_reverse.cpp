#include <string>
#include <vector>

void Reverse(std::vector<int>& v) {
	size_t sz = v.size();
	for (size_t i = 0; i < sz / 2; ++i) {
		int tmp = v[i];
		v[i] = v[sz - 1 - i];
		v[sz - 1 - i] = tmp;
	}
}

int main()
{
	std::vector<int> numbers = {1, 5, 3, 4, 2};
	Reverse(numbers);
	
	return 0;
}
