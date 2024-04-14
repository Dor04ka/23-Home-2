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

	// ����������� ������ �������, ������� � �������� �������� � �������
	Matrix() {
		cout << "������� ���-�� �����: ";
		cin >> rows;
		cout << "������ ���-�� ��������: ";
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

	// ����������� ������� ��������� ������� (��������� 0)
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

	// ����������� �������, ����������� �� �����
	Matrix(const string& fileName) {
		ifstream fin;
		fin.open(fileName);
		if (!fin.is_open()) {
			cout << "������ �������� �����!" << endl;
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



	// ���������� ������� � �������
	void readConsole() {
		for (size_t i = 0; i < rows; i++) {
			for (size_t j = 0; j < cols; j++) {
				cin >> m[i][j];
			}
		}
	}

	// ����� �������� ������� � �������
	void printConsole() {
		for (size_t i = 0; i < rows; i++) {
			for (size_t j = 0; j < cols; j++) {
				cout << m[i][j] << " ";
			}
			cout << endl;
		}
	}

	// ���������� ������� �� �����
	void readFile(const string& fileName) {
		ifstream fin;
		fin.open(fileName);
		if (!fin.is_open()) {
			cout << "������ �������� �����!" << endl;
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

	// ����� �������� ������� � ����
	void printFile(const string& fileName) {
		ofstream fout;
		fout.open(fileName);
		if (!fout.is_open()) {
			cout << "������ �������� �����!" << endl;
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



	// ���������� ������ �� �������
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

	// ���������� ������ � �������
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



	// �������� ������������
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

	// �������� 2� ������
	Matrix operator + (const Matrix& other) {
		//if (typeid(m[0][0]).name() != typeid(other.m[0][0]).name()) {
			//cout << "�������� ����������. ������� ������ �����." << endl;
		//}
		if (this->rows != other.rows || this->cols != other.cols) {
			cout << "�������� ����������. ������� ������ ������������." << endl;
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

	// ��������� 2� ������
	Matrix operator - (const Matrix& other) {
		//if (typeid(m[0][0]).name() != typeid(other.m[0][0]).name()) {
			//cout << "�������� ����������. ������� ������ �����." << endl;
		//}
		if (this->rows != other.rows || this->cols != other.cols) {
			cout << "�������� ����������. ������� ������ ������������." << endl;
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

	// ��������� 2� ������
	Matrix operator * (const Matrix& other) {
		if (this->cols != other.rows) cout << "������� ����������� ������." << endl;
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

	// ��������� ������� �� ������
	Matrix operator * (const double a) {
		for (size_t i = 0; i < rows; i++) {
			for (size_t j = 0; j < cols; j++) {
				m[i][j] *= a;
			}
		}
		return *this;
	}

	// ����������� ����� �������� ������� �������
	static Matrix ZeroMatrix(size_t rows, size_t cols) {
		Matrix res(rows, cols);
		return res;
	}

	// ����������� ����� �������� ��������� �������
	static Matrix OneMatrix(size_t rows, size_t cols) {
		if (rows != cols)
			cout << "������� �� �������� ����������!";
		else {
			Matrix res(rows, cols);
			for (size_t i = 0; i < res.rows; i++) {
				res.m[i][i] = 1;
			}
			return res;
		}
	}



	// ����������
	~Matrix() {
		for (size_t i = 0; i < rows; i++) {
			delete[] m[i];
		}
		delete[] m;
	}

};

int main() {

	setlocale(LC_ALL, "ru");

	//cout << "������ ������� ������� 3�3:" << endl;
	//Matrix<int> ma = Matrix<int>::ZeroMatrix(3, 3);
	//cout << ma;

	//cout << "������ ��������� ������� 4�4." << endl;
	//Matrix<double> m = Matrix<double>::OneMatrix(4, 4);
	//cout << m;

	Matrix<int> a("file.txt");
	cout << a;

}