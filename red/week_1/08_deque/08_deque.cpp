#include "deque.h"
#include "test_runner.h"

int main() {
	
	{
		Deque<int> deque;
		ASSERT_EQUAL(deque.Empty(), true);
		deque.PushFront(10);
		ASSERT_EQUAL(deque.Empty(), false);
		AssertEqual(deque[0], 10);
		try {
			deque.At(1);
		} catch (std::out_of_range &e) {
			std::cout << "ALL OK: " << e.what() << "\n";
		}
		deque.PushBack(11);
		ASSERT_EQUAL(deque[1], 11);
		deque.PushBack(12);
		ASSERT_EQUAL(deque[2], 12);
	}
	
	{
		Deque<int> deque;
		deque.PushBack(1);
		deque.PushBack(2);
		deque.PushBack(3);
		deque.PushBack(4);
		deque.PushBack(5);
		deque.PushBack(6);
		deque.PushFront(1);
		deque.PushFront(2);
		deque.PushFront(3);
		deque.PushFront(4);
		deque.PushFront(5);
		deque.PushFront(6);
		for (int i = 0; i< deque.Size(); ++i) {
			std::cout << deque[i] << '\n';
		}
		std::cout << "at 5: " << deque.At(5) << "\n";
		std::cout << deque.Front() << ' ' << deque.Back();
	}
	
	{
		Deque<int> deque;
		deque.PushBack(10);
		ASSERT_EQUAL(deque.Front(), 10);
	}
	
	return 0;
}