#include "pch.h"
#include "opencv.hpp"
#include <time.h>
using namespace std;
using namespace cv;

//1207
/*const double MHI_DURATION = 1;
const double MAX_TIME_DELTA = 0.5;
const double MIN_TIME_DELTA = 0.05;
const int N = 4;*/

//1207
/*void DifferenceIFrames(Mat &src1, Mat &src2, Mat &dst, int nTh) {
	absdiff(src1, src2, dst);
	threshold(dst, dst, nTh, 255, THRESH_BINARY);
}

void Mhi2MotionImage(Mat &mhi, Mat &motion, Mat &mask, double timeStamp) {
	if (motion.empty())
		motion.create(mhi.size(), CV_8UC3);
	double scale = 255 / MHI_DURATION;
	double t = MHI_DURATION - timeStamp;
	mask = mhi * scale + t * scale;
	mask.convertTo(mask, CV_8U);
	motion = Scalar::all(0);
	Mat tmp = Mat::zeros(mhi.size(), CV_8U);
	Mat outImage[] = { mask, tmp, tmp };
	merge(outImage, 3, motion);
}

void DrawMotionOrientation(vector<Rect> rects, Mat &silh, Mat &mhi, Mat &orient, Mat &mask, Mat &dstImage, double timeStamp) {
	int i, x, y;
	int count;
	Rect comp_rect;
	Scalar color;
	Point center;
	double r, angle;
	Size size = dstImage.size();

	for (i = -1; i < (int)rects.size(); i++) {
		if (i < 0) {
			comp_rect = Rect(0, 0, size.width, size.height);
			color = Scalar(0, 0, 255);
			r = 100;
		}
		else {
			comp_rect = rects[i];
			if (comp_rect.width *comp_rect.height < 100)
				continue;
			color = Scalar(0, 255, 0);
			r = 30;
		}
		Mat silhROI = silh(comp_rect);
		Mat mhiROI = mhi(comp_rect);
		Mat orientROI = orient(comp_rect);
		Mat maskROI = mask(comp_rect);

		angle = calcGlobalOrientation(orientROI, maskROI, mhiROI, timeStamp, MHI_DURATION);
		angle = 360.0 - angle;

		count = countNonZero(silhROI);
		if (count < comp_rect.width*comp_rect.height*0.001)
			continue;
		center = Point((comp_rect.x + comp_rect.width / 2), (comp_rect.y + comp_rect.height / 2));
		circle(dstImage, center, cvRound(r*1.2), color, 3, -1);
		x = cvRound(center.x + r * cos(angle*CV_PI / 180));
		y= cvRound(center.y - r * sin(angle*CV_PI / 180));
		line(dstImage, center, Point(x, y), color, 3, -1);
	}
}*/

//1208
/*#define MAX_POINTS 16
Point g_pt1, g_pt2;
bool g_bLeftDownAndMove = false;
bool g_bROI = false;

//void onMouse
/*void OnMouse(int mevent, int x, int y, int flags, void *param) {
	switch (mevent)
	{
	case EVENT_LBUTTONDOWN:
		g_bLeftDownAndMove = false;
		g_pt1 = Point(x, y);
		break;
	case EVENT_MOUSEMOVE:
		if (flags == EVENT_FLAG_LBUTTON) {
			g_pt2 = Point(x, y);
			g_bLeftDownAndMove = true;
		}
		break;
	case EVENT_LBUTTONUP:
		g_pt2 = Point(x, y);
		g_bROI = true;
		g_bLeftDownAndMove = false;
		break;
	}
}

void DrawTrackingPoints(vector<Point2f>&points, Mat &image) {
	for (int i = 0; i < points.size(); i++) {
		int x = cvRound(points[i].x);
		int y = cvRound(points[i].y);
		circle(image, Point(x, y), 3, Scalar(255, 0, 0), 2);
	}
}*/

//1209
/*#define THRESHOLD 3

void DrawOpticalFlow(Mat &flow, Mat &image) {
	int x, y;

	Point pt1, pt2;
	Size size = image.size();
	Size shiftSize = Size(4, 4);

	for(y=0; y<size.height; y+=shiftSize.height)
		for (x = 0; x < size.width; x += shiftSize.width) {
			Point2f delta = flow.at<Point2f>(y, x);
			float len = sqrt(delta.x*delta.x + delta.y*delta.y);
			if (len < THRESHOLD)
				continue;
			pt1.x = x;
			pt1.y = y;
			pt2.x = cvRound(pt1.x + delta.x);
			pt2.y = cvRound(pt1.y + delta.y);
			line(image, pt1, pt2, Scalar(255, 0, 0));
		}
}*/

//1210 ~ 17
Rect selection;
bool bLButtonDown = false;
typedef enum { INIT, CALC_HIST, TRACKING } STATUS;
STATUS trackingMode = INIT;

