#pragma once
class Matrix
{

private:
	int _M, _N, _C;
	double *_data;
	Matrix *_data2;

public:
	Matrix();
	Matrix(int sizeR, int sizeC, double* input_data);
	Matrix(int sizeR, int sizeC, Matrix* input_data);
	//copy constructor
	Matrix(const Matrix& m);
	//operator overloads
	Matrix operator+(const Matrix& other);
	Matrix operator=(const Matrix& other);
	//functions
	int getM();
	int getN();
	double get(int i, int j);
	Matrix getMatrix(int i, int j);
	double update(int i, int j, int x, int y, int value);
	double update(int i, int j, int value);
	double getSSD(int i, int j, Matrix& compare);
	double* getData();
	~Matrix();
};