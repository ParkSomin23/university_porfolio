#include "pch.h"
#include "opencv.hpp"
#include "opencv2/nonfree/nonfree.hpp"
using namespace std;
using namespace cv;

#define MAX_POINTS 16
Point g_pt1, g_pt2;
bool g_bLeftDownAndMove = false;
bool g_bROI = false;


bool isFound = false;
bool isTracking = false;
Mat matchImage;


//void onMouse
void OnMouse(int mevent, int x, int y, int flags, void *param) {
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
}

int main() {
	VideoCapture inputVideo(0);
	Mat srcImage = imread("circleTracking.jpg", IMREAD_GRAYSCALE);

	if (srcImage.empty() || !inputVideo.isOpened())
		return -1;

	//detect keypoints
	vector<KeyPoint> keyPoints1, keypoints2;

	//SiftFeatureDetector detector(100);
	SurfFeatureDetector detector(400);
	detector.detect(srcImage, keyPoints1);

	//descriptors
	Mat descriptors1, descriptors2;
	SurfDescriptorExtractor extractor;
	//SiftDescriptorExtractor extractor;
	extractor.compute(srcImage, keyPoints1, descriptors1);

	//matching
	//vector<vector<DMatch>> matches;
	vector<DMatch> matches;
	FlannBasedMatcher matcher;

	Size size = Size((int)inputVideo.get(CV_CAP_PROP_FRAME_WIDTH), (int)inputVideo.get(CV_CAP_PROP_FRAME_HEIGHT));
	cout << "size=" << size << endl;

	int fps = 24;
	Mat currImage, prevImage;
	Mat frame, dstImage;
	Mat mask;
	namedWindow("matchImage");
	//setMouseCallback("dstImage", OnMouse, NULL);

	int fourcc = CV_FOURCC('D', 'I', 'V', 'X');
	bool isColor = true;
	VideoWriter outputVideo("trackingRect.avi", fourcc, fps, size, isColor);

	if (!outputVideo.isOpened()) {
		return 0;
	}

	if (!fourcc != -1) {
		imshow("matchImage", NULL);
		waitKey(100);
	}

	TermCriteria criteria = TermCriteria(TermCriteria::COUNT + TermCriteria::EPS, 10, 0.01);
	Size winSize(11, 11);

	vector<Point2f> prevPoints;
	vector<Point2f> currPoints;
	vector<Point2f> boundPoints;

	int delay = 1000 / fps;
	int count = 0;
	for (;;) {
		inputVideo >> frame;
		if (frame.empty())
			break;

		frame.copyTo(dstImage);
		imshow("matchImage", dstImage);

		cvtColor(dstImage, currImage, COLOR_BGR2GRAY);
		GaussianBlur(currImage, currImage, Size(5, 5), 0.5);

		if (!isFound) {

			detector.detect(frame, keypoints2);
			extractor.compute(frame, keypoints2, descriptors2);
			matcher.match(descriptors1, descriptors2, matches);

			if (matches.size() < 4)
				continue;

			double minDist, maxDist;
			minDist = maxDist = matches[0].distance;

			for (int i = 1; i < matches.size(); i++) {
				double dist = matches[i].distance;
				if (dist < minDist) minDist = dist;
				if (dist > maxDist) maxDist = dist;
			}

			vector<DMatch> goodMatches;
			float nndrRatio = 0.4f;
			double fTh = 4 * minDist;
			for (int i = 0; i < matches.size(); i++) {
				if (matches[i].distance <= max(fTh, 0.02))
					goodMatches.push_back(matches[i]);
			}
			if (goodMatches.size() < 4)
				continue;

			drawMatches(srcImage, keyPoints1, frame, keypoints2, goodMatches, matchImage, Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

			vector<Point2f> obj;
			vector<Point2f> scene;
			for (int i = 0; i < goodMatches.size(); i++) {
				obj.push_back(keyPoints1[goodMatches[i].queryIdx].pt);
				scene.push_back(keypoints2[goodMatches[i].trainIdx].pt);
			}
			Mat H = findHomography(obj, scene, CV_RANSAC);

			vector<Point2f>objP(4);
			objP[0] = cvPoint(0, 0);
			objP[1] = cvPoint(srcImage.cols, 0);
			objP[2] = cvPoint(srcImage.cols, srcImage.rows);
			objP[3] = cvPoint(0, srcImage.rows);

			vector<Point2f> sceneP(4);
			perspectiveTransform(objP, sceneP, H);

			for (int i = 0; i < 4; i++)
				sceneP[i] += Point2f(srcImage.cols, 0);
			for (int i = 0; i < 4; i++) {
				line(matchImage, sceneP[i], sceneP[(i + 1) % 4], Scalar(255, 0, 0), 4);
			}

			outputVideo << matchImage;
			imshow("matchImage", matchImage);

			int w = cvRound(abs(sceneP[1].x - sceneP[0].x));
			int h = cvRound(abs(sceneP[3].y - sceneP[0].y));
			mask(Rect(cvRound(sceneP[0].x), cvRound(sceneP[0].y), w, h)) = 1;

			if (cv::countNonZero(mask) > 100) {
				isFound = true;
				g_bROI = true;
			}

			goodMatches.clear();

		}

		if (g_bROI) {
			double qualityLevel = 0.001;
			double minDIstance = 10;
			int blockSize = 3;
			prevPoints.clear();
			goodFeaturesToTrack(prevImage, prevPoints, MAX_POINTS, qualityLevel, minDIstance, mask, blockSize, true, 0.04);

			cornerSubPix(prevImage, prevPoints, winSize, Size(-1, -1), criteria);

			DrawTrackingPoints(prevPoints, matchImage);

			RotatedRect minRect = minAreaRect(prevPoints);
			Point2f rectPoints[4];
			minRect.points(rectPoints);
			for (int i = 0; i < 4; i++)
				boundPoints.push_back(rectPoints[i]);

			outputVideo << matchImage;
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
				DrawTrackingPoints(currPoints, matchImage);

				Mat M = findHomography(prevPoints, currPoints, RANSAC);
				perspectiveTransform(boundPoints, boundPoints, M);
				for (int j = 0; j < 4; j++)
					line(matchImage, boundPoints[j], boundPoints[(j + 1) % 4], Scalar(0, 255, 255), 2);
			}
			outputVideo << matchImage;
			imshow("matchImage", matchImage);
			prevPoints = currPoints;
		}
		currImage.copyTo(prevImage);

		int ckey = waitKey(delay);
		if (ckey == 27) break;
	}
	return 0;
}