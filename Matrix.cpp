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
		cols = 0;
		rows = 0;
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



	// перегрузка чтения из консоли (А ОНО НУЖНО ВООБЩЕ?????)
	friend istream& operator >> (istream& os, Matrix& m) {
		cout << "Введите кол-во строк: ";
		os >> m.rows;
		cout << "Ведите кол-во столбцов: ";
		os >> m.cols;
		m.m = new T * [m.rows];
		for (size_t i = 0; i < m.rows; i++) {
			m.m[i] = new T[m.cols];
		}
		for (size_t i = 0; i < m.rows; i++) {
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

	// перегрузка чтения из файла
	friend ifstream& operator >> (ifstream& fileName, Matrix& m) {
		fileName >> m.rows;
		fileName >> m.cols;
		m.m = new T * [m.rows];
		for (size_t i = 0; i < m.rows; i++) {
			m.m[i] = new T[m.cols];
		}
		for (size_t i = 0; i < m.rows; i++) {
			for (int j = 0; j < m.cols; j++) {
				fileName >> m.m[i][j];
			}
		}
		return fileName;
	}

	// перегрузка вывода в файл 
	friend ofstream& operator << (ofstream& fileName, const Matrix& m) {
		fileName << m.rows << " " << m.cols << endl;
		for (size_t i = 0; i < m.rows; i++) {
			for (size_t j = 0; j < m.cols; j++) {
				fileName << m.m[i][j] << " ";
			}
			fileName << endl;
			
		}
		return fileName;
	}


	// проверка равенства двух матриц 
	bool operator == (const Matrix& other) {
		if (this->cols != other.cols || this->rows != other.rows) {
			return false;
		}
		else {
			bool flag = true;
			for (size_t i = 0; i < rows; i++) {
				for (size_t j = 0; j < cols; j++) {
					if (this->m[i][j] != other.m[i][j]) {
						flag = false;
						break;
					}
				}
			}
			return flag;
		}

	}

	// равенство матрицы и скаляра
	bool operator == (const double a) {
		if (this->cols != this->rows) return false;
		else {
			bool flag = true;
			for (size_t i = 0; i < rows; i++) {
				for (size_t j = 0; j < cols; j++) {
					if (i == j && m[i][j] != a) {
						flag = false;
						break;
					}
					else if (i != j && m[i][j] != 0) {
						flag = false;
						break;
					}
				}
			}
			return flag;
		}
	}

	// проверка неравенства двух матриц 
	bool operator != (const Matrix& other) {
		if (this->rows == other.rows && this->cols == other.cols) {     // если размерность одинаковая
			long flag = 0;
			for (size_t i = 0; i < rows; i++) {
				for (size_t j = 0; j < cols; j++) {
					if (this->m[i][j] == other.m[i][j]) flag++;
				}
			}
			if (flag == rows * cols) return false;
			else return true;
		}
		else return true;        // в противном случае
	}

	// проверка неравенства матрицы и скаляра
	bool operator != (const double a) {
		if (this->cols != this->rows) return true;
		else {
			bool flag = false;
			for (size_t i = 0; i < rows; i++) {
				for (size_t j = 0; j < cols; j++) {
					if (i == j && m[i][j] != a) {
						flag = true;
						break;
					}
					else if (i != j && m[i][j] != 0) {
						flag = true;
						break;
					}
				}
			}
			return flag;
		}
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
			throw "Матрицы невозможно сложить.";
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
			throw "Матрицы невозможно вычесть";
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
		if (this->cols != other.rows) throw "Матрицы невозможно перемножить.";
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
		if (rows == cols) {
			Matrix res(rows, cols);
			for (size_t i = 0; i < res.rows; i++) {
				res.m[i][i] = 1;
			}
			return res;
		}
		else {
			throw "Матрица не является квадратной.";
		}
	}



	// Минор матрицы с удаленными строкой и столбцом
	Matrix Minor(size_t row, size_t col) {
		Matrix minor(rows - 1, cols - 1);
		size_t minorRow = 0;
		for (size_t i = 0; i < rows; i++) {
			if (i == row)
				continue;
			size_t minorCol = 0;
			for (size_t j = 0; j < cols; j++) {
				if (j == col)
					continue;
				minor.m[minorRow][minorCol] = m[i][j];
				minorCol++;
			}
			minorRow++;
		}
		return minor;
	}

	// определитель матрицы
	double det() {
		if (rows != cols)
			throw "Матрица не является квадратной.";
		else {
			if (this->rows == 1)
				return m[0][0];
			else if (this->rows == 2)
				return m[0][0] * m[1][1] - m[0][1] * m[1][0];
			else {
				double res = 0;
				for (size_t j = 0; j < cols; j++) {
					Matrix minor = Minor(0, j);
					short sign = 0;
					if (j % 2 == 0)
						sign = 1;
					else
						sign = -1;
					res += sign * minor.det() * m[0][j];
				}
				return res;
			}
		}
	}

	// транспонированная матрица
	Matrix trans() {
		if (this->rows == this->cols) {
			Matrix mat(rows, cols);
			for (size_t i = 0; i < rows; i++) {
				for (size_t j = 0; j < cols; j++) {
					mat.m[i][j] = m[j][i];
				}
			}
			return mat;
		}
		else {
			throw "Матрица не является квадратной.";
		}
	}

	// перегрузка !
	Matrix operator ! () {
		// делаем копию, чтобы не менять содержание искомой матрицы
		Matrix copy(rows, cols);
		for (size_t i = 0; i < rows; i++) {
			for (size_t j = 0; j < cols; j++) {
				copy.m[i][j] = m[i][j];
			}
		}
		double det = copy.det();
		if (rows != cols || det == 0)
			throw "Обратной матрицы не существует.";
		else {
			// матрица миноров, состоящая из определителей соответсвующих миноров
			Matrix minor(rows, cols);
			for (size_t i = 0; i < rows; i++) {
				for (size_t j = 0; j < cols; j++) {
					short sign;
					if ((i + j) % 2 == 0)
						sign = 1;
					else
						sign = -1;
					minor.m[i][j] = sign * (copy.Minor(i, j)).det();
				}
			}
			minor = minor.trans();
			for (size_t i = 0; i < rows; i++) {
				for (size_t j = 0; j < cols; j++) {
					minor.m[i][j] *= (1 / det);
				}
			}
			return minor;

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

	//cout << "Пример записи матрицы в файл." << endl;
	//Matrix<double> a;
	//ofstream fout;
	//string path = "file.txt";
	//fout.open(path);
	//fout << a;
	//fout.close();
	//Matrix<double> b("file.txt");
	//cout << b;

	//cout << "Пример считывания матрицы из файла" << endl;
	//string path = "file.txt";
	//ifstream fin;
	//fin.open(path);
	//Matrix<double> a("file.txt");
	//fin >> a;
	//cout << a;

	//Matrix<int> a;
	//cin >> a;
	//Matrix<int> b;
	//cin >> b;
	//try {
		//cout << a + b;
	//}
	//catch (const char* error) {
		//cout << error << endl;
	//}

	cout << "Пример нахождения обратной матрицы" << endl;
	Matrix<double>a;
	cin >> a;
	try {
		Matrix<double> b = !a;
		cout << b;
		cout << b * a;
	}
	catch (const char* error) {
		cout << error << endl;
	}
	
}
