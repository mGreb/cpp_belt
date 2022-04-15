#pragma once


enum class Comparison {
	Less,
	LessOrEqual,
	Greater,
	GreaterOrEqual,
	Equal,
	NotEqual
};


template <class T>
bool Compare(Comparison comp, const T &left, const T &right) {
	switch (comp) {
		case Comparison::Less:
			return left < right;
		case Comparison::LessOrEqual:
			return left < right || left == right;
		case Comparison::Greater:
			return left > right;
		case Comparison::GreaterOrEqual:
			return left > right || left == right;
		case Comparison::Equal:
			return left == right;
		case Comparison::NotEqual:
			return left != right;
		default:
			return false;
	}
}
