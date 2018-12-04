#pragma once

#include <string>

// filter setting
#define FILTER_ROW_SIZE 3
#define FILTER_COL_SIZE 3
#define FILTER_TOTAL_SIZE 9

// number of filter setting
#define LAYER1_FILTER 32
#define LAYER2_FILTER 64

// label
#define ONEHOT_BIG 26
#define ONEHOT_SMALL 26
#define ONEHOT_NUM 10

// input image
#define IMAGE_ROW 28
#define IMAGE_COL 28
#define IMAGE_TOTAL_SIZE 784

// L1 CONV size
#define L1_CONV_ROW 26
#define L1_CONV_COL 26
#define L1_CONV_TOTAL 676

// L1 POOL size
#define L1_POOL_KSIZE 2
#define L1_POOL_STRIDES 2
#define L1_POOL_ROW 13
#define L1_POOL_COL 13
#define L1_POOL_TOTAL 169

// L2 CONV size
#define L2_CONV_ROW 11
#define L2_CONV_COL 11
#define L2_CONV_TOTAL 121

// L2 POOL size
#define L2_POOL_KSIZE 2
#define L2_POOL_STRIDES 1
#define L2_POOL_ROW 10
#define L2_POOL_COL 10
#define L2_POOL_TOTAL 100

using std;
using std::string;

class Layer {

public:
	float* imgs;

};

class Bias {

public:
	int size;
	float* data;

};

class ConvWeight {

public:
	int filterrow, filtercol, in, out;
	float* data;

};

class FlatWeight {

public:
	int size;
	float* data;
};

int initialize_CapitalAlphabet(ConvWeight* cweight1, ConvWeight* cweight2, FlatWeight* fweight, Bias* bias3);
int initialize_SmallAlphabet(ConvWeight* cweight1, ConvWeight* cweight2, FlatWeight* fweight, Bias* bias3);
int initialize_Number(ConvWeight* cweight1, ConvWeight* cweight2, FlatWeight* fweight, Bias* bias3);
int CharRecognition_CapitalAlphabet(float* input, float* prob, ConvWeight* cweight1, ConvWeight* cweight2, ConvWeight* fweight, Bias* bias3);
int GetWeightFromCSV(int m, int n, ConvWeight* cweight, int filterrow, int filtercol, int in, int out);
int GetWeightFromCSV(int m, FlatWeight* fweight, int matrow, int matcol, int out, int onehot);
int GetBiasFromCSV(int chartype, Bias* bias, int onehot);