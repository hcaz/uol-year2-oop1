#pragma once

class Matrix
{
public:
	Matrix();
	~Matrix();
	Matrix(int sizeR, int sizeC, double* input_data);
	const double get(int i, int j);
	const double set(int i, int j, double val);

private:
	int _M, _N;
	double* _data;
};