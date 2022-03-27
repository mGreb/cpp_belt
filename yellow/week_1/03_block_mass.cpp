#include <iostream>

int main() {
	uint64_t n = 0;
	uint64_t r = 0;
	std::cin >> n >> r;
	
	uint64_t sum = 0;
	
	for (uint64_t i = 0; i < n; ++i) {
		uint64_t w, h, d;
		std::cin >> w >> h >> d;
		sum += w * d * h;
	}
	
	uint64_t res = sum * r;
	std::cout << res;
	
	return 0;
}
