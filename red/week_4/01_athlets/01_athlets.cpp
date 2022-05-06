// user includes
#include "test_runner.h"
// system includes
#include <iostream>
#include <list>
#include <vector>

static const size_t MAX_ATHLETS = 100000;

class Athlets {
public:
  Athlets() {
    iters.resize(MAX_ATHLETS + 1, l.end());
  }
  void PlaceBefore(size_t ath1, size_t ath2) {
      iters[ath1] = l.insert(iters[ath2], ath1);
  }
  std::list<size_t> l;
private:
  std::vector<std::list<size_t>::iterator> iters;
};

void TestSimple() {
  Athlets a;
  a.PlaceBefore(42, 0);
  a.PlaceBefore(17, 42);
  a.PlaceBefore(13, 0);
  a.PlaceBefore(123, 42);
  a.PlaceBefore(5, 13);
  
  auto it = a.l.begin();
  ASSERT_EQUAL(*(it++), 17);
  ASSERT_EQUAL(*(it++), 123);
  ASSERT_EQUAL(*(it++), 42);
  ASSERT_EQUAL(*(it++), 5);
  ASSERT_EQUAL(*(it++), 13);
  ASSERT(it == a.l.end());
}

void TestSimpler() {
  Athlets a;
  a.PlaceBefore(42, 10);
  a.PlaceBefore(17, 10);
  a.PlaceBefore(13, 10);
  a.PlaceBefore(123, 10);
  a.PlaceBefore(5, 10);
  
  auto it = a.l.begin();
  ASSERT_EQUAL(*(it++), 42);
  ASSERT_EQUAL(*(it++), 17);
  ASSERT_EQUAL(*(it++), 13);
  ASSERT_EQUAL(*(it++), 123);
  ASSERT_EQUAL(*(it++), 5);
  ASSERT(it == a.l.end());
}

void TestSimplest() {
  Athlets a;
  a.PlaceBefore(42, 10);
  a.PlaceBefore(10, 42);
  a.PlaceBefore(13, 10);
  a.PlaceBefore(123, 10);
  a.PlaceBefore(5, 10);
  
  auto it = a.l.begin();
  ASSERT_EQUAL(*(it++), 13);
  ASSERT_EQUAL(*(it++), 123);
  ASSERT_EQUAL(*(it++), 5);
  ASSERT_EQUAL(*(it++), 10);
  ASSERT_EQUAL(*(it++), 42);
  ASSERT(it == a.l.end());
}

void TestAll() {
  TestRunner tr;
  tr.RunTest(TestSimple, "TestSimple");
  tr.RunTest(TestSimpler, "TestSimpler");
  tr.RunTest(TestSimplest, "TestSimplest");
}

int main() {
//  TestAll(); return 0;
  
  size_t num = 0;
  std::cin >> num;
  
  Athlets a;
  
  for (size_t i = 0; i < num; ++i) {
    size_t athelet1 = 0, athelet2 = 0;
    std::cin >> athelet1 >> athelet2;
  
    a.PlaceBefore(athelet1, athelet2);
  }
  
  for (auto item : a.l) {
    std::cout << item << "\n";
  }
  
  return 0;
}
