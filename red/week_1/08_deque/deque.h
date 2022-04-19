// #pragma once

// system includes
#include <vector>
#include <stdexcept>

template <typename T>
class Deque {
public:
	Deque() = default;
	[[nodiscard]] bool Empty() const { return front.empty() && back.empty(); }
	[[nodiscard]] std::size_t Size() const { return front.size() + back.size(); }
	
	      T& operator[](std::size_t index)        { return Get(index); }
	const T& operator[](std::size_t index) const  { return Get(index); }
	
	      T& At(std::size_t index)       { CheckIndex(index); return Get(index); }
	const T& At(std::size_t index) const { CheckIndex(index); return Get(index); }
	
	      T& Front()       { if (!front.empty()) return front.back(); else return back.front(); }
	const T& Front() const { if (!front.empty()) return front.back(); else return back.front(); }
	
	      T& Back()       { if (!back.empty()) return back.back(); else return front.front(); }
	const T& Back() const { if (!back.empty()) return back.back(); else return front.front(); }
	
	void PushBack(const T &val) { back.push_back(val); }
	void PushFront(const T &val) { front.push_back(val); }
private:
	std::vector<T> front, back;
	void CheckIndex(std::size_t index) {
		if (index > front.size() + back.size() - 1)
			throw std::out_of_range("deque index out of range: " +
									std::to_string(index) + " out of " +
									std::to_string(front.size() + back.size()));
	}
	void CheckIndex(std::size_t index) const {
		if (index > front.size() + back.size() - 1)
			throw std::out_of_range("deque index out of range: " +
									std::to_string(index) + " out of " +
									std::to_string(front.size() + back.size()));
	}
	T& Get(std::size_t index) {
		if (index < front.size())
			return front[front.size() - index - 1];
		else
			return back[index - front.size()];
	}
	const T& Get(std::size_t index) const {
		if (index < front.size())
			return front[front.size() - index - 1];
		else
			return back[index - front.size()];
	}
};
