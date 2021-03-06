// ImageProcessing_TeamProject02.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"


int main()
{
	Mat image = imread("C:\\test-en-2.jpg", IMREAD_UNCHANGED);

	if (image.empty())
	{
		cout << "Could not open or find the image" << endl;
		return -1;
	}

	Point small;
	small.x = 0;
	small.y = 0;

	Point big;
	big.x = image.cols; // image.cols;
	big.y = image.rows; // image.rows;

	OneSentence a = findOneCharacter(image);

	//vector<String> answer = findOneCharacter(image);

	imshow("data", image);
	waitKey(0);

	return 0;
}

