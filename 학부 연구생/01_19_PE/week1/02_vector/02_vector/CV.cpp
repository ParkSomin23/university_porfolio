#include "pch.h"
#include "opencv.hpp"
#include <time.h>
using namespace cv;
using namespace std;

//vec을 1차원 Point로
template<class T>
T* vec_to_arr(vector<T>v1) {
	T* v2 = new T[v1.size()];
	for (int i = 0; i < v1.size(); i++)
		v2[i] = v1[i];
	return v2;
}

template <class T>
void delete_arr(T* arr) {
	delete[] arr;
}

//vec을 2차원 Point로
template<class T>
T** vec_to_arr_arr(vector<vector<T>>v1) {
	T** v2 = new T*[v1.size()];
	for (int i = 0; i < v1.size(); i++)
	{
		v2[i] = new T[v1[i].size()];
		for (int j = 0; j < v1[i].size(); j++)
			v2[i][j] = v1[i][j];
	}
	return v2;
}

template <class T>
void delete_arr_arr(T** arr, int size) {
	for (int i = 0; i < size; i++)
		delete[] arr[i];
	delete[] arr;
}

int main()
{
	//0255
	/*Mat dstImage(512, 512, CV_8UC3, Scalar(255, 255, 255));

	vector<Point> contour;
	contour.push_back(Point(100, 100));
	contour.push_back(Point(200, 100));
	contour.push_back(Point(200, 200));
	contour.push_back(Point(100, 200));

	int npts[] = { contour.size() };
	int i;

	Point *P1 = &contour[0];
	for (i = 0; i < contour.size(); i++)
		cout << "P1[" << i << "]=" << P1[i] << endl;

	Point *P2 = (Point*)Mat(contour).data;
	for (i = 0; i < contour.size(); i++)
		cout << "P2[" << i << "]=" << P2[i] << endl;

	Point *P4 = vec_to_arr<Point>(contour);
	for (i = 0; i < contour.size(); i++)
		cout << "P4[" << i << "]=" << P4[i] << endl;

	polylines(dstImage, (const Point**)&P4, npts, 1, true, Scalar(0, 0, 255));
	delete_arr<Point> (P4);
	imshow("dstImage", dstImage);*/

	//0256
	/*Mat dstImage(512, 512, CV_8UC3, Scalar(255, 255, 255));

	vector<vector<Point>> contour(2, vector<Point>());
	contour[0].push_back(Point(100, 100));
	contour[0].push_back(Point(200, 100));
	contour[0].push_back(Point(200, 200));
	contour[0].push_back(Point(100, 200));

	contour[1].push_back(Point(300, 200));
	contour[1].push_back(Point(400, 100));
	contour[1].push_back(Point(400, 200));

	int npts[2] = { contour[0].size(),contour[1].size() };
	int i, j;

	Point *pts1, *pts2;
	pts1 = &contour[0][0];
	pts2 = &contour[1][0];
	Point *P1[] = { pts1, pts2 };

	for (i = 0; i < contour.size(); i++)
		for (j = 0; j < contour[i].size(); j++)
			cout << "P1[" << i << "]=" << P1[i][j] << endl;

	pts1 = (Point*)Mat(contour[0]).data;
	pts2 = (Point*)Mat(contour[1]).data;
	Point*P2[2] = { pts1,pts2 };
	for (i = 0; i < contour.size(); i++)
		for (j = 0; j < contour[i].size(); j++)
			cout << "P2[" << i << "][" << j << "]=" << P2[i][j] << endl;

	Point P3[2][4];
	copy(contour[0].begin(), contour[0].end(), P3[0]);
	copy(contour[1].begin(), contour[1].end(), P3[1]);
	for (i = 0; i < contour.size(); i++)
		for (j = 0; j < contour[i].size(); j++)
			cout << "P3[" << i << "][" << j << "]=" << P3[i][j] << endl;

	Point *ptrP3[] = { P3[0],P3[1] };

	Point **P4 = vec_to_arr_arr<Point>(contour);
	for (i = 0; i < contour.size(); i++)
		for (j = 0; j < contour[i].size(); j++)
			cout << "P4[" << i << "][" << j << "]=" << P4[i][j] << endl;

	polylines(dstImage, (const Point**)P4, npts, 2, true, Scalar(0, 0, 255));
	delete_arr_arr<Point>(P4, contour.size());

	imshow("dstImage", dstImage);
	waitKey();  */

	//0258
	/*FileStorage fs("test.xml", FileStorage::WRITE);

	time_t date;
	time(&date);
	fs << "Date" << asctime(localtime(&date));

	fs << "name" << "KDK";
	fs << "age" << 25;

	fs << "Images" << "[";
	fs << "Apple.jpg" << "Banana.jpg" << "Orange.jpg";
	fs << "]";

	fs << "Box";
	fs << "{" << "Left"<<100;
	fs << "Top" << 200;
	fs << "Right" << 300;
	fs << "Bottom" << 400 << "}";

	int arr[] = { 1,2,3,4,5,6,7, 8,9 };
	vector<int> V1(arr, arr + sizeof(arr) / sizeof(arr[0]));
	fs << "V1" << V1;

	Point2f ptCenter(256.0f, 256.0f);
	float angle = 45;
	double scale = 10.0;
	fs << "angle" << angle;
	fs << "scale" << scale;
	fs << "center" << ptCenter;

	Mat matR = getRotationMatrix2D(ptCenter, angle, scale);
	fs << "matR" << matR;
	fs.release();*/

	//0259
	FileStorage fs("test.xml", FileStorage::READ);

	if (!fs.isOpened()) {
		cerr << "The File is not oppend! FAIL" << endl;
		return 1;
	}
	string date;
	fs["Date"] >> date;
	cout << "Date:" << date << endl;

	string sName;
	fs["name"] >> sName;
	cout << "name:" << sName << endl;
	
	int nAge;
	fs["age"] >> nAge;
	cout <<"age:" << nAge << endl;

	float fAngle;
	fs["angle"] >> fAngle;
	cout << "angle:" << fAngle << endl;

	double dScale;
	fs["scale"] >> dScale;
	cout << "scale:" << dScale << endl;

	Point ptCenter;
	fs["center"] >> ptCenter;
	cout << "center:" << ptCenter << endl;

	FileNode node = fs["Images"];
	if (node.type() != FileNode::SEQ) {
		cerr << "It is not a sequnce! FAIL" << endl;
		return 1;
	}

	cout << "node[0]:"<<(string)node[0] << endl;
	cout << "node[1]:" << (string)node[1] << endl;
	cout << "node[2]:" << (string)node[2] << endl;

	cout << node.name() << "=[";
	FileNodeIterator it;
	for (it = node.begin(); it != node.end(); it++) {
		cout << (string)*it << ";";
	}
	cout << "]" << endl << endl;

	node = fs["Box"];
	if (node.type() != FileNode::MAP) {
		cerr << "It is not a mapping! FAIL" << endl;
		return 1;
	}
	cout << node.name() << "={";
	cout << "Left:" << (int)(node["Left"]) << ";";	
	cout << "Top:" << (int)(node["Top"]) << ";";
	cout << "Right:" << (int)(node["Right"]) << ";";
	cout << "Bottom:" << (int)(node["Bottom"]) << ";";

	vector<int> V1;
	fs["V1"] >> V1;
	cout << fs["V1"].name() << ":" << (Mat)V1 << endl << endl;
	Mat matR;
	fs["matR"] >> matR;
	cout << fs["matR"].name() << ":" << matR << endl << endl;
	fs.release();

	//0260
	/*Mat A(1, 3, CV_8U);
	int a = -1;
	float b = 2.6;
	double c = 300.4;
	A.at<uchar>(0, 0) = a;
	A.at<uchar>(0, 1) = b;
	A.at<uchar>(0, 2) = c;
	cout << "A" << A << endl << endl;

	cout << "saturate_cat<uchar>" << endl;
	A.at<uchar>(0, 0) = saturate_cast<uchar>(a);
	A.at<uchar>(0, 1) = saturate_cast<uchar>(b);
	A.at<uchar>(0, 2) = saturate_cast<uchar>(c);
	cout << "A" << A << endl << endl;*/
	
	//0261/*
	/*Mat A(1, 3, CV_8U, 100);
	int a = 0;
	int b = 2;
	cout << "A=" << A << endl;
	try {
		if (a != 0)
			CV_StsDivByZero;

		A /= a;
		cout << "A1=" << A << endl;

		if (b < 0 || b>3)
			CV_StsOutOfRange;

		A.at<uchar>(b) = saturate_cast<uchar>(300);
		cout << "A2=" << A << endl;
		CV_Assert(A.type() == CV_8UC3);
	}
	catch (cv::Exception& e) {
		const char* err_msg = e.what();
		cout << "Exception(" << e.code << "):" << err_msg << endl;
	}*/

	return 0;
}