// 문자 인식용 함수 util

#include <string>
#include <algorithm>
#include "character_recognition.h"

using std;
using std::string;

/*
MATRIX AND LAYER
class Matrix {
public:
	int row;
	int col;
	double mat[][];

public:
	Matrix();
	Matrix(int row, int col);
	Matrix(string data, int row, int col);
	EditMatrix(string data);
};

class Layer {
public:
	int size;
	int matRow;
	int matCol;
	Matrix[] layerData;

public:
	Layer();
	Layer(int size, int matRolw, int matCol);
};
*/

Matrix::Matrix() {
}

Matrix::Matrix(int irow, int icol) {

	this->row = irow;
	this->col = icol;

	mat = new double[row][col];

}

Matrix::Matrix(string idata, int irow, int icol) {

	this->row = irow;
	this->col = icol;

	mat = new double[irow][icol];

	int i = 0;
	
	for (int m = 0; m < irow; m++) {
		for (int n = 0; n < icol; n++) {
			mat[m][n] = idata.at(i);
			i++;
		}
	}

}

int Matrix::EditMatrix(string data) {

	int i = 0;

	for (int m = 0; m < this->row; m++) {
		for (int n = 0; n < this->col; n++) {
			mat[m][n] = idata.at(i);
			i++;
		}
	}

	return 0;

}

Layer::Layer() {
}

Layer::Layer(int isize, int imatRow, int imatCol) {

	this->size = isize;
	this->matRow = imatRow;
	this->matCol = imatCol;

	layerData = new Matrix*[size]();
	for (int i = 0; i < isize; i++) {

		Matrix* matrix = new Matrix[imatRow][imatCol]();
		layerData[i] = matrix;

	}

}

Layer::~Layer() {

	for (int i = 0; i < this->size; i++) {
		free(this->layerData[i]);
	}

	free(this->layerData);

}

Weight::Weight() {
}



Weight::~Weight() {


}

Model::Model() {
}

Model::Model(int isize, Weight* w, Bias* b) {

	this->size = isize;

	thils->weight = Weight;
	this->bias = b;

}

int Matadd(Matrix* A, Matrix* B, Matrix* outMat) {

	// Matrix size match error
	if ((A->row == B->row) && (B->row == outMat->row) && (A->row == outMat->row)){}
	else return 1;
	if ((A->col == B->col) && (B->col == outMat->col) && (A->col == outMat->col)){}
	else return 1;

	for (int m = 0; m < this->row; m++) {
		for (int n = 0; n < this->col; n++) {
			outMat->mat[m][n] = A->mat[m][n] + B->mat[m][n];
		}
	}

	return 0;

}

int Matadd(Matrix* A, float B, Matrix* outMat) {

	// Matrix size match error
	if ((A->row != outMat->row) || (A->col != outMat->col)) return 1;

	for (int m = 0; m < A->row; m++) {
		for (int n = 0; n < A->col; n++) {
			outMat->mat[m][n] = A->mat[m][n] + B->mat[m][n];
		}
	}

	return 0;
}

int Matmul(Matrix* A, Matrix* B, Matrix* outMat) {

	if ((A->col != B->row) || (A->col != outMat->col) || (B->row != outMat->row)) return 1;




}
int Conv(Matrix* input, Matrix* kernel, Matrix* outMat) {



}

Matrix* ReLU(Matrix* input, Matrix* outMat) {

	for (int m = 0; m < this->row; m++) {
		for (int n = 0; n < this->col; n++) {
			outMat->mat[m][n] = max(0, input->mat[m][n]);
		}
	}

	return out;
}

int LayerConv(Layer* input, Layer* output) {



}

int CharRecognition(Matrix* input, Matrix* output, Model model) {

	Layer layerOut1 = new Layer(int SIZE_LAYER1, int ROW_LAYER1, int COL_LAYER1);
	Layer layerOut2 = new Layer(int SIZE_LAYER2, int ROW_LAYER2, int COL_LAYER2);

	for()



}

char MatrixToChar(Matrix* input);

