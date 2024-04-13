#include <iostream>
#include <typeinfo>
#include <fstream>
using namespace std;
template <typename T>
class Matrix {

private:
	size_t rows, cols;
	T** m;

public:

	// конструктор пустой матрицы
	Matrix() {
		rows = 0;
		cols = 0;
		m = nullptr;
	}

	// конструктор матрицы заданного размера (заполнена 0)
	Matrix(size_t rows, size_t cols) {
		this->rows = rows;
		this->cols = cols;
		m = new T * [rows];
		for (size_t i = 0; i < rows; i++) {
			m[i] = new T[cols];
		}
		for (size_t i = 0; i < rows; i++) {
			for (size_t j = 0; j < cols; j++) {
				m[i][j] = 0;
			}
		}
	}

	// перегрузка чтения из консоли
	friend istream& operator >> (istream& os, Matrix& m) {
		m.m = new T * [m.rows];
		for (size_t i = 0; i < m.rows; i++) {
			m.m[i] = new T[m.cols];
			for (size_t j = 0; j < m.cols; j++) {
				os >> m.m[i][j];
			}
		}
		cout << endl;
		return os;
	}

	// перегрузка вывода в консоль
	friend ostream& operator << (ostream& os, const Matrix& m) {
		for (size_t i = 0; i < m.rows; i++) {
			for (size_t j = 0; j < m.cols; j++) {
				os << m.m[i][j] << " ";
			}
			os << endl;
		}
		cout << endl;
		return os;
	}
};

int main() {
	Matrix<int> a(3, 4);
	cin >> a;
	cout << a;
}