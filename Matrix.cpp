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

	// конструктор пустой матрицы, размеры и элементы задаются с консоли
	Matrix() {
		cout << "Введите кол-во строк: ";
		cin >> rows;
		cout << "Ведите кол-во столбцов: ";
		cin >> cols;
		m = new T * [rows];
		for (size_t i = 0; i < rows; i++) {
			m[i] = new T[cols];
		}
		for (size_t i = 0; i < rows; i++) {
			for (size_t j = 0; j < cols; j++) {
				cin >> m[i][j];
			}
		}
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

	// конструктор матрицы, считываемой из файла
	Matrix(const string& fileName) {
		ifstream fin;
		fin.open(fileName);
		if (!fin.is_open()) {
			cout << "Ошибка открытия файла!" << endl;
		}
		else {
			fin >> rows;
			fin >> cols;
			this->rows = rows;
			this->cols = cols;
			this->m = new T * [rows];
			for (size_t i = 0; i < rows; i++) {
				m[i] = new T[cols];
			}
			for (size_t i = 0; i < rows; i++) {
				for (int j = 0; j < cols; j++) {
					fin >> m[i][j];
				}
			}
		}
		fin.close();
	}



	// считывание матрицы с консоли
	void readConsole() {
		for (size_t i = 0; i < rows; i++) {
			for (size_t j = 0; j < cols; j++) {
				cin >> m[i][j];
			}
		}
	}

	// вывод заданной матрицы в консоль
	void printConsole() {
		for (size_t i = 0; i < rows; i++) {
			for (size_t j = 0; j < cols; j++) {
				cout << m[i][j] << " ";
			}
			cout << endl;
		}
	}

	// считывание матрицы из файла
	void readFile(const string& fileName) {
		ifstream fin;
		fin.open(fileName);
		if (!fin.is_open()) {
			cout << "Ошибка открытия файла!" << endl;
		}
		else {
			fin >> rows;
			fin >> cols;
			this->rows = rows;
			this->cols = cols;
			this->m = new T * [rows];
			for (size_t i = 0; i < rows; i++) {
				m[i] = new T[cols];
			}
			for (size_t i = 0; i < rows; i++) {
				for (int j = 0; j < cols; j++) {
					fin >> m[i][j];
				}
			}
		}
		fin.close();
	}

	// вывод заданной матрицы в файл
	void printFile(const string& fileName) {
		ofstream fout;
		fout.open(fileName);
		if (!fout.is_open()) {
			cout << "Ошибка открытия файла!" << endl;
		}
		else {
			fout << rows << " " << cols << endl;
			for (size_t i = 0; i < rows; i++) {
				for (size_t j = 0; j < cols; j++) {
					fout << m[i][j] << " ";
				}
				fout << endl;
			}
		}
		fout.close();
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

	//cout << "Пример нулевой матрицы 3х3:" << endl;
	//Matrix<int> ma = Matrix<int>::ZeroMatrix(3, 3);
	//cout << ma;

	//cout << "Пример единичной матрицы 4х4." << endl;
	//Matrix<double> m = Matrix<double>::OneMatrix(4, 4);
	//cout << m;

	Matrix<int> a("file.txt");
	cout << a;

}