#pragma once

// Interface for CharacterSegmentation to CharacterRecognition
// Vec 안에는 문장이 담겨있음
// 문장 안에는 Character를 담음
// insert(data, height, width) 함수에 Segmentation 한 character 한개를 String에 일렬로 저장한 후, height 와 width를 넣음 
// 공백을 전달할 경우에는 CharacterMatrix의 space 변수를 1로 만듬
// 다음 문장을 채우기 위해서는 goNext()를 호출함

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