#pragma once
class Matrix
{

private:
	int _M, _N;
	double *_data;

public:
	Matrix();
	Matrix(int sizeR, int sizeC, double* input_data);
	//copy constructor
	Matrix(const Matrix& m);
	//operator overloads
	Matrix operator+(const Matrix& other);
	Matrix operator=(const Matrix& other);
	Matrix operator/(const Matrix& other);
	Matrix operator*(const Matrix& other);
	Matrix operator-(const Matrix& other);
	//functions
	int getM();
	int getN();
	double get(int i, int j);
	Matrix getBlock(int startR, int endR, int startC, int endC);
	Matrix add(const Matrix& other);
	double* getData();
	~Matrix();
};