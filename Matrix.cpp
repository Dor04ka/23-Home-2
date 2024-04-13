#include <iostream>
#include <typeinfo>
#include <fstream>
#include <string>
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



	// оператор присваивания
	Matrix& operator = (const Matrix& other) {
		this->cols = other.cols;
		this->rows = other.rows;
		if (this->m != nullptr) {
			for (size_t i = 0; i < rows; i++) {
				delete[] this->m[i];
			}
			delete[] this->m;
		}
		this->m = new T * [rows];
		for (size_t i = 0; i < rows; i++) {
			m[i] = new T[cols];
		}
		for (size_t i = 0; i < other.rows; i++) {
			for (size_t j = 0; j < other.cols; j++) {
				this->m[i][j] = other.m[i][j];
			}
		}
		return *this;
	}

	// сложение 2х матриц
	Matrix operator + (const Matrix& other) {
		//if (typeid(m[0][0]).name() != typeid(other.m[0][0]).name()) {
			//cout << "Операция невозможна. Матрицы разных типов." << endl;
		//}
		if (this->rows != other.rows || this->cols != other.cols) {
			cout << "Операция невозможна. Матрицы разных размерностей." << endl;
		}
		else {
			Matrix res(rows, cols);
			for (size_t i = 0; i < rows; i++) {
				for (size_t j = 0; j < cols; j++) {
					res.m[i][j] = m[i][j] + other.m[i][j];
				}
			}
			return res;
		}
	}

	// вычитание 2х матриц
	Matrix operator - (const Matrix& other) {
		//if (typeid(m[0][0]).name() != typeid(other.m[0][0]).name()) {
			//cout << "Операция невозможна. Матрицы разных типов." << endl;
		//}
		if (this->rows != other.rows || this->cols != other.cols) {
			cout << "Операция невозможна. Матрицы разных размерностей." << endl;
		}
		else {
			Matrix res(rows, cols);
			for (size_t i = 0; i < rows; i++) {
				for (size_t j = 0; j < cols; j++) {
					res.m[i][j] = m[i][j] - other.m[i][j];
				}
			}
			return res;
		}
	}

	// умножение 2х матриц
	Matrix operator * (const Matrix& other) {
		if (this->cols != other.rows) cout << "Матрицы перемножить нельзя." << endl;
		else {
			Matrix res(rows, other.cols);
			for (size_t i = 0; i < rows; i++) {
				for (size_t j = 0; j < other.cols; j++) {
					res.m[i][j] = 0;
					for (size_t k = 0; k < cols; k++) {
						res.m[i][j] += m[i][k] * other.m[k][j];
					}
				}
			}
			return res;
		}
	}

	// умножение матрицы на скаляр
	Matrix operator * (const double a) {
		for (size_t i = 0; i < rows; i++) {
			for (size_t j = 0; j < cols; j++) {
				m[i][j] *= a;
			}
		}
		return *this;
	}

	// статический метод создания нулевой матрицы
	static Matrix ZeroMatrix(size_t rows, size_t cols) {
		Matrix res(rows, cols);
		return res;
	}

	// статический метод создания единичной матрицы
	static Matrix OneMatrix(size_t rows, size_t cols) {
		if (rows != cols)
			cout << "Матрица не является квадратной!";
		else {
			Matrix res(rows, cols);
			for (size_t i = 0; i < res.rows; i++) {
				res.m[i][i] = 1;
			}
			return res;
		}
	}



	// деструктор
	~Matrix() {
		for (size_t i = 0; i < rows; i++) {
			delete[] m[i];
		}
		delete[] m;
	}

};

int main() {

	setlocale(LC_ALL, "ru");

	Matrix<int> ma = Matrix<int>::ZeroMatrix(3, 3);
	cout << ma;

	Matrix<double> m = Matrix<double>::OneMatrix(4, 4);
	cout << m;
}