#include "pch.h"
#include "opencv.hpp"
using namespace cv;
using namespace std;

int main()
{
	//0401
	/*IplImage * image = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Mat matA = cvarrToMat(image);

	Mat matB;
	flip(matA, matB, 0);
	imshow("flip 1", matB);

	Mat matC;
	flip(matA, matC, 1);
	imshow("flip 2", matC);

	Mat matD;
	flip(matA, matD, -1);
	imshow("fip 3", matD);

	waitKey();*/

	//0402
	/*Mat srcImage = imread("lena.jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;

	Rect rtROI(0, 0, 256, 256);
	Mat roi = srcImage(rtROI);
	rectangle(srcImage, rtROI, Scalar::all(255));
	imshow("srcImage", srcImage);

	Mat dstImage = repeat(roi, 2, 2);
	imshow("dstImage", dstImage);
	*/

	//0403
	/*Mat srcImage = imread("lena.jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;

	Mat dstImage = Mat::zeros(srcImage.rows, srcImage.cols, srcImage.type());

	int N = 64;
	int nWidth = srcImage.cols / N;
	int nHeigth = srcImage.rows / N;
	int x, y;
	Rect rtROI;
	Mat roi;
	for(int i=0;i<N; i++)
		for (int j = 0; j < N; j++) {
			x = j * nWidth;
			y = i * nHeigth;
			rtROI = Rect(x, y, nWidth, nHeigth);
			roi = srcImage(rtROI);
			dstImage(rtROI) = mean(roi);
		}
	imshow("d", dstImage);
	waitKey();*/

	//0404
	/*Mat srcImage = imread("lena.jpg");
	if (srcImage.empty())
		return -1;

	vector<Mat> planes;
	split(srcImage, planes);

	imshow("planes[0]", planes[0]);
	imshow("planes[1]", planes[1]);
	imshow("planes[2]", planes[2]);

	Mat dstImage;
	merge(planes, dstImage);
	imshow("s", dstImage);*/

	//0405
	/*Mat srcImage = imread("lena.jpg");
	if (srcImage.empty())
		return -1;
	//cout << srcImage << endl<<endl<<endl;

	Mat imR(srcImage.rows, srcImage.cols, CV_8UC1);
	Mat imG(srcImage.rows, srcImage.cols, CV_8UC1);
	Mat imB(srcImage.rows, srcImage.cols, CV_8UC1);

	Mat outImage[] = { imB,imG,imR };
	int fromTo[] = { 0,0,1,1,2,2 };
	mixChannels(&srcImage, 1, outImage, 3, fromTo, 3);

	Mat dstImage(srcImage.rows, srcImage.cols, srcImage.type());
	mixChannels(outImage, 3, &dstImage, 1, fromTo, 3);
	imshow("d", dstImage);

	//cout << dstImage << endl;*/

	//0406
	/*Mat srcImage = imread("lena.jpg");
	if (srcImage.empty())
		return -1;

	vector<Mat> images(1, srcImage);

	vector < Mat> planes(1, Mat(srcImage.rows, srcImage.cols, srcImage.type()));
	int fromTo[] = { 0,0,0,1,0,2 };
	mixChannels(images, planes, fromTo, 3);

	Mat dstImage = planes[0];
	imshow("s", dstImage);*/

	//0407
	/*Mat srcImage = imread("lena.jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;

	IplImage* arrImage = cvCreateImage(cvSize(512, 512), IPL_DEPTH_8U, 3);

	insertImageCOI(srcImage, arrImage, 0);
	insertImageCOI(srcImage, arrImage, 1);
	insertImageCOI(srcImage, arrImage, 2);

	Mat dstImage = cvarrToMat(arrImage);
	imshow("d", dstImage);

	Mat imR, imG, imB;
	extractImageCOI(arrImage, imB, 0);
	extractImageCOI(arrImage, imG, 1);
	extractImageCOI(arrImage, imR, 2);

	imshow("B", imB);
	imshow("G", imG);
	imshow("R", imR);
	waitKey();*/

	//0408
	/*Mat A = (Mat_<uchar>(2, 3) << 0, 50, 100, 150, 200, 255);
	cout << A << endl;

	Mat_<uchar> lut(1, 256);
	for (int i = 0; i < 256; i++)
		lut(i) = 255 - i;
	cout << "lut=" << lut << endl;

	Mat dst;
	LUT(A, lut, dst);
	cout << dst << endl;*/

	//0409
	/*float dataA[] = {   -2,2,-2,
						-1,1,3,
						2,0,-1 };

	Mat A(3, 3, CV_32F, dataA);

	Mat B, C, D, E;
	B = abs(A);
	convertScaleAbs(A, C);

	convertScaleAbs(A, D, 2.0, 1.0);
	E = abs(A*2.0 + 1);

	Mat dst;
	absdiff(C, D, dst);

	cout << "A=" << A << endl;
	cout << "B=" << B << endl;
	cout << "C=" << C << endl;
	cout << "D=" << D << endl;
	cout << "E=" << E << endl;
	cout << "dst=" << dst << endl;*/

	//0410
	/*float dataA[] = { 1,2,3,
		4,5,6 };
	float dataB[] = { 10,10,10,
		10,10,10 };
	uchar dataC[] = { 0,0,0,1,1,1 };

	Mat A(2, 3, CV_32F, dataA);
	Mat B(2, 3, CV_32F, dataB); 
	Mat mask(2, 3, CV_8U, dataC);

	cout << "A=" << A << endl;
	cout << "B=" << B << endl;
	cout << "mask=" << mask << endl;

	Mat dst1;
	add(A, B, dst1);
	cout << "dst1=" << dst1 << endl;

	Mat dst2;
	add(A, B, dst2, mask);
	cout << "dst2=" << dst2 << endl;

	Mat dst3;
	add(A, 100, dst3);
	cout << "dst3=" << dst3 << endl;

	Mat dst4;
	add(A, Scalar(200), dst4);
	cout << "dst4=" << dst4 << endl;

	Mat dst5;
	scaleAdd(A, 2.0, B, dst5);
	cout << "dst5=" << dst5<< endl;

	Mat dst6;
	addWeighted(A, 1.0, B, 2.0, 10, dst6);
	cout << "dst6=" << dst6 << endl;

	Mat dst7;
	subtract(A, B, dst7);
	cout << "dst7=" << dst7 << endl;

	Mat dst8;
	multiply(A, B, dst8);
	cout << "dst8=" << dst8 << endl;

	Mat dst9;
	divide(A, B, dst9);
	cout << "dst9=" << dst9 << endl;

	Mat dst10;
	divide(A, 10, dst10);
	cout << "dst10=" << dst10 << endl;*/

	//0411
	/*uchar dataA[] = { 0x11,0x12,0x13, 0x14,0x15,0x16 };
	uchar dataB[] = { 0x0F,0x0F,0x0F, 0x0F, 0x0F, 0x0F };
	uchar dataC[] = {0,0,0,1,1,1};

	Mat A(2, 3, CV_8U, dataA);
	Mat B(2, 3, CV_8U, dataB);
	Mat mask(2, 3, CV_8U, dataC);

	cout << "A=" << A << endl;
	cout << "B=" << B << endl;
	cout << "mask=" << mask << endl;

	Mat dst1;
	bitwise_and(A, B, dst1);
	cout << "dst1=" << dst1 << endl;

	Mat dst2;
	bitwise_and(A, B, dst2, mask);
	cout << "dst2=" << dst2 << endl;

	Mat dst3;
	bitwise_and(A, 0x0F, dst3);
	cout << "dst3=" << dst3 << endl;

	Mat dst4;
	bitwise_or(A, B, dst4);
	cout << "dst4=" << dst4 << endl;

	Mat dst5;
	bitwise_or(A, B, dst5, mask);
	cout << "dst5=" << dst5 << endl;

	Mat dst6;
	bitwise_or(A, 0x0F, dst6);
	cout << "dst6=" << dst6 << endl;

	Mat dst7;
	bitwise_xor(A, B, dst7);
	cout << "dst7" << dst7 << endl;

	Mat dst8;
	bitwise_xor(A, B, dst8, mask);
	cout << "dst8=" << dst8 << endl;

	Mat dst9;
	bitwise_xor(A, 0x0F, dst9);
	cout << "dst9=" << dst9 << endl;

	Mat dst10;
	bitwise_not(A, dst10);
	cout << "dst10=" << dst10 << endl;*/

	//0412
	/*float dataA[] = { 10,20,30,40,50,60 };
	float dataB[] = { 10,20,30,100,200,300 };

	Mat A(2, 3, CV_32F, dataA);
	Mat B(2, 3, CV_32F, dataB);
	cout << "A=" << A << endl;
	cout << "B=" << B << endl;

	Mat dst1;
	compare(A, B, dst1, CMP_EQ);
	cout << "dst1=" << dst1 << endl;

	Mat dst2;
	compare(A, B, dst2, CMP_GT);
	cout << "dst2=" << dst2 << endl;

	Mat dst3;
	compare(A, B, dst3, CMP_GE);
	cout << "dst3=" << dst3 << endl;

	Mat dst4;
	compare(A, 40, dst4, CMP_GE);
	cout << "dst4=" << dst4 << endl;

	Point pt;
	checkRange(A, true, &pt, 10, 35);
	cout << "pt=" << pt << endl;

	Mat dst5;
	inRange(A, 30, 50, dst5);
	cout << "dst5=" << dst5 << endl;

	Mat dst6;
	inRange(A, Scalar(30), Scalar(50), dst6);
	cout << "dst6=" << dst6 << endl;*/

	//0413
	float dataA[] = { 10,20,30,40,50,60 };
	float dataB[] = { 10,20,30,100,200,300 };

	Mat A(2, 3, CV_32F, dataA);
	Mat B(2, 3, CV_32F, dataB);
	cout << "A=" << A << endl;
	cout << "B=" << B << endl;

	Mat dst1;
	min(A, B, dst1);
	cout << "1=" << dst1 << endl;

	Mat dst2;
	min(A, 20, dst2);
	cout << "2=" << dst2 << endl;

	Mat dst3;
	max(A, B, dst3);
	cout << "3=" << dst3 << endl;

	Mat dst4;
	max(A, 20, dst4);
	cout << "4=" << dst4 << endl;

	return 0;

}