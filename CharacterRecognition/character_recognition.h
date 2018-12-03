#pragma once

#include <string>

// Layer1
#define SIZE_LAYER1;
#define ROW_LAYER1;
#define COL_LAYER1;
// Layer2
#define SIZE_LAYER2;
#define ROW_LAYER2;
#define COL_LAYER2;

using std;
using std::string;

class Matrix {

public:
	int row;
	int col;
	float* mat;

public:
	Matrix();
	Matrix(int row, int col);
	Matrix(string data, int row, int col);
	int EditMatrix(string data);
};

class Layer {
public:
	int size;
	int matRow;
	int matCol;
	Matrix* layerData[];

public:
	Layer();
	~Layer();
	Layer(int size, int matRolw, int matCol);
};

class Weight {

public:
	int size;
	int matRow;
	int matCol;
	Matrix* weightData[];

public:
	Weight();
	~Weight();
	Weight(int size, int matRow, int matCol);
	int SetWeight
	

};

class Bias {

public:
	int size;
	float* data;

};

class Model {

public:
	int size;
	Weight* weight[];
	Bias* bias[];

public:
	Model();
	Model(int size, Weight*, Bias*);

};


int Matadd(Matrix* A, Matrix* B, Matrix* outMat);
int Matadd(Matrix* A, float B, Matrix* outMat);
int Matmul(Matrix* A, Matrix* B, Matrix* outMat);
int Conv(Matrix* input, Matrix* kernel, Matrix* outMat);
int ReLU(Matrix* input, Matrix* outMat);
int LayerConv(Layer* input, Layer* output);
int CharRecognition(Matrix* input, Matrix* output, Layer Layer1, Layer Layer2);
char MatrixToChar(Matrix* input);

