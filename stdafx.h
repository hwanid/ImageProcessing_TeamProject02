// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
#include <vector>
#include <stack>

using namespace cv;
using namespace std;


typedef struct OneSentence {
	vector<String> vector_character;
	vector<int> vector_row_size;
	vector<int> vector_col_size;
} OneSentence;

int labeling(Mat image, Point, Point);

OneSentence findOneCharacter(Mat image);

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
