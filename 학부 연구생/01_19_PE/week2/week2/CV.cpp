#include "pch.h"
#include "opencv.hpp"
#include <fstream>
using namespace cv;
using namespace std;

void onMouse(int event, int x, int y, int flags, void* param);
void onChange(int pos, void *param);

int main()
{
	//0301
	/*Mat dstImage(512, 512, CV_8UC3, Scalar(255, 255, 255));

	//rectangle(dstImage, Point(100, 100), Point(400, 400), Scalar(0, 0, 255), 2);

	line(dstImage, Point(400, 100), Point(100, 400), Scalar(0, 255, 0),4,8,0);
	line(dstImage, Point(400, 100), Point(100, 400), Scalar(0, 255, 0),4,4,1);
	line(dstImage, Point(400, 100), Point(100, 400), Scalar(0, 255, 0), 4, CV_AA, 2);

	//rectangle(dstImage, Point(400 / 2, 100 / 2), Point(100 / 2, 400.2), Scalar(255, 0, 0));*/
	
	//0302
	/*Mat dstImage(512, 512, CV_8UC3, Scalar(255, 255, 255));
	if (dstImage.empty())
		return -1;

	Rect imgRect(100, 100, 300, 300);
	rectangle(dstImage, imgRect.tl(), imgRect.br(), Scalar(255, 0, 0), 2);
	
	Point pt1(0, 50), pt2(0, 100);
	line(dstImage, pt1, pt2, Scalar(0, 255, 0), 2);

	clipLine(imgRect, pt1, pt2);
	cout << pt1 << endl;
	cout << pt2 << endl;

	circle(dstImage, pt1, 5, Scalar(0, 0, 255), 2);
	circle(dstImage, pt2, 5, Scalar(0, 0, 255), 2);
	line(dstImage, pt1, pt2, Scalar(255, 0, 0), 2);

	imshow("dstImage", dstImage);*/

	//0303
	/*Mat srcImage = imread("lena.jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;

	Point pt1(10, 10), pt2(10, 400);
	LineIterator it(srcImage, pt1, pt2, 4);

	vector<uchar> buffer(it.count);
	for (int i = 0; i < it.count; i++, ++it) {
		buffer[i] = **it;
	}
	cout << (Mat)buffer << endl;
	cout << it.count << endl;
	line(srcImage, pt1, pt2, Scalar(255), 2);

	Mat dstImage(512, 512, CV_8UC3, Scalar(255, 255, 255));
	pt1 = Point(0, dstImage.cols - buffer[0]);
	for(int i=1; i<buffer.size();i++,++it){
		pt2 = Point(i, dstImage.cols - buffer[i]);
		line(dstImage, pt1, pt2, Scalar(255), 2);
		pt1 = pt2;
	}
	imshow("scrImage", srcImage);
	imshow("dstImage", dstImage);*/

	//0304
	/*Mat dstImage(512, 512, CV_8UC3, Scalar(255, 255, 255));
	rectangle(dstImage, Point(100, 100), Point(400, 400), Scalar(0, 0, 255));
	line(dstImage,Point(250, 100), Point(250, 400), Scalar(0, 0, 255));
	line(dstImage,Point(100,250),Point(400,250),Scalar(255,0,0));
	circle(dstImage, Point(250, 250), 150, Scalar(255, 0, 0));

	circle(dstImage, Point(250, 250), 50, Scalar(0, 255, 0), -1);
	imshow("dst", dstImage);*/

	//0305
	/*Mat dstImage(512, 512, CV_8UC3, Scalar(255, 255, 255));
	Point center(250, 200);
	Size size(200, 100);
	rectangle(dstImage, Point(center.x - size.width, center.y - size.height), Point(center.x + size.width, center.y + size.height), Scalar(255, 0, 0));
	
	line(dstImage, Point(center.x - size.width, center.y), Point(center.x + size.width, center.y), Scalar(0, 255, 0));
	line(dstImage, Point(center.x, center.y - size.height), Point(center.x, center.y - size.height), Scalar(0, 255, 0));
	
	ellipse(dstImage, center, size, 0, 0, 360, Scalar(0, 0, 255));
	//ellipse(dstImage, center, size, 90, 45, 360, Scalar(0, 0, 255),2);

	RotatedRect box(center, size, 90);
	ellipse(dstImage, box, Scalar(255, 0, 0), 2);

	vector<Point> pts;
	ellipse2Poly(center, size, 90, 0, 360, 45, pts);
	polylines(dstImage, pts, true, Scalar(0, 255, 0), 4);

	Point pt1, pt2;
	for (int i = 0; i < pts.size(); i++) {
		pt1 = pts[i];
		if (i == pts.size() - 1)
			pt2 = pts[0];
		else
			pt2 = pts[i + 1];
		line(dstImage, pt1, pt2, Scalar(0, 0, 255));
	}
	imshow("d", dstImage);*/

	//0306
	/*Mat dstImage(512, 512, CV_8UC3, Scalar(255, 255, 255));
	Point pts1[4] = { Point(100,100), Point(200,100),Point(200,200),Point(100,200) };
	Point pts2[3] = { Point(300,200),Point(400,100),Point(400,200) };

	const Point *polygons[2] = { pts1, pts2 };
	int npts[2] = { 4,3 };

	polylines(dstImage, polygons, npts, 2, true, Scalar(255, 0, 0));
	//fillConvexPoly(dstImage, polygons[0], npts[0], Scalar(0, 0, 255));
	//fillConvexPoly(dstImage, polygons[1], npts[1], Scalar(255, 0, 0));
	fillPoly(dstImage, polygons, npts, 2, Scalar(0, 0, 255));
	imshow("d", dstImage);*/

	//0307
	/*Mat dstImage(512, 512, CV_8UC3, Scalar(255, 255, 255));

	vector<vector<Point>> contour(2, vector<Point>());
	contour[0].push_back(Point(100, 100));
	contour[0].push_back(Point(200, 100));
	contour[0].push_back(Point(200, 200));
	contour[0].push_back(Point(100, 200));

	contour[1].push_back(Point(300, 200));
	contour[1].push_back(Point(400, 100));
	contour[1].push_back(Point(400, 200));
	
	const cv::Point * pts1 = (const cv::Point*)Mat(contour[0]).data;
	const cv::Point * pts2 = (const cv::Point*)Mat(contour[1]).data;

	const Point *polygon[2] = { pts1,pts2 };
	int npts[2] = { contour[0].size(),contour[1].size() };

	polylines(dstImage, polygon, npts, 2, true, Scalar(255, 0, 0));
	imshow("d", dstImage);*/

	//0308
	/*Mat dstImage(512, 512, CV_8UC3, Scalar(255, 255, 255));

	string text = "OpenCV Programming";
	int fontFace = FONT_HERSHEY_SIMPLEX;
	double fontScale = 1.0;
	int thickness = 1;
	int baseLine;
	Point org(100, 100);

	putText(dstImage, text, org, fontFace, fontScale, Scalar(0, 0, 0));
	Size size = getTextSize(text, fontFace, fontScale, thickness, &baseLine);

	rectangle(dstImage, org, Point(org.x + size.width, org.y - size.height), Scalar(0, 0, 255));
	circle(dstImage, org, 3, Scalar(255, 0, 0), 2);
	imshow("d", dstImage);*/

	//0309
	/*Mat srcImage = imread("lena.jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;

	namedWindow("srcImage", WINDOW_NORMAL);
	imshow("srcImage", srcImage);

	waitKey();

	resizeWindow("srcImage", 320, 240);
	waitKey();
	destroyAllWindows();*/

	//0310
	/*Mat srcImage = imread("lena.jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;

	namedWindow("srcImage");
	imshow("srcImage", srcImage);
	int x = 100;
	int y = 100;
	moveWindow("srcImage", x, y);

	int nKey;
	while (1) {
		nKey = waitKey(0);
		if (nKey == 0x1B)
			break;
		switch (nKey) {
		
		case 0x250000:
			x -= 10;
			break;
		
		case 0x270000:
			x += 10; 
			break;

		case 0x260000:
			y -= 10;
			break;

		case 0x280000:
			y += 10;
			break;
		}
		moveWindow("srcImage", x, y);
	}*/

	//0311
	/*Mat dstImage(512, 512, CV_8UC3, Scalar(255, 255, 255));

	imshow("dstImage", dstImage);
	setMouseCallback("dstImage", onMouse, (void*)&dstImage);

	waitKey();*/

	//0312
	/*Mat image[2];
	image[0] = imread("lena.jpg", IMREAD_GRAYSCALE);
	if (image->empty())
		return -1;
	image[1].create(image[0].size(), CV_8U);

	imshow("image", image[0]);

	int pos = 128;
	onChange(pos, (void*)image);
	createTrackbar("threshold", "image", &pos, 255, onChange, (void*)image);
	waitKey();*/

	//0313
	/*Mat srcImage1 = imread("lena.jpg", -1);
	if (srcImage1.empty())
		return -1;
	cout << "srcImage1" << endl;
	cout << "type : " << srcImage1.type() << endl;
	cout << "depth : " << srcImage1.depth() << endl;
	cout << "channels : " << srcImage1.channels() << endl<<endl;

	Mat srcImage2 = imread("lena.jpg", IMREAD_COLOR);
	if (srcImage2.empty())
		return -1;
	cout << "srcImage2" << endl;
	cout << "type : " << srcImage2.type() << endl;
	cout << "depth : " << srcImage2.depth() << endl;
	cout << "channels : " << srcImage2.channels() << endl << endl;

	Mat srcImage3 = imread("lena.jpg", IMREAD_GRAYSCALE);
	if (srcImage3.empty())
		return -1;
	cout << "srcImage3" << endl;
	cout << "type : " << srcImage3.type() << endl;
	cout << "depth : " << srcImage3.depth() << endl;
	cout << "channels : " << srcImage3.channels() << endl << endl;

	imwrite("lena.bmp", srcImage1);

	vector<int> params;
	params.push_back(IMWRITE_JPEG_QUALITY);
	params.push_back(100);
	imwrite("lena2.jpg", srcImage3, params);

	params.clear();
	params.push_back(IMWRITE_PNG_COMPRESSION);
	params.push_back(9);
	imwrite("lena3.jpg", srcImage3, params);

	imshow("srcImage1", srcImage1);
	imshow("srcImage2", srcImage2);
	imshow("srcImage3", srcImage3);
	waitKey();*/

	//0314
	Mat srcImage(512, 512, CV_8UC3, Scalar::all(255));
	rectangle(srcImage, Point(100, 100), Point(400, 400), Scalar(255, 0, 0), -1);

	vector<uchar> buf1;
	imencode(".bmp", srcImage, buf1);
	Mat dstImage1 = imdecode(buf1, IMREAD_COLOR);

	imshow("dstImage1", dstImage1);
	ofstream outfile1("test.bmp", ios::binary);
	outfile1.write((const char*)buf1.data(), buf1.size());
	outfile1.close();

	vector<int> params;
	params.push_back(IMWRITE_JPEG_QUALITY);
	params.push_back(90);

	vector<uchar> buf2;
	imencode(".jpg", srcImage, buf2);
	Mat dstImage2 = imdecode(buf2, IMREAD_COLOR);

	imshow("dstImage2", dstImage2);
	ofstream outfile2("test.jpg", ios::binary);
	outfile2.write((const char*)buf2.data(), buf2.size());
	outfile2.close();

	params.clear();
	params.push_back(IMWRITE_PNG_COMPRESSION);
	params.push_back(9);
	
	vector<uchar> buf3;
	imencode(".png", srcImage, buf3);
	Mat dstImage3 = imdecode(buf3, IMREAD_COLOR);

	imshow("dstImage3", dstImage2);
	ofstream outfile3("test.png", ios::binary);
	outfile3.write((const char*)buf3.data(), buf3.size());
	outfile3.close();
	waitKey();
	return 0;

}  

