#pragma once

// Interface for CharacterSegmentation to CharacterRecognition
// Vec �ȿ��� ������ �������
// ���� �ȿ��� Character�� ����
// insert(data, height, width) �Լ��� Segmentation �� character �Ѱ��� String�� �Ϸķ� ������ ��, height �� width�� ���� 
// ������ ������ ��쿡�� CharacterMatrix�� space ������ 1�� ����
// ���� ������ ä��� ���ؼ��� goNext()�� ȣ����

#define MATRIX_HEIGHT 12
#define MATRIX_WIDTH 12

#include <vector>
#include <list>
#include <string>

using std::string;

typedef struct{

	// space = 1, character = 0
	int space = 0;
	// Character Data Matrix 0 or 1
	int data[MATRIX_HEIGHT][MATRIX_WIDTH] = { 0 };

}ChracterMatrix;


struct SegmentationArr {

	SegmentationArr();

	//Node vector
	std::vector<std::list<ChracterMatrix> > vec;
	int now = 0;

	// insert data
	void insert(string data, int height, int width);

	
	// next sentence
	void goNext();

};