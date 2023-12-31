#include "pch.h"
#include "opencv.hpp"
#include "opencv2/legacy/legacy.hpp"
#include <iomanip>
using namespace cv;
using namespace std;

typedef struct _DATA {
	Mat image;
	Mat mask;
}DATA;

class ClosePoints {
public:
	ClosePoints(int minDist) :minDist_(minDist) {}

	bool operator()(const Point &p1, const Point &p2)const {
		int dist2 = (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
		return dist2 < (minDist_*minDist_);
	}

private:
	int minDist_;
};

#define TH 10
#define MAX_CLUSTERS 4

void onMouse(int event, int x, int y, int flags, void * params);
vector<Point> g_points;

void Printmat(const char *strName, Mat A);
vector<Rect> PyrSegmentation(Mat &src, Mat &dst, int level, int th1, int th2);
void floodFillPostProcess(Mat& img, const Scalar& colorDiff);

int main()
{
	//0801
	/*Mat srcImage = imread("lena.jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;
	Mat edges;
	Canny(srcImage, edges, 50, 100);
	imshow("e", edges);*/

	//0802
	/*Mat srcImage = imread("line.jpg", IMREAD_GRAYSCALE);

	if (srcImage.empty())
		return -1;

	Mat edges;
	Canny(srcImage, edges, 50, 100);
	imshow("edges", edges);
	vector<Vec2f> lines;
	HoughLines(edges, lines, 1, CV_PI / 180.0, 100);

	Mat dstImage(srcImage.size(), CV_8UC3);
	cvtColor(srcImage, dstImage, COLOR_GRAY2BGR);
	cout << "lines.size()=" << lines.size() << endl;

	Vec2f params;
	float rho, theta;
	float c, s;
	float x0, y0;
	for (int k = 0; k < lines.size(); k++) {
		params = lines[k];
		rho = params[0];
		theta = params[1];
		printf("lines[%2d]=(rho, theta) = (%f, %f)\n", k, rho, theta);

		c = cos(theta);
		s = sin(theta);
		x0 = rho * c;
		y0 = rho * s;
		
		Point pt1, pt2;
		pt1.x = cvRound(x0 + 1000 * (-s));
		pt1.y = cvRound(y0 + 1000 * c);

		pt2.x = cvRound(x0 - 1000 * (-s));
		pt2.y = cvRound(y0 - 1000 * c);
		line(dstImage, pt1, pt2, Scalar(0, 0, 255), 2);
	}
	imshow("dstImage", dstImage);
	waitKey();*/

	//0803
	/*Mat srcImage = imread("line.jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;

	Mat edges;
	Canny(srcImage, edges, 50, 100);
	imshow("edges", edges);
	vector<Vec4i> lines;
	HoughLinesP(edges, lines, 1, CV_PI / 180.0, 10, 30, 10);

	Mat dstImage(srcImage.size(), CV_8UC3);
	cvtColor(srcImage, dstImage, COLOR_GRAY2BGR);
	Vec4i params;
	int x1, y1, x2, y2;
	for (int k = 0; k < lines.size(); k++) {
		params = lines[k];
		x1 = params[0];
		y1 = params[1];
		x2 = params[2];
		y2 = params[3];
		printf("lines[%2d] = P1(%4d,%4d) = P2(%4d,%4d)\n", k, x1, y1, x2, y2);
		Point pt1(x1, y1), pt2(x2, y2);
		line(dstImage, pt1, pt2, Scalar(0, 0, 255), 2);
	}
	imshow("dst", dstImage);
	waitKey();*/

	//0804
	/*Mat srcImage = imread("circle.jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;

	vector<Vec3f>circles;
	HoughCircles(srcImage, circles, CV_HOUGH_GRADIENT, 1, 50);
	cout << "circle.size()=" << circles.size() << endl;

	Mat dstImage;
	cvtColor(srcImage, dstImage, COLOR_GRAY2BGR);

	Vec3f params;
	int cx, cy, r;

	for (int k = 0; k < circles.size(); k++) {
		params = circles[k];
		cx = cvRound(params[0]);
		cy = cvRound(params[1]);
		r = cvRound(params[2]);
		printf("circles[%2d]:(cx,cy)=(%d,%d),r=%d\n", k, cx, cy, r);

		Point center(cx, cy);
		circle(dstImage, center, r, Scalar(0, 0, 255), 2);
	}
	imshow("d", dstImage);
	waitKey();*/

	//0805
	/*Mat srcImage = imread("heart10.jpg", IMREAD_GRAYSCALE);

	GaussianBlur(srcImage, srcImage, Size(7, 7), 0.0, 0.0);
	imshow("srcImage", srcImage);

	Mat dstImage1;
	double th1 = threshold(srcImage, dstImage1, 128, 255, THRESH_BINARY_INV + THRESH_OTSU);
	cout << "th1=" << th1 << endl;

	int blockSize = 7;
	int C = 5;
	Mat dstImage2;
	adaptiveThreshold(srcImage, dstImage2, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY_INV, blockSize, C);

	Mat dstImage3;
	adaptiveThreshold(srcImage, dstImage3, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, blockSize, C);

	imshow("OTSU", dstImage1);
	imshow("MEAN_C", dstImage2);
	imshow("GAUSSIAN_C", dstImage3);
	waitKey(0);*/

	//0806 + color
	/*Mat rgbImage = imread("hand.jpg");
	imshow("rgbImage", rgbImage);

	Mat hsvImage;
	cvtColor(rgbImage, hsvImage, COLOR_BGR2HSV);
	imshow("hsvImage", hsvImage);

	Scalar lowerb(0, 40, 0);
	Scalar upperb(20, 180, 255);

	Mat dstImage1;
	inRange(hsvImage, lowerb, upperb, dstImage1);
	imshow("dstImage1", dstImage1);

	Mat result;
	bitwise_and(rgbImage, rgbImage, result, dstImage1);
	imshow("result", result);

	vector<Mat> planes;
	split(hsvImage, planes);
	//imshow("0", planes[0]);
	//imshow("1", planes[1]);
	//imshow("2", planes[2]);

	double minH, maxH;
	minMaxLoc(planes[0], &minH, &maxH, NULL, NULL, dstImage1);
	cout << "minH=" << minH << ", maxH=" << maxH << endl;

	double minS, maxS;
	minMaxLoc(planes[1], &minS, &maxS, NULL, NULL, dstImage1);
	cout << "minS=" << minS << ", maxS=" << maxS << endl;

	double minV, maxV;
	minMaxLoc(planes[2], &minV, &maxV, NULL, NULL, dstImage1);
	cout << "minV=" << minV << ", maxV=" << maxV << endl;*/

	//0807
	/*Mat srcImage = Mat::zeros(512, 512, CV_8UC1);
	rectangle(srcImage, Point(50, 100), Point(200, 400), Scalar::all(255), -1);
	rectangle(srcImage, Point(80, 150), Point(180, 350), Scalar::all(0), -1);

	rectangle(srcImage, Point(250, 100), Point(450, 400), Scalar::all(255), -1);
	rectangle(srcImage, Point(280, 150), Point(420, 350), Scalar::all(0), -1);
	rectangle(srcImage, Point(320, 200), Point(380, 300), Scalar::all(255), -1);

	Mat dstImage(srcImage.size(), CV_8UC3);
	cvtColor(srcImage, dstImage, COLOR_GRAY2BGR);

	//int mode = RETR_EXTERNAL;
	int mode = RETR_LIST;

	//int method = CHAIN_APPROX_SIMPLE;
	int method = CHAIN_APPROX_NONE;
	
	vector<vector<Point>> contours;
	findContours(srcImage, contours, noArray(), mode, method);
	cout << "contours.size()=" << contours.size() << endl;

	for (int k = 0; k < contours.size(); k++) {
		Scalar color(rand() & 255, rand() & 255, rand() & 255);
		drawContours(dstImage, contours, k, color, 4);

		cout << "contours[" << k << "].size()=" << contours[k].size() << endl;
		for (int j = 0; j < contours[k].size(); j++) {
			Point pt = contours[k][j];
			cout << "pt[" << j << "]=" << pt << endl;
		}
	}
	imshow("d", dstImage);*/

	//0808
	/*Mat srcImage = imread("ContourTest.jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;
	threshold(srcImage, srcImage, 128, 255, THRESH_BINARY);

	Mat srcImage2 = srcImage.clone();
	Mat dstImage(srcImage2.size(), CV_8UC3);
	cvtColor(srcImage2, dstImage, COLOR_GRAY2BGR);

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	//int mode = RETR_CCOMP;
	int mode = RETR_TREE;
	int method = CHAIN_APPROX_SIMPLE;

	findContours(srcImage, contours, hierarchy, mode, method);
	cout << "contour.size()=" << contours.size() << endl;

	//dd
	drawContours(dstImage, contours, -1, Scalar(2, 0, 255), 4, 8, hierarchy, 3);
	imshow("dstImage", dstImage);
	waitKey();

	Scalar color[4] = { Scalar(255,0,0),Scalar(0,255,0),Scalar(255,0,255),Scalar(0,255,255) };

	for (int k = 0; k < contours.size(); k++) {
		cvtColor(srcImage2, dstImage, COLOR_GRAY2BGR);
		cout << "hierarchy[" << k << "][0]=" << hierarchy[k][0] << endl;
		cout << "hierarchy[" << k << "][1]=" << hierarchy[k][1] << endl;
		cout << "hierarchy[" << k << "][2]=" << hierarchy[k][2] << endl;
		cout << "hierarchy[" << k << "][3]=" << hierarchy[k][3] << endl;

		drawContours(dstImage, contours, k, Scalar(0, 0, 255), 2);
		for (int j = 0; j< 4; j++) {
			if (hierarchy[k][j] < 0)
				continue;
			drawContours(dstImage, contours, hierarchy[k][j], color[j], 2);
		}
		imshow("dstImage", dstImage);
		waitKey();
	}
	
	waitKey();*/

	//0809
	/*Mat dstImage(Size(512, 512), CV_8UC3, Scalar::all(255));

	rectangle(dstImage, Point(50, 50), Point(200, 200), Scalar(0, 0, 255), 2);
	circle(dstImage, Point(300, 300), 100, Scalar(0, 0, 255), 2);

	Scalar loDiff = Scalar::all(10);
	Scalar upDiff = Scalar::all(10);
	int floodFlags = 4 | FLOODFILL_FIXED_RANGE;
	Rect boundRect;

	floodFill(dstImage, Point(100, 100), Scalar(255, 0, 0), &boundRect, loDiff, upDiff, floodFlags);
	rectangle(dstImage, boundRect, Scalar(0, 255, 0), 2);

	floodFill(dstImage, Point(300, 300), Scalar(255, 0, 0), &boundRect, loDiff, upDiff, floodFlags);
	rectangle(dstImage, boundRect, Scalar(0, 255, 0), 2);
	imshow("d", dstImage);
	waitKey();*/

	//0810
	/*Mat srcImage = imread("lena.jpg");
	if (srcImage.empty())
		return -1;

	Mat dstImage = srcImage.clone();
	Mat mask = Mat::zeros(srcImage.size(), CV_8U);
	imshow("dstImage", dstImage);

	DATA data = { dstImage, mask };
	setMouseCallback("dstImage", onMouse, (void*)&data);

	double inpaintRadius = 5;
	int flags = INPAINT_TELEA;

	bool bEscKey = false;
	int nKey;
	while (!bEscKey) {
		nKey = waitKey(0);
		switch (nKey) {
		case 27:
			bEscKey = true;
			break;
		case 'r':
			mask = 0;
			srcImage.copyTo(dstImage);
			imshow("dstImage", dstImage);
			break;
		case ' ':
			inpaint(dstImage, mask, dstImage, inpaintRadius, flags);
			imshow("dstImage", dstImage);
			break;
		}
	}*/

	//0811
	/*uchar dataA[] = { 0,0,0,0,0,0,0,
				      0,1,1,1,1,1,0,
				      0,1,1,1,1,1,0,
				      0,1,1,1,1,1,0,
					  0,1,1,1,1,1,0,
				      0,1,1,1,1,1,0,
				  	  0,0,0,0,0,0,0 };
	Mat A(7, 7, CV_8U, dataA);
	Printmat("A=", A);

	int distanceType = CV_DIST_C;
	int maskSize = 3;
	Mat labels;
	Mat distance;
	
	//distanceTransform(A, distance, distanceType, maskSize);
	distanceTransform(A, distance, labels, distanceType, maskSize, DIST_LABEL_PIXEL);
	//distanceTransform(A, distance, labels, distanceType, maskSize, DIST_LABEL_CCOMP);

	Printmat("distance=", distance);
	Printmat("labels=", labels);

	waitKey();*/

	//0812
	/*Mat srcImage = imread("DistTest.jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;
	threshold(srcImage, srcImage, 200, 255, THRESH_BINARY);
	int distanceType = CV_DIST_L1;
	int makSize = 3;
	int maskSize = 5;

	Mat distance1,distance2;
	distanceTransform(srcImage, distance1, distanceType, makSize);
	distanceTransform(srcImage, distance2, distanceType, makSize);

	Mat dstImage1, dstImage2;
	normalize(distance1, dstImage1, 0, 255, NORM_MINMAX, CV_8U);
	normalize(distance2, dstImage2, 0, 255, NORM_MINMAX, CV_8U);

	imshow("d1", dstImage1);
	imshow("d2", dstImage2);

	int histSize = 256;
	float valueRange[] = { 0,256 };
	const float*ranges[] = { valueRange };
	int channels = 0;
	int dims = 1;

	Mat H1;
	calcHist(&dstImage1, 1, &channels, Mat(), H1, dims, &histSize, ranges);
	normalize(H1, H1, 1, 0, NORM_L1, CV_32F);

	Mat H2;
	calcHist(&dstImage2, 1, &channels, Mat(), H2, dims, &histSize, ranges);
	normalize(H2, H2, 1, 0, NORM_L1, CV_32F);

	double d1 = compareHist(H1, H2, CV_COMP_CORREL);
	cout << "d1=" << d1 << endl;

	double d2 = compareHist(H1, H2, CV_COMP_CHISQR);
	cout << "d2=" << d2 << endl;

	double d3 = compareHist(H1, H2, CV_COMP_INTERSECT);
	cout << "d3=" << d3 << endl;

	double d4 = compareHist(H1, H2, CV_COMP_BHATTACHARYYA);
	cout << "d4=" << d4 << endl;*/

	//0813
	/*Mat srcImage = imread("flower.jpg");
	if (srcImage.empty())
		return -1;
	Mat dstImage = srcImage.clone();
	imshow("dstImage", dstImage);

	Mat mask = Mat::zeros(srcImage.size(), CV_8U);
	Mat markers = Mat::zeros(srcImage.size(), CV_32S);
	
	DATA data = { dstImage,mask };
	setMouseCallback("dstImage", onMouse, (void*)&data);

	int mode = CV_RETR_LIST;
	int method = CV_CHAIN_APPROX_SIMPLE;
	vector<vector<Point>>contours;

	bool bEscKey = false;
	int nKey;
	while (!bEscKey) {
		nKey = cvWaitKey(0);
		switch (nKey) {
		case 27:
			bEscKey = true;
			break;
		case 'r':
			mask = 0;
			srcImage.copyTo(dstImage);
			imshow("dstImage", dstImage);
			break;
		case ' ':
			findContours(mask, contours, noArray(), mode, method);
			if (contours.size() < 1)
				break;
			markers = 0;
			for (int k = 0; k < contours.size(); k++) {
				drawContours(markers, contours, k, k + 1, -1);
			}
			watershed(srcImage, markers);

			Mat colorTable(contours.size(), 1, CV_8UC3);
			Vec3b color;
			for (int k = 0; k < contours.size(); k++) {
				color[0] = rand() & 180 + 50;
				color[1] = rand() & 180 + 50;
				color[2] = rand() & 180 + 50;
				colorTable.at<Vec3b>(k, 0) = color;
			}

			for(int y=0; y<markers.rows;y++)
				for (int x = 0; x< markers.cols; x++) {
					int k = markers.at<int>(y, x);
					if (k == -1)
						color[0] = color[1] = color[2] = 255;
					else if(k<=0||k>contours.size())
						color[0] = color[1] = color[2] = 0;
					else {
						color = colorTable.at<Vec3b>(k - 1, 0);
						dstImage.at<Vec3b>(y, x) = color;
					}
				}
			addWeighted(dstImage, 0.5, srcImage, 0.5, 0, dstImage);
			imshow("dstImage", dstImage);
			break;
		}
	}*/

	//0814
	/*Mat srcImage = imread("Heart10.jpg");
	if (srcImage.empty())
		return -1;
	imshow("srcImage", srcImage);

	Mat srcImage8;
	cvtColor(srcImage, srcImage8, COLOR_BGR2GRAY);

	Mat dstImage8;
	threshold(srcImage8, dstImage8, 0, 255, THRESH_BINARY_INV + THRESH_OTSU);
	imshow("dstImage8", dstImage8);

	Mat distance, distImage8;
	distanceTransform(dstImage8, distance, CV_DIST_L1, 3);
	normalize(distance, distImage8, 0, 255, NORM_MINMAX, CV_8U);
	imshow("distance", distImage8);

	Mat mask;
	//threshold(dstImage8, mask, TH, 255, THRESH_BINARY);
	mask = distance > TH;
	imshow("mask", mask);

	vector<vector<Point>>contours;
	findContours(mask, contours, noArray(), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
	if (contours.size() < 1)
		return 0;

	Mat markers = Mat::zeros(srcImage.size(), CV_32S);
	for (int k = 0; k < contours.size(); k++) {
		drawContours(markers, contours, k, k + 1, -1);
	}
	circle(markers, Point(5, 5), 3, Scalar::all(contours.size() + 1), -1);

	Mat dstImage = srcImage.clone();
	watershed(dstImage, markers);

	Mat colorTable(contours.size() + 1, 1, CV_8UC3);
	Vec3b color;
	for (int k = 0; k < contours.size(); k++) {
		color[0] = theRNG().uniform(0, 180) + 50;
		color[1] = theRNG().uniform(0, 180) + 50;
		color[2] = theRNG().uniform(0, 180) + 50;
		colorTable.at<Vec3b>(k, 0) = color;
	}

	for (int y = 0; y < markers.rows; y++)
		for (int x = 0; x < markers.cols; x++) {
			int k = markers.at<int>(y, x);
			if (k == -1)
				color[0] = color[1] = color[2] = 255;
			else if (k <= 0 || k > contours.size()+1)
				color[0] = color[1] = color[2] = 0;
			else {
				color = colorTable.at<Vec3b>(k - 1, 0);
				dstImage.at<Vec3b>(y, x) = color;
			}
		}
	addWeighted(dstImage, 0.5, srcImage, 0.5, 0, dstImage);
	imshow("dstImage", dstImage);*/

	//0816
	/*Mat srcImage = imread("SegmentTest.jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;

	int level = 4;
	int th1 = 100;
	int th2 = 30;
	vector<Rect>rects;
	Mat dstImage;
	rects = PyrSegmentation(srcImage, dstImage, level, th1, th2);
	cout << "rects.size()=" << rects.size() << endl;

	Mat dstImageColor;
	cvtColor(dstImage, dstImageColor, COLOR_GRAY2BGR);
	for (int i = 0; i < rects.size(); i++)
		rectangle(dstImageColor, rects[i], Scalar(0, 0, 255), 2);
	imshow("srcImage", srcImage);
	imshow("dstImageColor", dstImageColor);*/

	//0817
	/*//Mat srcImage = imread("SegmentTest.jpg");
	Mat srcImage = imread("lena.jpg");
	if (srcImage.empty())
		return -1;

	int maxLevel = 4;
	double sp = 10;
	double sr = 40;

	Mat dstImage;
	pyrMeanShiftFiltering(srcImage, dstImage, sp, sr, maxLevel);
	floodFillPostProcess(dstImage, Scalar::all(2));
	imshow("srcImage", srcImage);
	imshow("dstImage", dstImage);*/

	//0818
	/*Scalar colorTable[MAX_CLUSTERS] = { Scalar(255,0,0),Scalar(0,255,0),Scalar(100,100,255),Scalar(255.0,255) };
	Mat dstImage(512, 512, CV_8UC3, Scalar::all(255));
	imshow("dstImage", dstImage);
	setMouseCallback("dstImage", onMouse, (void*)&dstImage);

	int K = 2;
	int attempts = 2;
	int flags = KMEANS_RANDOM_CENTERS;
	TermCriteria criteria(TermCriteria::COUNT + TermCriteria::EPS, 10, 1.0);
	bool bEscKey = false;
	int nKey;
	while (!bEscKey) {
		nKey = waitKey(0);
		switch (nKey) {
		case 27:
			bEscKey = true;
			break;
		case 'r':
			g_points.clear();
			dstImage = Scalar::all(255);
			imshow("dstImage", dstImage);
			break;
		case ' ':
			if (g_points.size() < 1)
				break;
			Mat labels, centers;
			Mat samples(g_points.size(), 1, CV_32FC2);
			for (int i = 0; i < g_points.size(); i++) {
				Point pt = g_points[i];
				samples.at<Point2f>(i, 0) = Point2f(pt.x, pt.y);
			}
			kmeans(samples, K, labels, criteria, attempts, flags, centers);

			//cluster
			for (int i = 0; i < g_points.size(); i++) {
				int k = labels.at<int>(i);
				Point pt = g_points[i];
				circle(dstImage, pt, 10, colorTable[k], -1);
			}

			//center
			for (int i = 0; i < K; i++) {
				Point pt = centers.at<Point2f>(i, 0);
				circle(dstImage, pt, 8, colorTable[i], -1);
				circle(dstImage, pt, 10, Scalar(0, 0, 255), 2);
			}
			imshow("dstImage", dstImage);
			break;

		}
	}*/

	//0819
	/*Mat srcImage = imread("hand.jpg");
	if (srcImage.empty())
		return -1;
	int K = 8;
	Mat colorTable(K, 1, CV_8UC3);
	Vec3b color;
	for (int k = 0; k < K; k++) {
		color[0] = rand() & 180 + 50;
		color[1] = rand() & 180 + 50;
		color[2] = rand() & 180 + 50;
		colorTable.at<Vec3b>(k, 0) = color;
	}
	Mat dstImage(srcImage.size(), srcImage.type());

	int attempts = 1;
	int flags = KMEANS_RANDOM_CENTERS;
	TermCriteria criteria(TermCriteria::COUNT + TermCriteria::EPS, 10, 1.0);

	Mat samples = srcImage.reshape(3, srcImage.rows*dstImage.cols);
	samples.convertTo(samples, CV_32FC3);

	Mat labels;
	kmeans(samples, K, labels, criteria, attempts, flags);

	for(int y=0, k=0;y<srcImage.rows;y++)
		for (int x = 0; x < srcImage.cols; x++, k++) {
			int idx = labels.at<int>(k, 0);
			color = colorTable.at<Vec3b>(idx, 0);
			dstImage.at<Vec3b>(y, x) = color;
		}
	imshow("dsrImage", dstImage);*/

	//0820
	Mat dstImage(512, 512, CV_8UC3, Scalar::all(255));
	imshow("dstImage", dstImage);
	setMouseCallback("dstImage", onMouse, (void*)&dstImage);

	bool bEscKey = false;
	int nKey;
	while (!bEscKey) {
		nKey = waitKey(0);
		switch (nKey) {
		case 27:
			bEscKey = true;
			break;
		case 'r':
			g_points.clear();
			dstImage = Scalar::all(255);
			imshow("dstImage", dstImage);
			break;
		case ' ':
			if (g_points.size() < 1)
				break;
			vector<int> labels;
			int K;
			K = partition(g_points, labels, ClosePoints(100));
			cout << "#of clusters, K=" << K << endl;

			Mat colorTable(K, 1, CV_8UC3);
			Vec3b color;
			for (int k = 0; k < K; k++) {
				color[0] = rand() & 180 + 50;
				color[1] = rand() & 180 + 50;
				color[2] = rand() & 180 + 50;
				colorTable.at<Vec3b>(k, 0) = color;
			}

			//cluster
			for (int i = 0; i < g_points.size(); i++) {
				int k = labels[i];
				Point pt = g_points[i];
				color = colorTable.at<Vec3b>(k, 0);
				circle(dstImage, pt, 10, Scalar(color), -1);
			}

			imshow("dstImage", dstImage);
			break;

		}

		waitKey();
		return 0;
	}
}

/*void floodFillPostProcess(Mat& img, const Scalar& colorDiff=Scalar::all(1)) {
	RNG rng = theRNG();
	Mat mask(img.rows + 2, img.cols + 2, CV_8U, Scalar::all(0));
	for(int y=0;y<img.rows; y++)
		for (int x = 0; x < img.cols; x++) {
			if (mask.at<uchar>(y + 1, x + 1) == 0) {
				Scalar newVal(rng(256), rng(256), rng(256));
				floodFill(img, mask, Point(x, y), newVal, 0, colorDiff, colorDiff);
			}
		}
}

vector<Rect> PyrSegmentation(Mat &src, Mat &dst, int level, int th1, int th2) {
	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq *components = 0;

	IplImage srcImage = src;
	dst.release();
	dst.create(src.size(), src.type());
	IplImage segImage = dst;
	cvPyrSegmentation(&srcImage, &segImage, storage, &components, level, (double)th1, (double)th2);
	
	vector<Rect> rects;
	CvSeq *first_contour = 0;
	for (int i = 0; i < components->total; i++) {
		CvConnectedComp* comp = (CvConnectedComp*)cvGetSeqElem(components, i);
		if (cvRound(comp->value.val[0]) == 0)
			continue;
		Rect r = comp->rect;
		rects.push_back(r);
	}
	//cvReleaseMemStorage(&storage);
	return rects;
}

void Printmat(const char *strName, Mat A) {
	int x, y;
	uchar uValue;
	float fValue;
	double dValue;
	int iValue;

	cout << endl << endl << strName << endl;
	cout << setiosflags(ios::fixed);
	for (y = 0; y < A.rows; y++) {
		for (x = 0; x < A.cols; x++) {
			switch (A.type()) {
			case CV_8U:
				uValue = A.at<uchar>(y, x);
				cout << setw(4) << (int)uValue;
				break;
			case CV_32S:
				iValue = A.at<int>(y, x);
				cout << setw(4) << iValue;
				break;
			case CV_32F:
				fValue = A.at<float>(y, x);
				cout << setprecision(1) << setw(5) << fValue;
				break;
			case CV_64F:
				dValue = A.at<double>(y, x);
				cout << setprecision(1) << setw(5) << dValue;
				break;
			}
		}
		cout << endl;
	}
	cout << endl;
}*/

void onMouse(int event, int x, int y, int flags, void * params) {
	Mat *data = (Mat*)params;
	Mat dstImage = *data;

	switch (event) {
	case EVENT_FLAG_LBUTTON:
		circle(dstImage, Point(x, y), 10, Scalar::all(0), -1);
		g_points.push_back(Point(x, y));
		break;
	}
	imshow("dstImage", dstImage);
}

/*void onMouse(int event, int x, int y, int flags, void * params) {
	DATA *data = (DATA*)params;
	Mat mask = data->mask;
	Mat dstImage = data->image;

	switch (event) {
	case EVENT_MOUSEMOVE:
		if (flags & EVENT_FLAG_LBUTTON) {
			circle(mask, Point(x, y), 10, Scalar::all(255), -1);
			circle(dstImage, Point(x, y), 10, Scalar::all(255), -1);
		}
	}
	imshow("dstImage", dstImage);
}*/