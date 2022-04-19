#include "test_runner.h"


template <typename T>
class Table {
public:
	Table(size_t n_x_, size_t n_y_) {
		data.resize(n_x_, std::vector<T>(n_y_));
	}
	std::pair<size_t, size_t> Size() const {
		if (data.empty())
			return {0, 0};
		else
			if (data[0].empty())
				return {0, 0};
		return {data.size(), data[0].size()};
	}
	std::vector<T>& operator[](size_t i) {
		return data[i];
	}
	const std::vector<T>& operator[](size_t i) const {
		return data[i];
	}
	void Resize(size_t n_x, size_t n_y) {
		data.resize(n_x);
		for (auto &d : data)
			d.resize(n_y);
	}
private:
	std::vector<std::vector<T>> data;
};

void TestTable() {
  Table<int> t(1, 1);
  ASSERT_EQUAL(t.Size().first, 1u);
  ASSERT_EQUAL(t.Size().second, 1u);
  t[0][0] = 42;
  ASSERT_EQUAL(t[0][0], 42);
  t.Resize(3, 4);
  ASSERT_EQUAL(t.Size().first, 3u);
  ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestTable);
  return 0;
}
