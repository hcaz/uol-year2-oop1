#include "stdafx.h"
#include "Matrix.h"
#include <sstream> // stringstream
#include <iostream> // cout, cerr
#include <fstream> // ifstream
#include <istream>
#include <math.h>
#include "windows.h"

using namespace std;

// Input data are provided in .txt format and can be converted to .pgm files for visualization
// Download (free) ImageJ for plotting images in .pgm format
// http://rsb.info.nih.gov/ij/download.html

// Reads .txt file representing an image of R rows and C Columns stored in filename 
// and converts it to a 1D array of doubles of size R*C
// Memory allocation is performed inside readTXT
double* readTXT(char *fileName, int sizeR, int sizeC);

// Converts a 1D array of doubles of size R*C to .pgm image of R rows and C Columns 
// and stores .pgm in filename
// Use Q = 255 for greyscale images and Q=1 for binary images.
void WritePGM(char *filename, double *data, int sizeR, int sizeC, int Q);


int main()
{
	// This part will show you how to use the two functions.

	//M and N represent the number of rows and columns in the image,
	//e.g. for task 1: logo_with_noise and logo_shuffled, M = 512, N = 512


	int M = 512; int chunk = 16;
	int chunkSize = M / chunk;
	// input_data is a pointer to a 1D array of M*N doubles stored in heap. Memory allocation is performed 
	// inside readTXT. readTXT will read an image (in .pgm format) of size MxN and will  store the result in input_data.
	// once you're done with data DO NOT forget to delete the memory as in the end of this main() function
	double* input_data = 0;
	double* input_dataUnshuffles = 0;

	cout << endl;
	cout << "Image size : " << M << "x" << M << " Chunk size : " << chunkSize << "x" << chunkSize << endl;
	cout << "Starting -------------------------------------------" << endl;

	// .pgm image is stored in inputFileName, change the path in your program appropriately
	char* inputFileName = "shuffled_logo.txt";
	input_data = readTXT(inputFileName, M, M);

	char* inputFileNameUnshuffles = "unshuffled_logo_noisy.txt";
	input_dataUnshuffles = readTXT(inputFileNameUnshuffles, M, M);

	if (input_data != 0) {
		//Create matrix
		int chunks = chunk * chunk;
		int chunkTotal = chunkSize * chunkSize;
		Matrix* dataTotal = new Matrix[chunks];
		double* data = new double[chunkTotal];
		for (int y = 0; y < chunkTotal; y++)
		{
			data[y] = 0;
		}
		for (int x = 0; x < chunks; x++)
		{
			Matrix shuffledTMP(chunkSize, chunkSize, data);
			dataTotal[x] = shuffledTMP;
		}
		Matrix shuffled(chunk, chunk, dataTotal);
		Matrix noisey(chunk, chunk, dataTotal);
		delete[] data;
		delete[] dataTotal;
		//go through data
		int count = 0;
		for (int y = 0; y < M; y++) {
			for (int x = 0; x < M; x++) {
				double currentX = 0;
				double currentY = 0;
				if (x > 16) { currentX = floor(x / chunkSize); }
				if (y > 16) { currentY = floor(y / chunkSize); }
				int localX = x - (currentX * chunkSize);
				int localY = y - (currentY * chunkSize);
				//get current chunk in array
				shuffled.update(currentX, currentY, localX, localY, input_data[count]);
				count++;
			}
		}

		Matrix tmp = shuffled.getMatrix(1, 1);
		int rndVal = tmp.get(1, 1);
		cout << endl << endl << "=========" << rndVal << "=========" << endl << endl;

		// writes data back to .pgm file stored in outputFileName
		char* outputFileName = "logo_restored.pgm";
		// Use Q = 255 for greyscale images and 1 for binary images.
		int Q = 255;
		WritePGM(outputFileName, input_data, M, M, Q);

		delete[] input_data;
		delete[] input_dataUnshuffles;
	}

	cout << "Done, type `y` to open image, `n` to exit (and press enter)  -------------------------------------------" << endl;

	char option = getchar();

	if (option == 'y') {
		ShellExecute(0, L"open", L"logo_restored.pgm", 0, 0, SW_SHOW);
	}

	return 0;
}


// Read .txt file with image of size RxC, and convert to an array of doubles
double* readTXT(char *fileName, int sizeR, int sizeC)
{
	double* data = new double[sizeR*sizeC];
	int i = 0;
	ifstream myfile(fileName);
	if (myfile.is_open())
	{

		while (myfile.good())
		{
			if (i>sizeR*sizeC - 1) break;
			myfile >> *(data + i);
		
			//cout << *(data+i) << ' '; // This line display the converted data on the screen, you may comment it out. 
			i++;
		}
		myfile.close();

		return data;
	}
	else
	{
		cout << "Unable to open file" << fileName << endl;

		return 0;
	}
}

// convert data from double to .pgm stored in filename
void WritePGM(char *filename, double *data, int sizeR, int sizeC, int Q)
{

	int i;
	unsigned char *image;
	ofstream myfile;

	image = (unsigned char *) new unsigned char[sizeR*sizeC];

	// convert the integer values to unsigned char

	for (i = 0; i<sizeR*sizeC; i++)
		image[i] = (unsigned char)data[i];

	myfile.open(filename, ios::out | ios::binary | ios::trunc);

	if (!myfile) {
		cout << "Can't open file: " << filename << endl;
		exit(1);
	}

	myfile << "P5" << endl;
	myfile << sizeC << " " << sizeR << endl;
	myfile << Q << endl;

	myfile.write(reinterpret_cast<char *>(image), (sizeR*sizeC)*sizeof(unsigned char));

	if (myfile.fail()) {
		cout << "Can't write image " << filename << endl;
		exit(0);
	}

	myfile.close();

	delete[] image;

}