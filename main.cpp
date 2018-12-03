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

	image = imread(imageName, IMREAD_UNCHANGED);
	if (image.empty()) {
		cout << "Could not open or find the image" << endl;
		return -1;
	}
	partitioning(&makeBox(&image, &image_gray));

	namedWindow("Image Original", WINDOW_NORMAL | WINDOW_GUI_NORMAL);
	imshow(imageName + " image Original", image);

	namedWindow("Image Original", WINDOW_NORMAL | WINDOW_GUI_NORMAL);
	imshow(imageName + " image Original", image_gray);

	waitKey(0);

	return 0;
}

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

					if(i + 1 < image->cols) i ++; // 10씩 뛰어넘어도 이미지 사이즈 over 안되면 점프
				}
				else { // 첫 시작이 아니라면 end 탐색
					end[0] = i;
					end[1] = j;
					if (i + 1 < image->cols) i ++; // 10씩 뛰어넘어도 이미지 사이즈 over 안되면 점프
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

				/*************************************************
				//imagePartitioned라는 이름으로 그 조각난 이미지 보여주기
				for (int j = start[1]; j < end[1]; j++) {
					for (int i = start[0]; i < end[0]; i++) {
						
						
						
						imagePartitioned->at<cv::Vec3b>(j, i)[0] = image->at<cv::Vec3b>(j, i)[0];
						imagePartitioned->at<cv::Vec3b>(j, i)[1] = image->at<cv::Vec3b>(j, i)[1];
						imagePartitioned->at<cv::Vec3b>(j, i)[2] = image->at<cv::Vec3b>(j, i)[2];
						
					}
				}

				namedWindow("Image Original", WINDOW_NORMAL | WINDOW_GUI_NORMAL);
				imshow("image Original", *imagePartitioned);
				*/
			}
		}
	}
}



Mat makeBox(Mat *image, Mat *dest)
{
	int cn = image->channels();
	bool flag = true;
	Scalar_<uint8_t> bgrPixel;
	uint8_t* pixelPtr = (uint8_t*)image->data;

	image->copyTo(*dest);

	float fGray = 0.0;
	for (int j = 20; j < image->rows; j++) {
		for (int i = 20; i < image->cols; i++) {
			bgrPixel.val[0] = pixelPtr[j * image->cols * cn + i * cn + 0]; // B
			bgrPixel.val[1] = pixelPtr[j * image->cols * cn + i * cn + 1]; // G
			bgrPixel.val[2] = pixelPtr[j * image->cols * cn + i * cn + 2]; // R

			fGray = 0.2126f * bgrPixel.val[2] + 0.7152f * bgrPixel.val[1] + 0.0722f * bgrPixel.val[0];
			
			if (fGray != 255) {
				if (flag) {
					for (int xi = 0; xi < 20; xi++) {
						for (int yi = 0; yi < 20; yi++) {
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
