#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>

using namespace cv;
using namespace std;


class Pixel {
public:
	int x;
	int y;

	Pixel() {

	}

	Pixel(int x1, int y1) {
		x = x1;
		y = y1;
	}

	void setPixel(int x1, int y1) {
		x = x1;
		y = y1;
	}

	void setPixelX(int x1) { x = x1; }
	void setPixelY(int y1) { y = y1; }
};

bool Compare(Pixel, Pixel);

Mat makeBox(Mat *, Mat *);
void partitioning(Mat *);

int main(int argc, char** argv)
{
	/*
	clock_t t1, t2;

	String imageName[4] = { "C:\\1.jpg", "C:\\2.jpg", "C:\\3.jpg", "C:\\4.jpg" };

	Mat image[4];
	Mat image_gray[4];


	t1 = clock();

	for (int i = 0; i < 4; i++) {
	image[i] = imread(imageName[i], IMREAD_UNCHANGED);

	if (image[i].empty())
	{
	cout << "Could not open or find the image" << endl;
	return -1;
	}

	grayToScale(&image[i], &image_gray[i]);

	int coner = FASTAlgorithm(image_gray[i]);

	if (coner == 3) { cout << imageName[i] + " is triangle" << endl; }
	else if (coner == 10) { cout << imageName[i] + " is star" << endl; }
	else {}
	}


	t2 = clock();

	float diff = ((float)t2 - (float)t1);

	cout << "The running time : ";
	cout << diff / CLOCKS_PER_SEC;
	cout << " sec" << endl;




	for (int i = 0; i < 4; i++) {
	namedWindow("Image Original", WINDOW_NORMAL | WINDOW_GUI_NORMAL);
	imshow(imageName[i] + " Image Original", image[i]);

	namedWindow("Image Grayed", WINDOW_NORMAL | WINDOW_GUI_NORMAL);
	imshow(imageName[i] + " Image Grayed", image_gray[i]);

	imwrite("C:\\Users\\CAUCSE\\Desktop\\sample_gray.jpg", image_gray[i]);
	}
	*/

	String imageName = "C:\\1.jpg";
	Mat image;
	Mat image_gray;
	int mask[3][3] = { {1,1,1}, {1,1,1}, {1,1,1} };

	//이미지 존재 검사
	image = imread(imageName, IMREAD_UNCHANGED);
	if (image.empty()) {
		cout << "Could not open or find the image" << endl;
		return -1;
	}

	/********정현수 영역 start*******************/
	//3rd version 조합이 가장 안정적
	//텍스트 영역 구분 및 coord 출력
	
	partitioning(&makeBox(&image, &image_gray));
	
	/********정현수 영역 end*********************/

	//기존 이미지 출력
	namedWindow("Image Original", WINDOW_NORMAL | WINDOW_GUI_NORMAL);
	imshow(imageName + " image Original", image);

	//영역 칠한 이미지 출력
	namedWindow("Image Original", WINDOW_NORMAL | WINDOW_GUI_NORMAL);
	imshow(imageName + " image Original", image_gray);

	waitKey(0);

	return 0;
}

//1st ver. partitioning
/* Original Version
void partitioning(Mat *image) {
	Scalar_<uint8_t> bgrPixel;
	uint8_t* pixelPtr = (uint8_t*)image->data;

	int start[2] = { 0 , 0 };
	int end[2] = { 0, 0 };
	bool startCount = true;
	bool endCount = true;

	for (int j = 0; j < image->rows; j++) {
		for (int i = 0; i < image->cols; i++) {
			if (image->at<cv::Vec3b>(j, i)[0] == 0) { // 검은색이면 시작
				if (startCount) {
					start[0] = i; //첫 시작의 x좌표
					start[1] = j; //첫 시작의 y좌표
					startCount = false;

				}
				else { // 첫 시작이 아니라면 end 탐색
					end[0] = i;
					end[1] = j;
				}
				endCount = true;
			}
			else { //검은색이 아니라면
				startCount = true;

				if (endCount) {
					printf("startX : %d", start[0]);
					printf("\t startY : %d\n", start[1]);
					
					printf("endX : %d", end[0]);
					printf("\tendY : %d\n", end[1]);

					endCount = false;
				}
				else {
					continue;
				}
			}
		}
	}
}
*/

