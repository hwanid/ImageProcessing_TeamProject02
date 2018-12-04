// 문자 인식용 함수 util

#include <iostream>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include "character_recognition.h"

using namespace std;
using std::string;


int initialize_CapitalAlphabet(ConvWeight* cweight1, ConvWeight* cweight2, FlatWeight* fweight, Bias* bias3) {

	GetWeightFromCSV(1, 1, cweight1, FILTER_ROW_SIZE, FILTER_COL_SIZE, 1, LAYER1_FILTER);
	GetWeightFromCSV(1, 2, cweight2, FILTER_ROW_SIZE, FILTER_COL_SIZE, LAYER1_FILTER, LAYER2_FILTER);

	GetWeightFromCSV(1, fweight, L2_POOL_ROW, L2_POOL_COL, LAYER2_FILTER, ONEHOT_BIG);
	GetBiasFromCSV(1, bias3, ONEHOT_BIG);

	return 0;
}

int initialize_SmallAlphabet(ConvWeight* cweight1, ConvWeight* cweight2, FlatWeight* fweight, Bias* bias3) {

	GetWeightFromCSV(2, 1, cweight1, FILTER_ROW_SIZE, FILTER_COL_SIZE, 1, LAYER1_FILTER);
	GetWeightFromCSV(2, 2, cweight2, FILTER_ROW_SIZE, FILTER_COL_SIZE, LAYER1_FILTER, LAYER2_FILTER);

	GetWeightFromCSV(2, fweight, L2_POOL_ROW, L2_POOL_COL, LAYER2_FILTER, ONEHOT_BIG);
	GetBiasFromCSV(2, bias3, ONEHOT_BIG);

	return 0;
}

int initialize_Number(ConvWeight* cweight1, ConvWeight* cweight2, FlatWeight* fweight, Bias* bias3) {

	GetWeightFromCSV(3, 1, cweight1, FILTER_ROW_SIZE, FILTER_COL_SIZE, 1, LAYER1_FILTER);
	GetWeightFromCSV(3, 2, cweight2, FILTER_ROW_SIZE, FILTER_COL_SIZE, LAYER1_FILTER, LAYER2_FILTER);

	GetWeightFromCSV(3, fweight, L2_POOL_ROW, L2_POOL_COL, LAYER2_FILTER, ONEHOT_BIG);
	GetBiasFromCSV(3, bias3, ONEHOT_BIG);

	return 0;
}

