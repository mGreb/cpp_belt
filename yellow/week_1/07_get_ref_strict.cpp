#include <string>
#include <map>
#include <iostream>
#include <stdexcept>

template <typename Key, typename Value>
Value& GetRefStrict(std::map<Key, Value> &m, const Key &k) {
	if (m.find(k) == m.end())
		throw std::runtime_error("key not found");
	return m.at(k);
}

int main() {
	
	std::map<int, std::string> m = {{0, "value"}};
	std::string& item = GetRefStrict(m, 0);
	item = "newvalue";
	std::cout << m[0] << std::endl; // выведет newvalue
	
	return 0;
}