void OnMouse(int mevent, int x, int y, int flags, void *param) {
	static Point origin;
	Mat *pMat = (Mat*)param;
	Mat image = Mat(*pMat);
	if (bLButtonDown) {
		selection.x = MIN(x, origin.x);
		selection.y = MIN(y, origin.y);
		selection.width = selection.x + abs(x - origin.x);
		selection.height = selection.y + abs(y - origin.y);

		selection.x = MAX(selection.x, 0);
		selection.y = MAX(selection.y, 0);
		selection.width = MIN(selection.width, image.cols);
		selection.height = MIN(selection.height, image.rows);
		selection.width -= selection.x;
		selection.height -= selection.y;
	}
	switch (mevent)
	{
	case EVENT_LBUTTONDOWN:
		origin = Point(x, y);
		selection = Rect(x, y, 0, 0);
		bLButtonDown = true;
		break;
	case EVENT_LBUTTONUP:
		bLButtonDown = false;
		if (selection.width > 0 && selection.height > 0)
			trackingMode = CALC_HIST;
		break;
	}
}

//1217
#define DIST_TH 0.4

int main() {
	//1201
	/*VideoCapture capture("Wildlife.wmv");
	if (!capture.isOpened()) {
		cout << "cannot open capture!" << endl;
		return 0;
	}
	int ex = (int)(capture.get(CV_CAP_PROP_FOURCC));
	char fourcc[] = { ex & 0XFF, (ex & 0XFF00) >> 8, (ex & 0XFF0000) >> 16, (ex & 0XFF000000) >> 24, 0 };
	cout << "fourcc=" << fourcc << endl;

	Size size = Size((int)capture.get(CV_CAP_PROP_FRAME_WIDTH), (int)capture.get(CV_CAP_PROP_FRAME_HEIGHT));
	cout << "Size=" << size << endl;

	int fps = (int)(capture.get(CV_CAP_PROP_FPS));
	cout << "fps=" << fps << endl;

	int delay = 1000 / fps;
	int frameNum = -1;
	Mat frame, grayImage, edgeImage;
	namedWindow("frame", WINDOW_AUTOSIZE);
	namedWindow("edgeImage", WINDOW_AUTOSIZE);
	for (;;) {
		capture >> frame;
		if (frame.empty())
			break;
		cvtColor(frame, grayImage, COLOR_BGR2GRAY);
		Canny(grayImage, edgeImage, 80, 150, 3);

		imshow("frame", frame);
		imshow("edgeImage", edgeImage);
		int ckey = waitKey(delay);
		if (ckey == 27)	break;
	}*/

	//1202
	/*VideoCapture capture(0);
	if (!capture.isOpened())
		return 0;
	Size size = Size((int)capture.get(CV_CAP_PROP_FRAME_WIDTH), (int)capture.get(CV_CAP_PROP_FRAME_HEIGHT));
	cout << "size=" << size << endl;

	imshow("frame", NULL);
	waitKey(100);

	int delay = 30;
	int frameNum = -1;
	Mat frame, grayImage, edgeImage;
	namedWindow("frame", WINDOW_AUTOSIZE);
	namedWindow("edgeImage", WINDOW_AUTOSIZE);
	for (;;) {
		capture >> frame;
		cvtColor(frame, grayImage, COLOR_BGR2GRAY);
		Canny(grayImage, edgeImage, 80, 150, 3);

		imshow("frame", frame);
		imshow("edgeImage", edgeImage);
		int cKey = waitKey(delay);
		if (cKey == 27) break;
	}*/

	//1203
	/*VideoCapture inputVideo(0);
	if (!inputVideo.isOpened()) {
		return 0;
	}
	Size size((int)inputVideo.get(CV_CAP_PROP_FRAME_WIDTH), (int)inputVideo.get(CV_CAP_PROP_FRAME_HEIGHT));
	cout << "size=" << size << endl;

	int fourcc = -1;
	double fps = 24;
	bool isColor = true;
	VideoWriter outputVideo("output.avi", fourcc, fps, size, isColor);
	if (!outputVideo.isOpened())
		return 0;
	if (fourcc != -1) {
		imshow("frame", NULL);
		waitKey(100);
	}
	int delay = 1000 / fps;
	Mat frame;
	for (;;) {
		inputVideo >> frame;
		if (frame.empty())
			break;

		outputVideo << frame;
		imshow("frame", frame);

		int ckey = waitKey(delay);
		if (ckey == 27) break;
	}*/

	//1204
	/*VideoCapture inputVideo("video2.avi");
	if (!inputVideo.isOpened())
		return 0;

	Size size = Size((int)inputVideo.get(CV_CAP_PROP_FRAME_WIDTH), (int)inputVideo.get(CV_CAP_PROP_FRAME_HEIGHT));
	cout << "size=" << size << endl;

	int fps = (int)(inputVideo.get(CV_CAP_PROP_FPS));
	cout << "fps=" << fps << endl;

	int frameNum = 0;
	int delay = 1000 / fps;
	Mat frame, grayImage;
	Mat sumImage(size, CV_32F, Scalar::all(0));
	for (;;) {
		inputVideo >> frame;
		if (frame.empty())
			return 0;
		cvtColor(frame, grayImage, COLOR_BGR2GRAY);
		accumulate(grayImage, sumImage);
		imshow("frame", frame);
		frameNum++;
		int ckey = waitKey(delay);
		if (ckey == 27) break;
	}

	sumImage = sumImage / (float)frameNum;
	imwrite("BkgImage2.jpg", sumImage);*/

	//1205
	/*VideoCapture inputVIdeo("video2.avi");
	if (!inputVIdeo.isOpened())
		return -1;

	Size size = Size((int)inputVIdeo.get(CV_CAP_PROP_FRAME_WIDTH), (int)inputVIdeo.get(CV_CAP_PROP_FRAME_HEIGHT));
	cout << "size=" << size << endl;

	int fps = (int)(inputVIdeo.get(CV_CAP_PROP_FPS));
	cout << "fps=" << fps << endl;

	Mat bkgImage = imread("BkgImage2.jpg", IMREAD_GRAYSCALE);
	if (bkgImage.empty())
		return 0;

	int nTh = 150;
	int frameNum = 0;
	int delay = 1000 / fps;
	Mat frame, grayImage, diffImage;
	for (;;) {
		inputVIdeo >> frame;
		if (frame.empty())
			break;
		cout << "frameNum:" << frameNum << endl;
		cvtColor(frame, grayImage, COLOR_BGR2GRAY);
		GaussianBlur(grayImage, grayImage, Size(5, 5), 0.5);

		absdiff(grayImage, bkgImage, diffImage);
		threshold(diffImage, diffImage, nTh, 255, THRESH_BINARY);

		frameNum++;
		imshow("grayImage", grayImage);
		imshow("diffImage", diffImage);
		int ckey = waitKey(delay);
		if (ckey == 27) break;
	}*/

	//1206
	/*VideoCapture inputVIdeo("video2.avi");
	if (!inputVIdeo.isOpened())
		return -1;

	Size size = Size((int)inputVIdeo.get(CV_CAP_PROP_FRAME_WIDTH), (int)inputVIdeo.get(CV_CAP_PROP_FRAME_HEIGHT));
	cout << "size=" << size << endl;

	int fps = (int)(inputVIdeo.get(CV_CAP_PROP_FPS));
	cout << "fps=" << fps << endl;

	Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));

	float alpha = 0.02;
	int nTh = 50;
	int frameNum = -1;
	int delay = 1000 / fps;
	Mat frame, grayImage;
	Mat avgImage, diffImage, mask;
	for (;;) {
		inputVIdeo >> frame;
		if (frame.empty())
			break;
		frameNum++;
		cout << "frameNum:" << frameNum << endl;

		cvtColor(frame, grayImage, COLOR_BGR2GRAY);
		GaussianBlur(grayImage, grayImage, Size(5, 5), 0.5);
		if (frameNum == 0) {
			avgImage = grayImage;
			continue;
		}

		avgImage.convertTo(avgImage, CV_32F);
		grayImage.convertTo(grayImage, CV_32F);
		absdiff(grayImage, avgImage, diffImage);
		threshold(diffImage, mask, nTh, 255, THRESH_BINARY);
		mask.convertTo(mask, CV_8U);

		erode(mask, mask, kernel, Point(-1, -1), 2);
		dilate(mask, mask, kernel, Point(-1, -1), 3);
		imshow("mask", mask);

		bitwise_not(mask, mask);
		accumulateWeighted(grayImage, avgImage, alpha, mask);

		avgImage.convertTo(avgImage, CV_8U);
		imshow("avgImage", avgImage);

		int ckey = waitKey(delay);
		if (ckey == 27) break;
	}*/

	//1207
	/*VideoCapture inputVideo("video2.avi");
	if (!inputVideo.isOpened())
		return -1;
	Size size = Size((int)inputVideo.get(CV_CAP_PROP_FRAME_WIDTH), (int)inputVideo.get(CV_CAP_PROP_FRAME_HEIGHT));
	cout << "size=" << size << endl;

	int fps = (int)(inputVideo.get(CV_CAP_PROP_FPS));
	cout << "fps=" << fps << endl;

	double timeStamp;
	int nTh = 50;
	int last = 0;
	int prev, curr;

	int frameNum = -1;
	int delay = 1000 / fps;
	Mat frame, dstImage;
	Mat silh, orient, motion, mask, segmask;
	Mat mhi(size, CV_32F, Scalar::all(0));
	vector<Mat> buffer(N);
	vector<Rect> boundingRects;

	for (;;) {
		inputVideo >> frame;
		if (frame.empty())
			break;
		frameNum++;

		cvtColor(frame, buffer[last], COLOR_BGR2GRAY);
		curr = last;
		prev = (curr + 1) % N;
		last = prev;
		silh = buffer[prev];

		if (frameNum < N)
			continue;
		DifferenceIFrames(buffer[prev], buffer[curr], silh, nTh);
		imshow("silh", silh);

		timeStamp = (double)clock() / CLOCKS_PER_SEC;
		updateMotionHistory(silh, mhi, timeStamp, MHI_DURATION);
		Mhi2MotionImage(mhi, motion, mask, timeStamp);
		imshow("motion", motion);
		calcMotionGradient(mhi, mask, orient, MAX_TIME_DELTA, MIN_TIME_DELTA, 3);
		segmentMotion(mhi, segmask, boundingRects, timeStamp, MAX_TIME_DELTA);
		frame.copyTo(dstImage);
		if (boundingRects.size() > 0)
			DrawMotionOrientation(boundingRects, silh, mhi, orient, mask, dstImage, timeStamp);
		imshow("dstImage", dstImage);

		int ckey = waitKey(delay);
		if (ckey == 27) break;
	}*/

	//1208
	/*VideoCapture inputVideo("checkBoard3x3.avi");
	if (!inputVideo.isOpened())
		return 0;

	Size size = Size((int)inputVideo.get(CV_CAP_PROP_FRAME_WIDTH), (int)inputVideo.get(CV_CAP_PROP_FRAME_HEIGHT));
	cout << "size=" << size << endl;

	int fps = 24;
	Mat currImage, prevImage;
	Mat frame, dstImage;
	namedWindow("dstImage");
	setMouseCallback("dstImage", OnMouse, NULL);

	int fourcc = CV_FOURCC('D', 'I', 'V', 'X');
	bool isColor = true;
	VideoWriter outputVideo("trackingRect.avi", fourcc, fps, size, isColor);
	
	if (!outputVideo.isOpened()) {
		return 0;
	}

	if (!fourcc != -1) {
		imshow("dstImage", NULL);
		waitKey(100);
	}

	TermCriteria criteria = TermCriteria(TermCriteria::COUNT + TermCriteria::EPS, 10, 0.01);
	Size winSize(11, 11);

	vector<Point2f> prevPoints;
	vector<Point2f> currPoints;
	vector<Point2f> boundPoints;

	int delay = 1000 / fps;

	for (;;) {
		inputVideo >> frame;
		if (frame.empty())
			break;

		frame.copyTo(dstImage);
		imshow("dstImage", dstImage);

		cvtColor(dstImage, currImage, COLOR_BGR2GRAY);
		GaussianBlur(currImage, currImage, Size(5, 5), 0.5);
		
		if (g_bLeftDownAndMove) {
			rectangle(dstImage, g_pt1, g_pt2, Scalar(0, 0, 255), 2);
			outputVideo << dstImage;
			imshow("dstImage", dstImage);
		}

		if (g_bROI) {
			Mat mask(size, CV_8U);
			mask = 0;
			int w = g_pt2.x - g_pt1.x + 1;
			int h = g_pt2.y - g_pt1.x + 1;
			mask(Rect(g_pt1.x, g_pt1.y, w, h)) = 1;

			double qualityLevel = 0.001;
			double minDIstance = 10;
			int blockSize = 3;
			prevPoints.clear();
			goodFeaturesToTrack(prevImage, prevPoints, MAX_POINTS, qualityLevel, minDIstance, mask, blockSize, true, 0.04);

			cornerSubPix(prevImage, prevPoints, winSize, Size(-1, -1), criteria);

			DrawTrackingPoints(prevPoints, dstImage);

			RotatedRect minRect = minAreaRect(prevPoints);
			Point2f rectPoints[4];
			minRect.points(rectPoints);
			for (int i = 0; i < 4; i++)
				boundPoints.push_back(rectPoints[i]);

			outputVideo << dstImage;
			g_bROI = false;
		}

		if (prevPoints.size() > 0) {
			vector<Mat> prevPyr, currPyr;
			Mat status, err;
			buildOpticalFlowPyramid(prevImage, prevPyr, winSize, 3, true);
			buildOpticalFlowPyramid(currImage, currPyr, winSize, 3, true);
			calcOpticalFlowPyrLK(prevPyr, currPyr, prevPoints, currPoints, status, err, winSize);

			for (int i = 0; i < prevPoints.size(); i++) {
				if (!status.at<char>(i)) {
					prevPoints.erase(prevPoints.begin() + i);
					currPoints.erase(currPoints.begin() + i);
				}
			}

			if (currPoints.size() >= 4) {
				cornerSubPix(currImage, currPoints, winSize, Size(-1, -1), criteria);
				DrawTrackingPoints(currPoints, dstImage);

				Mat M = findHomography(prevPoints, currPoints, RANSAC);
				perspectiveTransform(boundPoints, boundPoints, M);
				for (int j = 0; j < 4; j++)
					line(dstImage, boundPoints[j], boundPoints[(j + 1) % 4], Scalar(0, 255, 255), 2);
			}
			outputVideo << dstImage;
			imshow("dstImage", dstImage);
			prevPoints = currPoints;
		}
		currImage.copyTo(prevImage);

		int ckey = waitKey(delay);
		if (ckey == 27) break;
	}*/

	//1209
	/*VideoCapture inputVideo("video2.avi");
	if (!inputVideo.isOpened())
		return 0;
	Size size = Size((int)inputVideo.get(CV_CAP_PROP_FRAME_WIDTH), (int)inputVideo.get(CV_CAP_PROP_FRAME_HEIGHT));
	size = Size(size.width / 2, size.height / 2);

	int fps = (int)inputVideo.get(CV_CAP_PROP_FPS);
	if (fps <= 0) fps = 24;

	Mat currImage, prevImage;
	Mat frame, dstImage;
	Mat flow;

	int fourcc = CV_FOURCC('D', 'I', 'V', 'X');
	bool isColor = true;
	VideoWriter outputVideo("trackingFlow.avi", fourcc, fps, size, isColor);
	if (!outputVideo.isOpened())
		return 0;
	if (fourcc != -1) {
		imshow("dstImage", NULL);
		waitKey(100);
	}
	int frameNum = -1;
	int delay = 1000 / fps;
	double pyr_scale = 0.5;
	int levels = 3;
	int winsize = 11;
	int iterations = 5;
	int poly_n = 5;
	double poly_sigma = 1.1;
	int flags = 0;

	for (;;) {
		inputVideo >> frame;
		if (frame.empty())
			break;
		frameNum++;

		pyrDown(frame, dstImage);
		cvtColor(dstImage, currImage, COLOR_BGR2GRAY);
		if (frameNum < 1) {
			currImage.copyTo(prevImage);
			continue;
		}
		if (frameNum > 1) {
			flags = OPTFLOW_USE_INITIAL_FLOW;
		}
		calcOpticalFlowFarneback(prevImage, currImage, flow, pyr_scale, levels, winsize, iterations, poly_n, poly_sigma, flags);
		DrawOpticalFlow(flow, dstImage);
		outputVideo << dstImage;
		imshow("dstImage", dstImage);
		currImage.copyTo(prevImage);
		int ckey = waitKey(delay);
		if (ckey == 27) break;
	}*/

	//1210, 1211
	/*VideoCapture inputVideo("ball.wmv");
	//VideoCapture inputVideo(0);
	if (!inputVideo.isOpened())
		return 0; 
	Size size = Size((int)inputVideo.get(CV_CAP_PROP_FRAME_WIDTH), (int)inputVideo.get(CV_CAP_PROP_FRAME_HEIGHT));
	size = Size(size.width / 2, size.height / 2);

	int fps = (int)inputVideo.get(CV_CAP_PROP_FPS);
	if (fps <= 0) fps = 24;

	Mat dstImage;
	namedWindow("dstImage");
	setMouseCallback("dstImage", OnMouse, (void*)&dstImage);

	int histSize = 8;
	float valueRange[] = { 0,180 };
	const float* ranges[] = { valueRange };
	int channels = 0;
	Mat hist, backProject;
	
	int fourcc = CV_FOURCC('D', 'I', 'V', 'X');
	bool isColor = true;
	VideoWriter outputVideo("trackingRect.avi", fourcc, fps, size, isColor);
	if (!outputVideo.isOpened())
		return 0;
	if (fourcc != -1) {
		imshow("dstImage", NULL);
		waitKey(100);
	}
	TermCriteria criteria = TermCriteria(TermCriteria::COUNT + TermCriteria::EPS, 10, 2);
	Rect trackWindow;
	RotatedRect trackBox;
	int delay = 1000 / fps;
	Mat frame, hImage, hsvImage, mask;

	for (;;) {
		inputVideo >> frame;
		if (frame.empty())
			break;
		cvtColor(frame, hsvImage, CV_BGR2HSV);
		frame.copyTo(dstImage);
		if (bLButtonDown && 0 < selection.width && 0 < selection.height) {
			Mat dstROI = dstImage(selection);
			bitwise_xor(dstROI, Scalar::all(255), dstROI);
		}
		if (trackingMode) {
			int vmin = 50, vmax = 256, smin = 50;
			inRange(hsvImage, Scalar(0, smin, MIN(vmin, vmax)), Scalar(180, 256, MAX(vmin, vmax)), mask);
			imshow("mask", mask);

			int ch[] = { 0,0 };
			hImage.create(hsvImage.size(), CV_8U);
			mixChannels(&hsvImage, 1, &hImage, 1, ch, 1);
			imshow("hImage", hImage);

			if (trackingMode == CALC_HIST) {
				Mat hImageROI(hImage, selection), maskROI(mask, selection);
				calcHist(&hImageROI, 1, &channels, maskROI, hist,1, &histSize, ranges);
				trackWindow = selection;
				trackingMode = TRACKING;
			}
			calcBackProject(&hImage, 1, &channels, hist, backProject, ranges);
			backProject &= mask;
			imshow("backProject", backProject);
			//meanShift(backProject, trackWindow, criteria);
			//Point pt1 = Point(trackWindow.x, trackWindow.y);
			//Point pt2 = Point(pt1.x + trackWindow.width, pt1.y + trackWindow.height);
			//rectangle(dstImage, pt1, pt2, Scalar(0, 0, 255), 2);

			trackBox = CamShift(backProject, trackWindow, criteria);
			ellipse(dstImage, trackBox, Scalar(255, 0, 0), 2);
			Point2f rectPoints[4];
			trackBox.points(rectPoints);
			for (int i = 0; i < 4; i++)
				line(dstImage, rectPoints[i], rectPoints[(i + 1) % 4], Scalar(0, 0, 255), 2);
		}
		imshow("dstImage", dstImage);
		outputVideo << dstImage;

		int ckey = waitKey(delay);
		if (ckey == 27) break;
	}*/

	//1212
	/*theRNG().state = time(NULL);
	int t, count = 100;
	double x = -0.37727;

	double Q = 1e-5;
	double R = 0.01;

	Scalar stddevR = Scalar::all(0.1);
	vector<float> measurement_k(count);
	randn(measurement_k, Scalar::all(x), stddevR);

	vector<float> state_k(count);
	vector<float> predict_k(count);
	vector<float> postP(count);
	vector<float> preP(count);
	vector<float> K(count);
	
	state_k[0] = 0.0;
	postP[0] = 1.0;
	for (t = 1; t < count; t++) {
		predict_k[t] = state_k[t - 1];
		preP[t] = postP[t - 1] + Q;

		K[t] = preP[t] / (preP[t] + R);
		state_k[t] = predict_k[t] + K[t] * (measurement_k[t] - predict_k[t]);
		postP[t] = (1 - K[t])*preP[t];
	}

	Mat dstImage(512, 512, CV_8UC3, Scalar::all(255));
	Size size = dstImage.size();
	namedWindow("dstImage");

	double minVal, maxVal;
	minMaxLoc(measurement_k, &minVal, &maxVal);
	double scale = size.height / (maxVal - minVal);
	cout << "measurement_k:";
	cout << " minVal=" << minVal;
	cout << ", maxVal=" << maxVal << endl;

	Point pt1, pt2;
	pt1.x = 0;
	pt1.y = size.height - cvRound(scale*x - scale * minVal);

	pt2.x = size.width;
	pt2.y= size.height - cvRound(scale*x - scale * minVal);
	line(dstImage, pt1, pt2, Scalar(255, 0, 0), 2);

	int step = size.width/count;
	for (t = 0; t < count; t++) {
		pt1.x = t * step;
		pt1.y= size.height - cvRound(scale*measurement_k[t]-scale*minVal);
		circle(dstImage, pt1, 3, Scalar(0, 255, 0), 2);
	}
	pt1.x = 0;
	pt1.y = size.height - cvRound(scale*state_k[0] - scale * minVal);
	for (t = 1; t < count; t++) {
		pt2.x = t * step;
		pt2.y = size.height - cvRound(scale*state_k[t] - scale * minVal);
		line(dstImage, pt1, pt2, Scalar(0, 0, 255), 2);
		pt1 = pt2;
	}
	imshow("dstImage", dstImage);

	Mat PImage(size.height, size.width, CV_8UC3, Scalar::all(255));
	size = PImage.size();
	namedWindow("PImage");

	minMaxLoc(postP, &minVal, &maxVal);
	scale = size.height / (maxVal - minVal);
	cout << "error covariance, P:";
	cout << " minVal= " << minVal;
	cout << ", maxVal= " << maxVal << endl;

	pt1.x = 0;
	pt1.y = size.height - cvRound(scale*postP[0] - scale*minVal);
	step = size.width / count;
	for (t = 1; t < count; t++) {
		pt2.x = t*step;
		pt2.y = size.height - cvRound(scale*postP[t] - scale * minVal);
		line(PImage, pt1, pt2, Scalar(0, 0, 255), 2);
		pt1 = pt2;
	}
	imshow("PImage", PImage);
	waitKey();*/

	//1214
	/*theRNG().state = time(NULL);
	int t, count = 100;
	double x = -0.37727;

	double Q = 1e-5;
	double R = 0.01;

	Scalar stddevR = Scalar::all(0.1);
	vector<float> measurement_k(count);
	randn(measurement_k, Scalar::all(x), stddevR);

	vector<float> state_k(count);
	vector<float> postP(count);

	KalmanFilter KF(1, 1, 0);
	Mat measurement(1, 1, CV_32F);

	setIdentity(KF.transitionMatrix);
	setIdentity(KF.measurementMatrix);
	setIdentity(KF.processNoiseCov, Scalar::all(Q));
	setIdentity(KF.measurementNoiseCov, Scalar::all(R));

	setIdentity(KF.statePost, Scalar::all(0));
	setIdentity(KF.errorCovPost, Scalar::all(1));
	state_k[0] = KF.statePost.at<float>(0);
	postP[0] = KF.errorCovPost.at<float>(0);

	for (t = 1; t < count; t++) {
		Mat prediction = KF.predict();
		measurement.at<float>(0) = measurement_k[t];
		Mat estimate = KF.correct(measurement);
		state_k[t] = KF.statePost.at <float>(0);
		postP[t] = KF.errorCovPost.at<float>(0);
	}

	Mat dstImage(512, 512, CV_8UC3, Scalar::all(255));
	Size size = dstImage.size();
	namedWindow("dstImage");

	double minVal, maxVal;
	minMaxLoc(measurement_k, &minVal, &maxVal);
	double scale = size.height / (maxVal - minVal);
	cout << "measurement_k:";
	cout << " minVal=" << minVal;
	cout << ", maxVal=" << maxVal << endl;

	Point pt1, pt2;
	pt1.x = 0;
	pt1.y = size.height - cvRound(scale*x - scale * minVal);

	pt2.x = size.width;
	pt2.y = size.height - cvRound(scale*x - scale * minVal);
	line(dstImage, pt1, pt2, Scalar(255, 0, 0), 2);

	int step = size.width / count;
	for (t = 0; t < count; t++) {
		pt1.x = t * step;
		pt1.y = size.height - cvRound(scale*measurement_k[t] - scale * minVal);
		circle(dstImage, pt1, 3, Scalar(0, 255, 0), 2);
	}
	pt1.x = 0;
	pt1.y = size.height - cvRound(scale*state_k[0] - scale * minVal);
	for (t = 1; t < count; t++) {
		pt2.x = t * step;
		pt2.y = size.height - cvRound(scale*state_k[t] - scale * minVal);
		line(dstImage, pt1, pt2, Scalar(0, 0, 255), 2);
		pt1 = pt2;
	}
	imshow("dstImage", dstImage);

	Mat PImage(size.height, size.width, CV_8UC3, Scalar::all(255));
	size = PImage.size();
	namedWindow("PImage");

	minMaxLoc(postP, &minVal, &maxVal);
	scale = size.height / (maxVal - minVal);
	cout << "error covariance, P:";
	cout << " minVal= " << minVal;
	cout << ", maxVal= " << maxVal << endl;

	pt1.x = 0;
	pt1.y = size.height - cvRound(scale*postP[0] - scale * minVal);
	step = size.width / count;
	for (t = 1; t < count; t++) {
		pt2.x = t * step;
		pt2.y = size.height - cvRound(scale*postP[t] - scale * minVal);
		line(PImage, pt1, pt2, Scalar(0, 0, 255), 2);
		pt1 = pt2;
	}
	imshow("PImage", PImage);
	waitKey();*/

	//1217
//	VideoCapture inputVideo("ball2.wmv");
	VideoCapture inputVideo(0);
	if (!inputVideo.isOpened())
		return 0;
	Size size = Size((int)inputVideo.get(CV_CAP_PROP_FRAME_WIDTH), (int)inputVideo.get(CV_CAP_PROP_FRAME_HEIGHT));
	size = Size(size.width / 2, size.height / 2);

	int fps = (int)inputVideo.get(CV_CAP_PROP_FPS);
	if (fps <= 0) fps = 24;

	Mat dstImage;
	namedWindow("dstImage");
	setMouseCallback("dstImage", OnMouse, (void*)&dstImage);

	int histSize = 8;
	float valueRange[] = { 0,180 };
	const float* ranges[] = { valueRange };
	int channels = 0;
	Mat hist, backProject;

	int fourcc = CV_FOURCC('D', 'I', 'V', 'X');
	bool isColor = true;
	VideoWriter outputVideo("trackingRect.avi", fourcc, fps, size, isColor);
	if (!outputVideo.isOpened())
		return 0;
	if (fourcc != -1) {
		imshow("dstImage", NULL);
		waitKey(100);
	}
	TermCriteria criteria = TermCriteria(TermCriteria::COUNT + TermCriteria::EPS, 10, 2);
	Rect trackWindow;
	int delay = 1000 / fps;
	Mat frame, hImage, hsvImage, mask;

	Point2f ptPredicted;
	Point2f ptEstimated;
	Point2f ptMeasured;

	KalmanFilter KF(4, 2, 0);
	Mat measurement(2, 1, CV_32F);

	float dt = 1.0;
	const float A[] = { 1,0,dt,0,
						0,1,0,dt,
						0,0,1,0,
						0,0,0,1 };
	memcpy(KF.transitionMatrix.data, A, sizeof(A));
	cout << "KF.transitionMatrix = " << KF.transitionMatrix << endl;

	double Q = 1e-5;
	double R = 0.0001;
	const float H[] = { 1,0,0,0,
						0,1,0,0 };
	memcpy(KF.measurementMatrix.data, H, sizeof(H));
	cout << "KF.measurementMatrix = " << KF.measurementMatrix << endl;

	setIdentity(KF.processNoiseCov, Scalar::all(Q));
	KF.processNoiseCov.at<float>(2, 2) = 0;
	KF.processNoiseCov.at<float>(3, 3) = 0;
	cout << "KF.processNoiseCov = " << KF.processNoiseCov << endl;

	setIdentity(KF.measurementNoiseCov, Scalar::all(R));
	cout << "KF.measurementNoiseCov = " << KF.measurementNoiseCov << endl;

	Mat hist1, hist2;
	for (;;) {
		inputVideo >> frame;
		if (frame.empty())
			break;
		cvtColor(frame, hsvImage, CV_BGR2HSV);
		frame.copyTo(dstImage);
		if (bLButtonDown && 0 < selection.width && 0 < selection.height) {
			Mat dstROI = dstImage(selection);
			bitwise_xor(dstROI, Scalar::all(255), dstROI);
		}
		if (trackingMode) {
			int vmin = 50, vmax = 256, smin = 50;
			inRange(hsvImage, Scalar(0, smin, MIN(vmin, vmax)), Scalar(180, 256, MAX(vmin, vmax)), mask);
			imshow("mask", mask);

			int ch[] = { 0,0 };
			hImage.create(hsvImage.size(), CV_8U);
			mixChannels(&hsvImage, 1, &hImage, 1, ch, 1);
			imshow("hImage", hImage);

			if (trackingMode == CALC_HIST) {
				Mat hImageROI(hImage, selection), maskROI(mask, selection);
				calcHist(&hImageROI, 1, &channels, maskROI, hist, 1, &histSize, ranges);
				hist.copyTo(hist1);
				normalize(hist1, hist1, 1.0);
				normalize(hist, hist, 0, 255, NORM_MINMAX);
				trackWindow = selection;
				trackingMode = TRACKING;

				ptMeasured = Point2f(trackWindow.x + trackWindow.width / 2.0, trackWindow.y + trackWindow.height / 2.0);
				KF.statePost.at<float>(0, 0) = ptMeasured.x;
				KF.statePost.at<float>(1, 0) = ptMeasured.y;
				KF.statePost.at<float>(2, 0) = 0;
				KF.statePost.at<float>(3, 0) = 0;

				setIdentity(KF.errorCovPost, Scalar::all(1));
			}
			Mat prediction = KF.predict();
			ptPredicted.x = prediction.at<float>(0, 0);
			ptPredicted.y = prediction.at<float>(1, 0);

			calcBackProject(&hImage, 1, &channels, hist, backProject, ranges);
			backProject &= mask;
			imshow("backProject", backProject);

			meanShift(backProject, trackWindow, criteria);
			Point pt1 = Point(trackWindow.x, trackWindow.y);
			Point pt2 = Point(pt1.x + trackWindow.width, pt1.y + trackWindow.height);
			rectangle(dstImage, pt1, pt2, Scalar(0, 0, 255), 2);

			Mat hImageROI(hImage, trackWindow), maskROI(mask, trackWindow);
			calcHist(&hImageROI, 1, &channels, maskROI, hist2, 1, &histSize, ranges);
			normalize(hist2, hist2, 1.0);
			double dist = compareHist(hist1, hist2, CV_COMP_BHATTACHARYYA);
			if (dist < DIST_TH) {
				ptMeasured = Point2f(trackWindow.x + trackWindow.width / 2.0, trackWindow.y + trackWindow.height / 2.0);

				measurement.at<float>(0, 0) = ptMeasured.x;
				measurement.at<float>(1, 0) = ptMeasured.y;

				Mat estimated = KF.correct(measurement);

				ptEstimated.x = estimated.at<float>(0, 0);
				ptEstimated.y = estimated.at<float>(1, 0);

				trackWindow = Rect(ptEstimated.x - selection.width / 2.0, ptEstimated.y - selection.height / 2.0, selection.width, selection.height);
				
				pt1 = Point(ptMeasured.x - trackWindow.width / 2.0, ptMeasured.y - trackWindow.height / 2.0);
				pt2 = Point(ptMeasured.x + trackWindow.width / 2.0, ptMeasured.y + trackWindow.height / 2.0);
				rectangle(dstImage, pt1, pt2, Scalar(0, 0, 255), 2);
				circle(dstImage, ptMeasured, 5, Scalar(0, 0, 255), 2);

				pt1 = Point(ptEstimated.x - trackWindow.width / 2.0, ptEstimated.y - trackWindow.height / 2.0);
				pt2 = Point(ptEstimated.x + trackWindow.width / 2.0, ptEstimated.y + trackWindow.height / 2.0);
				rectangle(dstImage, pt1, pt2, Scalar(255, 0, 0), 2);
				circle(dstImage, ptEstimated, 5, Scalar(255, 0, 0), 2);
			}
			else {
				trackWindow=Rect(ptPredicted.x - selection.width / 2.0, ptPredicted.y - selection.height / 2.0, selection.width, selection.height);
				pt1 = Point(ptPredicted.x - trackWindow.width / 2.0, ptPredicted.y - trackWindow.height / 2.0);
				pt2 = Point(ptPredicted.x + trackWindow.width / 2.0, ptPredicted.y + trackWindow.height / 2.0);
				rectangle(dstImage, pt1, pt2, Scalar(0, 255, 0), 2);
				circle(dstImage, ptPredicted, 5, Scalar(0, 255, 0), 2);

			}
		}
		imshow("dstImage", dstImage);
		outputVideo << dstImage;

		int ckey = waitKey(delay);
		if (ckey == 27) break;
	}

	return 0;
}