// send prob[26]
int CharRecognition_CapitalAlphabet(float* input, float* prob, ConvWeight* cweight1, ConvWeight* cweight2, FlatWeight* fweight, Bias* bias3) {

	/*
	// Weight data, bias Data 받기
	ConvWeight cweight1;
	ConvWeight cweight2;
	FlatWeight fweight;
	Bias bias3;

	GetWeightFromCSV(1, &cweight1, FILTER_ROW_SIZE, FILTER_COL_SIZE, 1, LAYER1_FILTER);
	GetWeightFromCSV(1, &cweight2, FILTER_ROW_SIZE, FILTER_COL_SIZE, LAYER1_FILTER, LAYER2_FILTER);
	
	// Capital Letter Bias
	GetWeightFromCSV(&fweight, L2_POOL_ROW, L2_POOL_COL, LAYER2_FILTER, ONEHOT_BIG);
	GetBiasFromCSV(&bias, L2_POOL_ROW, L2_POOL_COL, LAYER2_FILTER, ONEHOT_BIG);
	*/


	Layer* L1 = new Layer;
	Layer* L1_pooled = new Layer;

	L1->imgs = (float*)calloc(LAYER1_FILTER * L1_CONV_TOTAL, sizeof(float));
	L1_pooled->imgs = (float*)calloc(LAYER1_FILTER * L1_POOL_TOTAL, sizeof(float));
	
	float from_input_tmp;
	int output_tmp;

	// L1 시작

	// Weight와 곱연산하기
	
	for (int channelRow = 0; channelRow < IMAGE_ROW - FILTER_ROW_SIZE + 1; channelRow++) {
		for (int channelCol = 0; channelCol < IMAGE_COL - FILTER_COL_SIZE + 1; channelCol++) {
			for (int filterRow = 0; filterRow < FILTER_ROW_SIZE; filterRow++) {
				for (int filterCol = 0; filterCol < FILTER_COL_SIZE; filterCol++) {
					for (int channel = 0; channel < 1; channel++) {
						for (int filter = 0; filter < LAYER1_FILTER; filter++) {
							// input = input IMG ... output = L1_CONV
							L1->imgs[channelCol + L1_CONV_ROW * channelRow + L1_CONV_TOTAL * filter] +=
								cweight1->data[filter + (LAYER1_FILTER * channel) + (LAYER1_FILTER * 1 * filterCol) + (LAYER1_FILTER * 1 * FILTER_ROW_SIZE * filterRow)]
								* input[IMAGE_ROW * (channelRow + filterRow) + (channelCol + filterCol)];
						}
					}
				}
			}
		}
	}



	// Relu 연산하기
	for (int channel = 0; channel < 1; channel++) {
		for (int filter = 0; filter < LAYER1_FILTER; filter++) {
			for (int channelRow = 0; channelRow < L1_CONV_ROW; channelRow++) {
				for (int channelCol = 0; channelCol < L1_CONV_COL; channelCol++) {
					// input = L1_CONV ... output = Relu(L1_CONV)
					L1->imgs[L1_CONV_TOTAL * filter + L1_CONV_ROW * channelRow + channelCol] = max(float(0), L1->imgs[L1_CONV_TOTAL * filter + L1_CONV_ROW * channelRow + channelCol]);

				}
			}
		}
	}

	// Maxpool 하기
	for (int channel = 0; channel < 1; channel++) {
		for (int filter = 0; filter < LAYER1_FILTER; filter++) {
			for (int channelRow = 0; channelRow < L1_CONV_ROW - L1_POOL_KSIZE + L1_POOL_STRIDES; channelRow += L1_POOL_STRIDES) {
				for (int channelCol = 0; channelCol < L1_CONV_COL - L1_POOL_KSIZE + L1_POOL_STRIDES; channelCol += L1_POOL_STRIDES) {
					// input = L1_CONV ... output = L1_POOL
					L1_pooled->imgs[L1_POOL_TOTAL * filter + L1_POOL_ROW * (channelRow / L1_POOL_STRIDES) + (channelCol / L1_POOL_STRIDES)] =
					max(
						// 주의 완전하지 않은 MAXPOOL, KSIZE = 2 인 경우의 MAXPOOL
						max(L1->imgs[L1_CONV_TOTAL * filter + L1_CONV_ROW * channelRow + channelCol], L1->imgs[L1_CONV_TOTAL * filter + L1_CONV_ROW * channelRow + (channelCol + 1)]),
						max(L1->imgs[L1_CONV_TOTAL * filter + L1_CONV_ROW * (channelRow + 1) + channelCol], L1->imgs[L1_CONV_TOTAL * filter + L1_CONV_ROW * (channelRow + 1) + (channelCol + 1)])
					);
				}
			}
		}
	}

	cout << "test 3" << endl;
	for (int i = 0; i < LAYER1_FILTER * L1_POOL_TOTAL; i++) {
		cout << L1_pooled->imgs[i] << "   ";
	}
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;

	// L2 시작

	Layer* L2 = new Layer;
	Layer* L2_pooled = new Layer;

	L2->imgs = (float*)calloc(LAYER2_FILTER * L2_CONV_TOTAL, sizeof(float));
	L2_pooled->imgs = (float*)calloc(LAYER2_FILTER * L2_POOL_TOTAL, sizeof(float));

	// Weight와 곱연산하기
	for (int channelRow = 0; channelRow < IMAGE_ROW - FILTER_ROW_SIZE + 1; channelRow++) {
		for (int channelCol = 0; channelCol < IMAGE_COL - FILTER_COL_SIZE + 1; channelCol++) {
			for (int filterRow = 0; filterRow < FILTER_ROW_SIZE; filterRow++) {
				for (int filterCol = 0; filterCol < FILTER_COL_SIZE; filterCol++) {
					for (int channel = 0; channel < LAYER1_FILTER; channel++) {
						for (int filter = 0; filter < LAYER2_FILTER; filter++) {
							// input = L1_POOL ... output = L2_CONV
							L2->imgs[channelCol + L2_CONV_ROW * channelRow + L2_CONV_TOTAL * filter] +=
								//W2
								cweight2->data[filter + (LAYER2_FILTER * channel) + (LAYER2_FILTER * LAYER1_FILTER * filterCol) + (LAYER2_FILTER * LAYER1_FILTER * FILTER_ROW_SIZE * filterRow)]
								//L1_POOL
								* L1_pooled->imgs[L1_POOL_ROW * (channelRow + filterRow) + (channelCol + filterCol)];
						}
					}
				}
			}
		}
	}


	cout << "test 4" << endl;
	for (int i = 0; i < 100; i++) {
		cout << L2->imgs[i] << "   ";
	}
	cout << endl;


	// Relu 연산하기
	for (int channel = 0; channel < LAYER1_FILTER; channel++) {
		for (int filter = 0; filter < LAYER2_FILTER; filter++) {
			for (int channelRow = 0; channelRow < L2_CONV_ROW; channelRow++) {
				for (int channelCol = 0; channelCol < L2_CONV_COL; channelCol++) {
					// input = L2_CONV ... output = Relu(L2_CONV)
					L2->imgs[L2_CONV_TOTAL * filter + L2_CONV_ROW * channelRow + channelCol] = max((float)0, L2->imgs[L2_CONV_TOTAL * filter + L2_CONV_ROW * channelRow + channelCol]);

				}
			}
		}
	}

	cout << endl;
	cout << "test 5" << endl;
	for (int i = 0; i < 1000; i++) {
		cout << L2->imgs[i] << "   ";
	}
	cout << endl;

	// Maxpool 하기
	for (int channel = 0; channel < LAYER1_FILTER; channel++) {
		for (int filter = 0; filter < LAYER2_FILTER; filter++) {
			for (int channelRow = 0; channelRow < L2_CONV_ROW - L2_POOL_KSIZE + L2_POOL_STRIDES; channelRow += L2_POOL_STRIDES) {
				for (int channelCol = 0; channelCol < L2_CONV_COL - L2_POOL_KSIZE + L2_POOL_STRIDES; channelCol += L2_POOL_STRIDES) {
					// input = L2_CONV ... output = L2_POOL
					L2_pooled->imgs[L2_POOL_TOTAL * filter + L2_POOL_ROW * (channelRow / L2_POOL_STRIDES) + (channelCol / L2_POOL_STRIDES)] =
						max(
							// 주의 완전하지 않은 MAXPOOL, KSIZE = 2 인 경우의 MAXPOOL
							max(L2->imgs[L2_CONV_TOTAL * filter + L2_CONV_ROW * channelRow + channelCol], L2->imgs[L2_CONV_TOTAL * filter + L2_CONV_ROW * channelRow + (channelCol + 1)]),
							max(L2->imgs[L2_CONV_TOTAL * filter + L2_CONV_ROW * (channelRow + 1) + channelCol], L2->imgs[L2_CONV_TOTAL * filter + L2_CONV_ROW * (channelRow + 1) + (channelCol + 1)])
						);
				}
			}
		}
	}


	cout << "test 6" << endl;
	for (int i = 0; i < 100; i++) {
		cout << L2_pooled->imgs[i] << "   ";
	}
	cout << endl;

	// 일렬 데이터로 펼치기
	// L2_pooled = 10 * 10 * LAYER2_FILLTER, 완료


	// W3 곱 + B3

	float tmp;
	for (int hot = 0; hot < ONEHOT_BIG; hot++) {
		prob[hot] = 0;
		tmp = 0;
		for (int iter = 0; iter < L2_POOL_TOTAL * LAYER2_FILTER; iter++) {
			tmp += (L2_pooled->imgs[iter] * fweight->data[iter]);
		}
		tmp += bias3->data[hot];

		prob[hot] = tmp;
	}

	/*
	float max = 0;
	int maxnum = 0;

	for (int hot = 0; hot < ONEHOT_BIG; hot++) {
		if (max < prob[hot]) {
			max = prob[hot];
			maxnum = hot;
		}
	}
	*/

	return 0;

}

