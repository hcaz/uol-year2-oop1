#include "stdafx.h"
#include "Matrix.h"
#include <sstream> // stringstream
#include <iostream> // cout, cerr
#include <fstream> // ifstream
#include <istream>
#include <math.h>

Matrix::Matrix()
{
	_M = 1;
	_N = 1;

	_data = new double[_M*_N];

	for (int x = 0; x < _M*_N; x++)
	{
		_data[x] = 0;
	}

}

Matrix::Matrix(int sizeR, int sizeC, double* input_data)
{
	_M = sizeR;
	_N = sizeC;

	_data = new double[_M*_N];

	for (int x = 0; x < _M*_N; x++)
	{
		_data[x] = input_data[x];
	}
}
Matrix::Matrix(int sizeR, int sizeC, Matrix* input_data)
{
	_M = sizeR;
	_N = sizeC;

	_data2 = new Matrix[_M*_N];

	for (int x = 0; x < _M*_N; x++)
	{
		_data2[x] = input_data[x];
	}
}
//copy constructor
Matrix::Matrix(const Matrix& m)
{
	_M = m._M;
	_N = m._N;

	_data = new double[_M*_N];

	for (int i = 0; i < _M*_N; i++)
	{
		_data[i] = m._data[i];
	}
}

//operator overloads
Matrix Matrix::operator+(const Matrix& other)
{
	Matrix temp;
	temp._M = other._M;
	temp._N = other._N;

	temp._data = new double[temp._M*temp._N];

	for (int x = 0; x < (temp._M*temp._N); x++)
	{
		temp._data[x] = this->_data[x] + other._data[x];
	}

	return temp;
}

Matrix Matrix::operator=(const Matrix& other)
{
	//delete existing _data information - as we are going to replace it with 'other._data'
	delete[] _data;
	_M = other._M;
	_N = other._N;

	//reserve memory for new array
	_data = new double[_M*_N];

	//'this' pointer refers to the current object
	for (int x = 0; x < (_M*_N); x++)
	{
		this->_data[x] = other._data[x];
	}

	return *this;
}


//functions
int Matrix::getM()
{
	return _M;
}

int Matrix::getN()
{
	return _N;
}

double Matrix::get(int i, int j)
{
	return _data[(i*_N) + j];
}

Matrix Matrix::getMatrix(int i, int j)
{
	return _data2[(i*_N) + j];
}

double Matrix::update(int i, int j, int x, int y, int value)
{
	Matrix tmp = _data2[(i*_N) + j];
	tmp.update(x, y, value);
	_data2[(i*_N) + j] = tmp;
	return true;
}
double Matrix::update(int i, int j, int value)
{
	_data[(i*_N) + j] = value;
	return true;
}

double Matrix::getSSD(int i, int j, Matrix& tmp2)
{
	Matrix tmp = _data2[(i*_N) + j];
	int M = tmp.getM();
	int value = 0;
	for (int y = 0; y < M - 1; y++) {
		for (int x = 0; x < M - 1; x++) {
			int val = tmp.get(x, y);
			int val2 = tmp2.get(x, y);
			int diff = val - val2;
			int squared = abs(diff * diff);
			value = value + squared;
		}
	}
	return value;
}

double* Matrix::getData()
{
	return _data;
}

Matrix::~Matrix()
{
	delete[] _data;
}