//2nd ver. partitioning
/*
void partitioning(Mat *image) {
	Scalar_<uint8_t> bgrPixel;
	uint8_t* pixelPtr = (uint8_t*)image->data;

	int start[2] = { 0 , 0 };
	int end[2] = { 0, 0 };
	bool startFlag = true;
	bool endFlag = true;

	for (int j = 10; j < image->rows; j = j+5) {
		for (int i = 10; i < image->cols; i = i + 5) {
			if (image->at<cv::Vec3b>(j, i)[0] == 0) 
			{ // 검은색이면 
				if (startFlag) // 시작점이라면
				{
					start[0] = i; // 시작점의 x 좌표
					start[1] = j; // 시작점의 y 좌표
					startFlag = false;
					continue; // 이거 넣어야 하나 꼭?
				}
				else // 시작점이 아니라면
				{
					end[0] = i; // 끝점의 x 좌표
					end[1] = j; // 끝점의 y 좌표
					endFlag = true;
				}
			}
			else //검은색이 아니라면
			{ 
				if (image->at<cv::Vec3b>(j+1, i)[0] == 0) // 지금은 검은색 아니지만, 직사각형의 우측 하단이 아니라면. 즉, 시작점의 아래 점이 검은색이라면.
				{
					break;
				}
				else // 진짜 우측 하단의 끝점이라면
				{
					if (endFlag == true) 
					{
						printf("start X = %d \t start Y = %d\n", start[0], start[1]);
						printf("end X = %d \t end Y = %d\n", end[0], end[1]);
						endFlag = false;
					}
					else 
					{
						break;
					}
					
					startFlag = true;
				}
			}
		}
	}
}
*/

//3rd ver. partitioning
void partitioning(Mat *image) {
	Scalar_<uint8_t> bgrPixel;
	uint8_t* pixelPtr = (uint8_t*)image->data;

	int start[2] = { 0 , 0 };
	int end[2] = { 0, 0 };
	bool startFlag = true;
	bool endFlag = true;
	int test = 0;

	for (int j = 1; j < image->rows; j = j + 1) {
		for (int i = 1; i < image->cols; i = i + 1) {
			if (image->at<cv::Vec3b>(j, image->cols - 1)[0] == 0)
			{ // 검은색이면 
				
				if (startFlag == true)
				{
					test = 1;
					start[0] = i; // x좌표
					start[1] = j;
					end[0] = image->cols - 1;
					end[1] = j;

					startFlag = false;
					endFlag = true;
					break;
				}
				else 
				{
					test = 2;
					end[1] = j;
				}
			}
			else //검은색이 아니라면
			{
				if (endFlag == true)
				{
					test = 3;
					printf("start X : %d \t start Y : %d\n", start[0], start[1]);
					printf("end X : %d \t end Y : %d\n", end[0], end[1]);
					endFlag = false;
					startFlag = true;
					break;
				}
				else
				{
					test = 4;
					break;
				}
			}
		}
	}
}

//1st & 2nd ver. makeBox
/*
Mat makeBox(Mat *image, Mat *dest)
{
	int cn = image->channels();
	bool flag = true;
	Scalar_<uint8_t> bgrPixel;
	uint8_t* pixelPtr = (uint8_t*)image->data;

	image->copyTo(*dest);

	float fGray = 0.0;
	
	for (int j = 40; j < image->rows; j++) {
		for (int i = 40; i < image->cols; i++) {
			bgrPixel.val[0] = pixelPtr[j * image->cols * cn + i * cn + 0]; // B
			bgrPixel.val[1] = pixelPtr[j * image->cols * cn + i * cn + 1]; // G
			bgrPixel.val[2] = pixelPtr[j * image->cols * cn + i * cn + 2]; // R

			fGray = 0.2126f * bgrPixel.val[2] + 0.7152f * bgrPixel.val[1] + 0.0722f * bgrPixel.val[0];
			
			if (fGray != 255) {
				if (flag) {
					for (int xi = 0; xi < 40; xi++) {
						for (int yi = 0; yi < 40; yi++) {
							dest->at<cv::Vec3b>(j - xi, i - yi)[0] = (int)0;
							dest->at<cv::Vec3b>(j - xi, i - yi)[1] = (int)0;
							dest->at<cv::Vec3b>(j - xi, i - yi)[2] = (int)0;
						}
					}
					flag = false;
				}
			}
			else { flag = true; }
		}
	}
	
	return *dest;
}
*/

// 3rd ver. makeBox
Mat makeBox(Mat *image, Mat *dest)
{
	int cn = image->channels();
	bool flag = true;
	Scalar_<uint8_t> bgrPixel;
	uint8_t* pixelPtr = (uint8_t*)image->data;

	image->copyTo(*dest);

	float fGray = 0.0;
	for (int j = 0; j < image->rows; j++)
	{
		for (int i = 0; i < image->cols; i++)
		{
			bgrPixel.val[0] = pixelPtr[j * image->cols * cn + i * cn + 0]; // B
			bgrPixel.val[1] = pixelPtr[j * image->cols * cn + i * cn + 1]; // G
			bgrPixel.val[2] = pixelPtr[j * image->cols * cn + i * cn + 2]; // R

			fGray = 0.2126f * bgrPixel.val[2] + 0.7152f * bgrPixel.val[1] + 0.0722f * bgrPixel.val[0];

			if (fGray != 255)
			{
				if (flag)
				{
					for (int xi = 0; xi < image->cols - i; xi++)
					{
						dest->at<cv::Vec3b>(j, i + xi)[0] = (int)0;
						dest->at<cv::Vec3b>(j, i + xi)[1] = (int)0;
						dest->at<cv::Vec3b>(j, i + xi)[2] = (int)0;
					}
					flag = false;
				}
			}
			else { flag = true; }
		}
	}
	return *dest;
}