int GetWeightFromCSV(int m, int n, ConvWeight* cweight, int filterrow, int filtercol, int in, int out) {

	FILE* fp;

	switch (m)
	{
	case 1:
		switch (n) {
		case 1: 
			fp = fopen("savedCapital_W1.csv", "r");
			break;
		case 2: 
			fp = fopen("savedCapital_W2.csv", "r");
		}
		break;
	case 2:
		switch (n) {
		case 1:
			fp = fopen("savedSmall_W1.csv", "r");
			break;
		case 2:
			fp = fopen("savedSmall_W2.csv", "r");
		}
		break;
	case 3:
		switch (n) {
		case 1:
			fp = fopen("savedNumber_W1.csv", "r");
			break;
		case 2:
			fp = fopen("savedNumber_W2.csv", "r");
		}
		break;
	}

	int size = filterrow * filtercol*in*out;
	float data;
	cweight->data = (float*)calloc(size, sizeof(float));


	for (int a = 0; a < size; a++) {
		fscanf(fp, "%f", &data);
		
		cweight->data[a] = data;
	}

	fclose(fp);

	return 0;

}

int GetWeightFromCSV(int m, FlatWeight* fweight, int matrow, int matcol, int out, int onehot) {

	FILE* fp;

	switch (m) {
	case 1:
		fp = fopen("savedCapital_W3.csv", "r");
		break;
	case 2:
		fp = fopen("savedSmall_W3.csv", "r");
		break;
	case 3:
		fp = fopen("savedNumber_W3.csv", "r");
		break;
	}

	int size = matrow * matcol * out * onehot;
	float data;
	fweight->data = (float*)calloc(size, sizeof(float));

	for (int a = 0; a < size; a++) {
		fscanf(fp, "%f", &data);
		fweight->data[a] = data;
	}
	
	return 0;

}

int GetBiasFromCSV(int chartype, Bias* bias, int onehot) {

	FILE* fp;

	switch (chartype) {
	case 1:
		fp = fopen("savedCapital_B3.csv", "r");
		break;
	case 2:
		fp = fopen("savedSmall_B3.csv", "r");
		break;
	case 3:
		fp = fopen("savedNumber_B3.csv", "r");
		break;
	}

	int size = onehot;
	float data;
	bias->data = (float*)calloc(size, sizeof(float));

	for (int a = 0; a < size; a++) {
		fscanf(fp, "%f", &data);
		bias->data[a] = data;
	}

	fclose(fp);

	return 0;
}