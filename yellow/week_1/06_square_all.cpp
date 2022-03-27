// для vector элементы нужно возвести в квадрат;
// для map в квадрат нужно возвести только значения, но не ключи;
// для pair в квадрат нужно возвести каждый элемент пары

#include <vector>
#include <map>
#include <iostream>

// Предварительное объявление шаблонных функций
template <typename T> std::vector<T> Sqr(const std::vector<T> &v);
template <typename Key, typename Value> std::map<Key, Value> Sqr(const std::map<Key, Value> &m);
template <typename F, typename S> std::pair<F, S> Sqr(const std::pair<F, S> &p);
template <typename T> T Sqr(const T &t);

template <typename T>
std::vector<T> Sqr(const std::vector<T> &v) {
	std::vector<T> res(v.size());
	for (size_t i = 0; i < v.size(); ++i)
		res[i] = Sqr(v[i]);
	return res;
}

template <typename Key, typename Value>
std::map<Key, Value> Sqr(const std::map<Key, Value> &m) {
	std::map<Key, Value> m_res;
	for (auto &[key, value] : m)
		m_res[key] = Sqr(value);
	return m_res;
}

template <typename F, typename S>
std::pair<F, S> Sqr(const std::pair<F, S> &p) {
	return {Sqr(p.first), Sqr(p.second)};
}

// number squared
template <typename T>
T Sqr(const T &t) {
	return t * t;
}

int main() {
	{
		// Пример вызова функции
		std::vector<int> v = {1, 2, 3};
		std::cout << "vector:";
		for (int x : Sqr(v)) {
			std::cout << ' ' << x;
		}
		std::cout << std::endl;
		
		std::map<int, std::pair<int, int>> map_of_pairs = {
			{4, {2, 2}},
			{7, {4, 3}}
		};
		std::cout << "map of pairs:" << std::endl;
		for (const auto& x : Sqr(map_of_pairs)) {
			std::cout << x.first << ' ' << x.second.first << ' ' << x.second.second << std::endl;
		}
	}
	
	{
		std::pair<double, int> p = {2.0, 3};
		std::cout << Sqr(p).first << std::endl;
		
		std::map<double, double> m = {{4.0, 5.0}};
		std::cout << Sqr(m)[4.0] << std::endl;
		
		std::vector<int> v = {1, 2, 3};
		std::cout << Sqr(v)[2] << std::endl;
		
		std::map<int, std::vector<int>> arr1 = {{1, {2,3}}};
		std::cout << Sqr(arr1).size() << std::endl;
		
		std::map<std::pair<int, int>, std::vector<int>> arr12 = {{{1 ,2},{3,4,5}}};
		std::cout << Sqr(arr12).size() << std::endl;
		
		std::map<std::map<int, int>, int> arr13 = {{{{1, 2}}, 4}};
		std::cout << Sqr(arr13).size() << std::endl;
		
		std::vector<std::pair<int, int>> arr2 = {{1,2}};
		arr2 = Sqr(arr2);
		std::cout << arr2[0].second << std::endl;
		
		std::vector<std::map<int,int>> arr3 = {{{1,1}}};
		std::cout << Sqr(arr3).size() << std::endl;
		
		std::vector<std::vector<int>> arr31 = {{1,2}, {3, 4}};
		std::cout << Sqr(arr31)[0][0] << std::endl;
		
		std::pair<int, std::vector<std::map<int ,int>>> arr4 = {3,{{{1 ,2}}}};
		std::cout << Sqr(arr4).first << std::endl;
		
		std::pair<std::map<int, int>, std::vector<int>> arr41 = {{{2,3}}, {4, 5}};
		std::cout << Sqr(arr41).second[0] << std::endl;
	}
	
	return 0;
}
