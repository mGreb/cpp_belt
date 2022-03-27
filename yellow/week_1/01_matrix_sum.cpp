#include <vector>
#include <iostream>
#include <stdexcept>

class Matrix {
	std::vector<std::vector<int>> matrix;
	static void CheckDimNeg(int row, int col) {
		if (row < 0 || col < 0)
			throw std::out_of_range("");
	}
	void CheckDim(int row, int col) const {
		CheckDimNeg(row, col);
		if (row >= matrix.size() || col >= matrix[0].size())
			throw std::out_of_range("");
	}
	[[nodiscard]] bool IsEmpty() const {
		int rows = GetNumRows(), cols = GetNumColumns();
		return rows == 0 || cols == 0;
	}
public:
	Matrix() = default;
	Matrix(int rows, int cols) {
		CheckDimNeg(rows, cols);
		matrix.resize(rows);
		for (auto &row : matrix)
			row.resize(cols);
	}
	void Reset(int rows, int cols) {
		CheckDimNeg(rows, cols);
		matrix.resize(rows);
		for (auto &row : matrix)
			row.assign(cols, 0);
	}
	[[nodiscard]] int At(int row, int col) const {
		CheckDim(row, col);
		return matrix[row][col];
	}
	int& At(int row, int col) {
		CheckDim(row, col);
		return matrix[row][col];
	}
	[[nodiscard]] size_t GetNumRows() const {return matrix.size();};
	[[nodiscard]] size_t GetNumColumns() const {
		return !matrix.empty() ? matrix[0].size() : 0;
	};
	
	bool operator==(const Matrix& m) const {
		if (IsEmpty() && m.IsEmpty())
			return true;
		return this->matrix == m.matrix;
	}
	Matrix operator+(const Matrix &m) const {
		if (IsEmpty() && m.IsEmpty())
			return {};
		int rows = GetNumRows(), cols = GetNumColumns();
		int m_rows = m.GetNumRows(), m_cols = m.GetNumColumns();
		if (cols != m_cols || rows != m_rows)
			throw std::invalid_argument("");
		Matrix res = *this;
		for (size_t i = 0; i < rows; ++i)
			for (size_t j = 0; j < cols; ++j)
				res.matrix[i][j] += m.matrix[i][j];
		return res;
	}
};

std::ostream& operator<<(std::ostream& s, const Matrix& m) {
	const int rows = m.GetNumRows(), cols = m.GetNumColumns();
	s << rows << " " << cols << std::endl;
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols-1; ++j)
			s << m.At(i, j) << " ";
		s << m.At(i, cols-1) << std::endl;
	}
	return s;
}

std::istream& operator>>(std::istream& s, Matrix& m) {
	int rows = 0, cols = 0;
	s >> rows >> cols;
	m.Reset(rows, cols);
	for (int i = 0; i < rows; ++i)
		for (int j = 0; j < cols; ++j)
			s >> m.At(i, j);
	return s;
}

/*
3 5
6 4 -1 9 8
12 1 2 9 -5
-4 0 12 8 6
+
3 5
5 1 0 -8 23
14 5 -6 6 9
8 0 5 4 1
=
3 5
11 5 -1 1 31
26 6 -4 15 4
4 0 17 12 7
 * */

int main() {
	Matrix one;
	Matrix two;
	
	std::cin >> one >> two;
	std::cout << one + two << (one == two) << (one == one) << std::endl;
	
	Matrix t = one + two;
	t.Reset(10, 10);
	
	Matrix x;
	
	return 0;
}