void onChange(int pos, void *param){
	Mat *pMat = (Mat *)param;
	Mat srcImage = Mat(pMat[0]);
	Mat dstImage = Mat(pMat[1]);

	int x, y, s, r;
	int nThreshod = pos;
	for(y=0;y<srcImage.rows;y++)
		for (x = 0; x < srcImage.cols; x++)
		{
			r = srcImage.at<uchar>(y, x);
			if (r > nThreshod)
				s = 255;
			else
				s = 0;
			dstImage.at<uchar>(y, x) = s;
		}
	imshow("image", dstImage);
}


void onMouse(int event, int x, int y, int flags, void* param) {
	Mat *pMat = (Mat*)param;
	Mat image = Mat(*pMat);
	switch (event) {
	case EVENT_LBUTTONDOWN:
		if (flags & EVENT_FLAG_SHIFTKEY)
			rectangle(image, Point(x - 5, y - 5), Point(x + 5, y + 5), Scalar(255, 0, 0));
		else
			circle(image, Point(x, y), 5, Scalar(0, 0, 255), 5);
		break;

	case EVENT_RBUTTONDOWN:
		circle(image, Point(x, y), 5, Scalar(255, 0, 0), 5);
		break;

	case EVENT_LBUTTONDBLCLK:
		image = Scalar(255, 255, 255);
		break;
	}

	imshow("dstImage", image);
}