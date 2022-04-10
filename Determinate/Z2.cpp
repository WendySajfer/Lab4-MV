#include <iostream>
#include "windows.h"
#include <vector>
#include "string"
#include <cmath>

using namespace std;

class Matrix {
private:
	vector<vector<double>> matrix;
	vector<int> width_form;
	int m = 0, n = 0;

	void Format() {
		width_form.clear();
		int width, buf_width, width_null;
		string str_width;
		width = 1;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				str_width = to_string(matrix[j][i]);
				for (int i = str_width.size() - 1; i >= 0; i--) {
					if (str_width[i] == '0' || str_width[i] == ',') {
						str_width.erase(i);
					}
					else break;
				}
				buf_width = str_width.size();
				if (width < buf_width) width = buf_width;
			}
			width_form.push_back(width);
		}
	}
	void Size() {
		m = matrix.size();
		n = matrix[0].size();
		for (int i = 1; i < m; i++) {
			if (matrix[i].size() != n) {
				n = 0;
				break;
			}
		}
	}
public:
	void Input_Matrix(int m, int n)
	{
		double number;
		vector<double> str_matrix;
		cout << "Enter the [" << m << "," << n << "] matrix:" << endl;
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				cin >> number;
				str_matrix.push_back(number);
			}
			matrix.push_back(str_matrix);
			str_matrix.clear();
		}
	}
	void Output_Matrix() {
		Size();
		if (n == 0 || m == 0) {
			return;
		}
		Format();
		cout << "A = " << endl;
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				cout.width(width_form[j]);
				cout << matrix[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
	void Output_INV_RES() {
		Size();
		if (n == 0 || m == 0) {
			return;
		}
		Format();
		cout << "A' = " << endl;
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				cout.width(width_form[j]);
				cout << matrix[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
	void Output_INV() {
		Size();
		if (n == 0 || m == 0) {
			return;
		}
		Format();
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				cout.width(width_form[j]);
				cout << matrix[i][j] << " ";
				if (j == n - (n/2) - 1) cout << "| ";
			}
			cout << endl;
		}
		cout << endl;
	}
	vector<vector<double>> get_Matrix() {
		return matrix;
	}
	void set_INV(vector<vector<double>> inv) {
		matrix = inv;
	}
};

class Determinant {
private:
	vector<vector<double>> matrix_det;
	double det = 0;
	Matrix M;

	double Accur(double n) {
		double buf = abs(n);
		if (buf != 0) {
			if (fmod(buf, 0.001) < 1) {
				n = round(n * 1000) / 1000;
			}
		}
		return n;
	}
	double Det_2x(vector<vector<double>> matrix_2x) {
		double right = matrix_2x[0][0] * matrix_2x[1][1];
		double left = matrix_2x[0][1] * matrix_2x[1][0];
		return Accur(right - left);
	}
	double Det_3x(vector<vector<double>> matrix_3x) {
		double right = 0;
		double buf = 1, buf1 = 1;
		for (int i = 0; i < 3; i++) {
			buf *= matrix_3x[i][i];
		}
		right += buf;
		buf = 1;
		for (int i = 0; i < 3; i++) {
			if (i + 1 < 3) {
				buf *= matrix_3x[i][i + 1];
				buf1 *= matrix_3x[i + 1][i];
			}
			else {
				buf *= matrix_3x[i][0];
				buf1 *= matrix_3x[0][i];
			}
		}
		right += buf;
		right += buf1;
		double left = 0;
		buf = matrix_3x[0][2] * matrix_3x[2][0] * matrix_3x[1][1];
		left += buf;
		buf = matrix_3x[0][1] * matrix_3x[1][0] * matrix_3x[2][2];
		left += buf;
		buf = matrix_3x[1][2] * matrix_3x[2][1] * matrix_3x[0][0];
		left += buf;
		return Accur(right - left);
	}
	double Det_mx(vector<vector<double>> matrix_mx) {
		if (matrix_mx.size() == 2) return Det_2x(matrix_mx);
		else if (matrix_mx.size() == 3) return Det_3x(matrix_mx);
		else {
			double det_mx = 0;
			for (int i = 0; i < matrix_mx.size(); i++) {
				vector<vector<double>> buf_m = matrix_mx;
				buf_m.erase(buf_m.begin());
				int buf_size = buf_m.size();
				for (int buf_index = 0; buf_index < buf_size; buf_index++) {
					buf_m[buf_index].erase(buf_m[buf_index].begin() + i);
				}
				if (i % 2 == 0) {
					det_mx += matrix_mx[0][i] * Det_mx(buf_m);
				}
				else det_mx -= matrix_mx[0][i] * Det_mx(buf_m);
			}
			return Accur(det_mx);
		}
	}
public:
	void Input_Det_Matrix(vector<vector<double>> matrix) {
		matrix_det = matrix;
	}
	void Decision() {
		det = Det_mx(matrix_det);
		cout << "det(A) = " << det << endl;
	}
	double get_det() {
		return det;
	}
};

class Inverse_Matrix {
private:
	vector<vector<double>> matrix_inv;
	vector<vector<double>> X;
	Matrix M;
	void Accur_str(int str_index) {
		double buf;
		vector<double> str_inv = matrix_inv[str_index];
		for (int i = 0; i < str_inv.size(); i++) {
			buf = abs(str_inv[i]);
			if (buf != 0) {
				if (fmod(buf, 0.001) < 1) {
					str_inv[i] = round(str_inv[i] * 1000) / 1000;
				}
			}
		}
		matrix_inv[str_index] = str_inv;
	}
	double Accur(double n) {
		double buf = abs(n);
		if (buf != 0) {
			if (fmod(buf, 0.001) < 1) {
				n = round(n * 1000) / 1000;
			}
		}
		return n;
	}
	void Output_INV() {
		M.set_INV(matrix_inv);
		M.Output_INV();
	}
	void Diagonal(int str_index) {
		double diff;
		vector<double> str_inv = matrix_inv[str_index];

		diff = 1 / str_inv[str_index];
		for (int i = str_index; i < str_inv.size(); i++) {
			str_inv[i] *= diff;
		}
		matrix_inv[str_index] = str_inv;
		Accur_str(str_index);
	}
	void Sub_buttom_Str(int str1_index, int str2_index, int null_index) {
		double diff;
		vector<double> str1_inv = matrix_inv[str1_index];
		vector<double> str2_inv = matrix_inv[str2_index];

		diff = str2_inv[null_index] / str1_inv[null_index];
		for (int i = 0; i < str1_inv.size(); i++) {
			str2_inv[i] -= (str1_inv[i] * diff);
		}
		matrix_inv[str2_index] = str2_inv;
		Accur_str(str2_index);
	}
	void Sub_top_Str(int str1_index, int str2_index, int null_index) {
		double diff;
		vector<double> str1_inv = matrix_inv[str1_index];
		vector<double> str2_inv = matrix_inv[str2_index];

		diff = str1_inv[null_index] / str2_inv[null_index];
		for (int i = null_index; i < str2_inv.size(); i++) {
			str1_inv[i] -= (str2_inv[i] * diff);
		}
		matrix_inv[str1_index] = str1_inv;
		Accur_str(str1_index);
	}
public:
	void Input_Inv(vector<vector<double>> matrix_A) {
		vector<vector<double>> matrix_E;
		for (int i = 0; i < matrix_A.size(); i++) {
			vector<double> str_E;
			for (int j = 0; j < matrix_A.size(); j++) {
				if (i == j) str_E.push_back(1);
				else str_E.push_back(0);
			}
			matrix_E.push_back(str_E);
		}
		matrix_inv = matrix_A;
		for (int i = 0; i < matrix_A.size(); i++) {
			for (int j = 0; j < matrix_E.size(); j++) {
				matrix_inv[i].push_back(matrix_E[i][j]);
			}
		}
	}
	void Decision() {
		for (int i = 1; i < matrix_inv.size(); i++) {
			for (int j = 0; j < i; j++) {
				if (matrix_inv[i][j] != 0) {
					Sub_buttom_Str(j, i, j);
					Output_INV();
				}
			}
		}
		for (int i = 0; i < matrix_inv.size(); i++) {
			if (matrix_inv[i][i] != 1) {
				Diagonal(i);
				Output_INV();
			}
		}
		for (int i = 0; i < matrix_inv.size() - 1; i++) {
			for (int j = i + 1; j < matrix_inv.size(); j++) {
				if (matrix_inv[i][j] != 0) {
					Sub_top_Str(i, j, j);
					Output_INV();
				}
			}
		}
	}
	void Rezult() {
		vector<vector<double>> matrix_inv_result;
		for (int i = 0; i < matrix_inv.size(); i++) {
			vector<double> str_res;
			for (int j = (matrix_inv[0].size() / 2); j < matrix_inv[0].size(); j++) {
				str_res.push_back(matrix_inv[i][j]);
			}
			matrix_inv_result.push_back(str_res);
		}
		Matrix M_Result;
		M_Result.set_INV(matrix_inv_result);
		M_Result.Output_INV_RES();
	}
};


class Task {
private:
	Matrix M;
	Determinant Det;
	Inverse_Matrix Inv_M;
	int m;
	void Create_Matrix() {
		M.Input_Matrix(m, m);
		Det.Input_Det_Matrix(M.get_Matrix());
	}
public:
	void Determinant_Task() {
		cout << "Input the size of the matrix." << endl << "m = ";
		cin >> m;
		if (m < 2 || m > 100) {
			cout << "Incorrect size of the matrix." << endl;
			return;
		}
		Create_Matrix();
		M.Output_Matrix();
		Det.Decision();
	}
	void Inverse_Task() {
		cout << "Input the size of the matrix." << endl << "m = ";
		cin >> m;
		if (m < 2 || m > 49) {
			cout << "Incorrect size of the matrix." << endl;
			return;
		}
		Create_Matrix();
		M.Output_Matrix();
		Det.Decision();
		if (Det.get_det() == 0) {
			cout << "The matrix hasn't inverse." << endl;
			return;
		}
		Inv_M.Input_Inv(M.get_Matrix());
		Inv_M.Decision();
		Inv_M.Rezult();
	}
};

int main() {
	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	int ans, exit = 1;
	while (exit == 1) {
		Task T;
		cout << "1.Determinant" << endl << "2.Inverse_Task" << endl << "3.Exit" << endl << "Choose a way:" << endl;
		cin >> ans;
		switch (ans)
		{
		case 1:
			T.Determinant_Task();
			break;
		case 2:
			T.Inverse_Task();
			break;
		case 3:
			exit = 0;
			break;
		default:
			cout << "This task does not exist" << endl;
			break;
		}
	}
	system("pause");
	return 0;
}

/*
0.47 1 0.67 -0.32
1 0.17 -0.25 0.54
0.55 0.43 0.36 1
-0.11 0.35 1 -0.74

1 2 0 1
-1 -3 3 -1
0 4 -10 2.0
1 -1 2 -1
*/