#include "pch.h"
#include "opencv.hpp"
using namespace cv;
using namespace std;

#define L 256

void drawHistogram(Mat &image, Mat hist);

int main()
{
//	Mat srcImage = imread("lena.jpg", IMREAD_GRAYSCALE);
	//if (srcImage.empty())
		//return -1;

	//0501-2  
	/*Mat srcImage = imread("lena.jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;

//	Mat_<uchar>image(srcImage);
//	Mat_<uchar>dstImage(srcImage.size());

//	for(int y=0; y<image.rows; y++)
//		for (int x = 0; x < image.cols; x++)
//		{
//			uchar r = image(y, x);
//			dstImage(y, x) = 255 - r;
//		}

	Mat_<uchar> lut(1, 256);
	for (int i = 0; i < 256; i++)
		lut(i) = 256 - i;

	Mat dstImage;
	LUT(srcImage, lut, dstImage);
	imshow("d", dstImage);
	waitKey();*/

	//0503
	/*Mat srcImage = imread("lena.jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;

	Mat dstImage1;
	double th1 = threshold(srcImage, dstImage1, 50, 255, THRESH_BINARY);
	cout << "th1=" << th1 << endl;

	Mat dstImage2;
	double th2 = threshold(srcImage, dstImage2, 100, 255, THRESH_BINARY + THRESH_OTSU);
	cout << "th2=" << th2 << endl;

	imshow("1", dstImage1);
	imshow("2", dstImage2);
	waitKey();*/

	//0504
	/*Mat srcImage = imread("lena.jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return - 1;

	Mat dstImage1;
	adaptiveThreshold(srcImage, dstImage1, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 21, 5);

	Mat dstImage2;
	adaptiveThreshold(srcImage, dstImage2, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 21, 5);

	imshow("1", dstImage1);
	imshow("2", dstImage2);*/

	//0505
	/*Mat srcImage = imread("lena.jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;
	double minVal, maxVal;
	Point minLoc, maxLoc;

	minMaxLoc(srcImage, &minVal, &maxVal, &minLoc, &maxLoc);
	cout << "In srcImage" << endl;
	cout << "minVal=" << minVal << endl;
	cout << "maxVal=" << maxVal << endl;
	cout << "minLoc=" << minLoc << endl;
	cout << "maxLoc=" << maxLoc << endl;

	Mat dstImage;
	double scale = 100.0 / (maxVal - minVal);
	srcImage.convertTo(dstImage, -1, scale, -scale*minVal);
	//normalize(srcImage, dstImage, 0, 100, NORM_MINMAX);

	minMaxLoc(dstImage, &minVal, &maxVal, &minLoc, &maxLoc);
	cout << "In dstImage" << endl;
	cout << "minVal=" << minVal << endl;
	cout << "maxVal=" << maxVal << endl;
	cout << "minLoc=" << minLoc << endl;
	cout << "maxLoc=" << maxLoc << endl;

	imshow("d", dstImage);*/

	//0506
	/*Mat fImage;
	srcImage.convertTo(fImage, CV_32F);
	add(fImage, Scalar(1), fImage);

	Mat logImage;
	log(fImage, logImage);

	double minVal, maxVal;
	minMaxLoc(logImage, &minVal, &maxVal);
	cout << "before" << endl;
	cout << "minVal=" << minVal << endl;
	cout << "maxVal=" << maxVal << endl;

	normalize(logImage, logImage, 0, 1.0, NORM_MINMAX);
	minMaxLoc(logImage, &minVal, &maxVal);
	cout << "after" << endl;
	cout << "minVal=" << minVal << endl;
	cout << "maxVal=" << maxVal << endl;

	imshow("d", logImage);*/

	//0507
	/*Mat fImage;
	srcImage.convertTo(fImage, CV_32F);

	double power = 0.1;
	Mat powImage;
	pow(fImage, power, powImage);

	double minVal, maxVal;
	minMaxLoc(powImage, &minVal, &maxVal);
	cout << "before" << endl;
	cout << "minVal=" << minVal << endl;
	cout << "maxVal=" << maxVal << endl;

	normalize(powImage, powImage, 0, 1.0, NORM_MINMAX);
	minMaxLoc(powImage, &minVal, &maxVal);
	cout << "after" << endl;
	cout << "minVal=" << minVal << endl;
	cout << "maxVal=" << maxVal << endl;

	imshow("d", powImage);*/

	//0508-9
	/*uchar dataA[16] = { 0,0,0,0,1,1,3,5,6,1,1,3,4,3,1,7 };
	Mat A(4, 4, CV_8U, dataA);
	cout << "A=" << A << endl;

	int hisSize[4] = { 4 };
	//float valRange[] = { 0,8 };
	float valRange[] = {0,1,4,5,8};
	const float* ranges[] = { valRange };
	int channels[] = { 0 };
	int dims = 1;

	Mat hist;
	calcHist(&A, 1, channels, Mat(), hist, dims, hisSize, ranges, false);
	//calcHist(&A, 1, channels, Mat(), hist, dims, hisSize, ranges, true);
	cout << "hist=" << hist << endl;

	Mat pdf;
	normalize(hist, pdf, 1, 0, NORM_L1);
	cout << "pdf=" << pdf << endl;*/

	//0510
	/*int histSize = 32;
	float valueRange[] = { 0,256 };
	const float* ranges[] = { valueRange };
	int channels = 0;
	int dims = 1;

	Mat hist;
	calcHist(&srcImage, 1, &channels, Mat(), hist, 1, &histSize, ranges);

	Mat histImage(512, 512, CV_8U);
	normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, CV_32F);

	histImage = Scalar(255);
	int binW = cvRound((double)histImage.cols / histSize);
	int x1, y1, x2, y2;
	for (int i = 0; i < histSize; i++) {
		x1 = i * binW;
		y1 = histImage.rows;
		x2 = (i + 1)*binW;
		y2 = histImage.rows - cvRound(hist.at<float>(i));
		rectangle(histImage, Point(x1, y1), Point(x2, y2), Scalar(0), -1);
	}
	imshow("h", histImage);
	waitKey();*/

	//0511
	/*Mat srcImage = imread("lena.jpg");
	if (srcImage
.empty())
		return -1;

	int histSize[] = { 64,64 };
	float range1[] = { 0,256 };
	float range2[] = { 0,256 };

	const float*ranges[] = { range1,range2 };
	const int channels[] = { 0,2 };
	int dims = 2;

	Mat hist;
	calcHist(&srcImage, 1, channels, Mat(), hist, dims, histSize, ranges,true,true);
	cout << "hist.size()=" << hist.size() << endl;
	normalize(hist, hist, 0, 255, NORM_MINMAX, CV_32F);

	Mat histImage(512, 512, CV_8U, Scalar(255));
	int binW = cvRound((double)histImage.cols / histSize[1]);
	int binH = cvRound((double)histImage.cols / histSize[0]);

	int x, y;
	Rect rtROI;
	Mat roi;
	for(int i=0;i<histSize[1]; i++)
		for (int j = 0; j < histSize[0]; j++) {
			float hValue = hist.at<float>(j, i);
			x = i * binW;
			y = j * binH;
			rtROI = Rect(x, y, binW, binH);
			histImage(rtROI) = hValue;
		}
	imshow("hist", histImage);
	waitKey();*/
	
	//0512
	/*uchar dataA[16] = { 0,0,0,0,
						1,1,3,5,
						6,1,1,3,
						4,3,1,7 };
	Mat A(4, 4, CV_8U, dataA);
	cout << "A=" << A << endl;

	int histSize[] = { L };
	float valueRange[] = { 0,L };
	const float *ranges[] = { valueRange };
	int channels[] = { 0 };
	int dims = 1;

	Mat hist;
	calcHist(&A, 1, channels, Mat(), hist, dims, histSize, ranges,true);
	cout << "hist=" << hist << endl;

	Mat pdf;
	normalize(hist, pdf, L - 1,0, NORM_L1);
	cout << "pdf=" << pdf << endl;
	cout << "pdf.size()=" << pdf.size() << endl;
	cout << "pdf.type()=" << pdf.type() << endl;

	Mat cdf(pdf.size(), pdf.type());
	cdf.at<float>(0) = pdf.at<float>(0);
	for (int i = 1; i < pdf.rows; i++)
		cdf.at<float>(i) = cdf.at<float>(i - 1) + pdf.at<float>(i);
	cout << "cdf=" << cdf << endl;

	Mat table(cdf.size(), CV_8U);
	table.at<uchar>(0) = 0;
	for (int i = 1; i < pdf.rows; i++)
		table.at<uchar>(i) = cvRound(cdf.at<float>(i));
	cout << "table=" << table << endl;

	Mat dst;
	LUT(A, table, dst);
	cout << "dst=" << dst << endl;*/
	
	//0513
	/*uchar dataA[] = { 0,0,0,0,1,1,3,5,6,1,1,1,6,1,1,3,4,3,1,7 };
	Mat A(4, 4, CV_8U, dataA);

	Mat dst;
	equalizeHist(A, dst);
	cout << "dst=" << dst << endl;

	CvMat pSrcMat = A;
	CvMat *pDstMat = cvCreateMat(4, 4, CV_8U);
	cvEqualizeHist(&pSrcMat, pDstMat);
	Mat dst2 = cvarrToMat(pDstMat);
	cout << "dst2=" << dst2 << endl;*/

	//0514
	/*Mat srcImage = imread("lena.jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;

	int histSize[] = { L };

	float valueRange[] = { 0,L };
	const float* ranges[] = {valueRange};
	int channels[] = { 0 };
	int dims = 1;

	Mat hist;
	calcHist(&srcImage, 1, channels, Mat(), hist, dims, histSize, ranges, true);
	Mat pdf;
	normalize(hist, pdf, L - 1, 0, NORM_L1);

	Mat cdf(pdf.size(), pdf.type());
	cdf.at<float>(0) = pdf.at<float>(0);
	for (int i = 1; i < pdf.rows; i++)
		cdf.at<float>(i) = cdf.at<float>(i - 1) + pdf.at<float>(i);

	Mat table(cdf.size(),CV_8U);
	table.at<uchar>(0) = 0;
	for (int i = 1; i < pdf.rows; i++)
		table.at<uchar>(i) = cvRound(cdf.at<float>(i));

	Mat dstImage;
	LUT(srcImage, table, dstImage);

	vector<int> params;
	params.push_back(IMWRITE_JPEG_QUALITY);
	params.push_back(100);
	imwrite("imageEq1.jpg", dstImage, params);*/

	//0515
	/*Mat srcImage = imread("lena.jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;
	Mat dstImage;
	equalizeHist(srcImage, dstImage);

	vector<int>params;
	params.push_back(IMWRITE_JPEG_QUALITY);
	params.push_back(100);
	imwrite("imageEq2.jpg", dstImage, params);
	
	imshow("d", dstImage);
	waitKey();*/

	//0516
	/*Mat srcImage1 = imread("lena.jpg", IMREAD_GRAYSCALE);
	if (srcImage1.empty())	return -1;

	Mat srcImage2 = imread("imageEq2.jpg", IMREAD_GRAYSCALE);
	if (srcImage2.empty())	return -1;

	int histSize = 256;
	float valueRange[] = { 0,256 };
	const float* ranges[] = { valueRange };
	int channels = 0;
	int dims = 1;

	Mat H1;
	calcHist(&srcImage1, 1, &channels, Mat(), H1, dims, &histSize, ranges);
	normalize(H1, H1, 1, 0, NORM_L1, CV_32F);

	Mat H2;
	calcHist(&srcImage2, 1, &channels, Mat(), H2, dims, &histSize, ranges);
	normalize(H2, H2, 1, 0, NORM_L1, CV_32F);

	double dist1 = compareHist(H1,H2,0);    //correl
	cout << "dist1=" << dist1 << endl;

	double dist2 = compareHist(H1, H2, 1);
	cout << "dist2=" << dist2 << endl;

	double dist3 = compareHist(H1, H2, 2);
	cout << "dist3=" << dist3 << endl;

	double dist4 = compareHist(H1, H2, 3);
	cout << "dist4=" << dist4 << endl;

	Mat histImage1;
	drawHistogram(histImage1, H1);
	imshow("1", histImage1);

	Mat histImage2;
	drawHistogram(histImage2, H2);
	imshow("2", histImage2);
	waitKey();*/

	//0520
	/*uchar dataA[16] = { 0,0,0,0,
		1,1,3,5,
		6,1,1,3,
		4,3,1,7 };
	Mat A(4, 4, CV_8U, dataA);
	cout << "A=" << A << endl;

	int histSize[] = { 8 };
	float valueRange[] = { 0,8 };
	const float * ranges[] = {valueRange};
	int channels[] = { 0 };
	int dims = 1;

	Mat hist;
	calcHist(&A, 1, channels, Mat(), hist, dims, histSize, ranges);
	cout << "hist=" << hist << endl;

	Mat backProject;
	calcBackProject(&A, 1, channels, hist, backProject, ranges);
	cout << "backproject=" << backProject << endl;*/

	//0521
	/*uchar dataA[16] = { 0,0,0,0,
		1,1,1,1,
		1,1,1,2,
		1,2,1,3 };
	Mat A(4, 2, CV_8UC2, dataA);
	cout << "A=" << A << endl;

	int histSize[] = { 4,4 };
	float valueRange1[] = { 0,4 };
	float valueRange2[] = { 0,4 };

	const float * ranges[] = { valueRange1, valueRange2 };
	int channels[] = { 0,1 };
	int dims = 2;

	Mat hist;
	calcHist(&A, 1, channels, Mat(), hist, dims, histSize, ranges);
	cout << "hist=" << hist << endl;

	Mat backProject;
	calcBackProject(&A, 1, channels, hist, backProject, ranges);
	cout << "backproject=" << backProject << endl;*/
	
	//0522
	/*Mat srcImage = imread("fruits.jpg");
	if (srcImage.empty())
		return -1;

	Mat hsvImage;
	cvtColor(srcImage, hsvImage, COLOR_BGR2HSV);
	vector<Mat>planes;
	split(hsvImage, planes);
	Mat hueImage = planes[0];

	Rect roi(100, 100, 100, 100);
	rectangle(srcImage, roi, Scalar(0, 0, 255), 2);
	Mat roiImage = hueImage(roi);

	int histSize = 256;
	float hValue[] = { 0,256 };
	const float * ranges[] = { hValue };
	int channels = 0;
	int dims = 1;

	Mat hist;
	calcHist(&roiImage, 1, &channels, Mat(), hist, dims, &histSize, ranges);

	Mat hueImage2;
	hueImage.convertTo(hueImage2, CV_32F);
	
	Mat backProject;
	calcBackProject(&hueImage2, 1, &channels, hist, backProject, ranges);

	double minVal, maxVal;
	minMaxLoc(backProject, &minVal, &maxVal);
	cout << "minVal=" << minVal << endl;
	cout << "maxVal=" << maxVal << endl;

	Mat backProject2;
	normalize(backProject, backProject2, 0, 255, NORM_MINMAX, CV_8U);

	imshow("backProject2", backProject2);
	imshow("srcImage", srcImage);
	waitKey();*/

	//0523
	Mat srcImage = imread("lena.jpg");
	if (srcImage.empty())
		return -1;
	imshow("s", srcImage);

	Mat grayImage;
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
	imshow("g", grayImage);

	Mat hsvImage;
	cvtColor(srcImage, hsvImage, COLOR_BGR2HSV);
	imshow("h", hsvImage);

	Mat yCrCbImage;
	cvtColor(srcImage, yCrCbImage, COLOR_BGR2YCrCb);
	imshow("y", yCrCbImage);

	Mat luvImage;
	cvtColor(srcImage, luvImage, COLOR_BGR2Luv);
	imshow("l", luvImage);
	waitKey();


	return 0;
}

void drawHistogram(Mat &image, Mat hist) {
	if (image.empty())
		image.create(512, 512, CV_8U);
	normalize(hist, hist, 0, image.rows, NORM_MINMAX, CV_32F);

	image = Scalar(255);
	int binW = cvRound((double)image.cols / hist.rows);
	int x1, x2, y1, y2;
	for (int i = 0; i < hist.rows; i++) {
		x1 = i * binW;
		y1 = image.rows;
		x2 = (i + 1)*binW;
		y2 = image.rows - cvRound(hist.at<float>(i));
		rectangle(image, Point(x1, y1), Point(x2, y2), Scalar(0), -1);
	}
};