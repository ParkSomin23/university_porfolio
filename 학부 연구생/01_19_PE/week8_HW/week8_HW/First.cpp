#include "pch.h"
#include <opencv.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int main() {
	VideoCapture inputVideo(0);
	Mat srcImage = imread("circleTracking.jpg", IMREAD_GRAYSCALE);

	if (srcImage.empty() || !inputVideo.isOpened())
		return -1;

	//detect keypoints
	vector<KeyPoint> keyPoints1, keypoints2;

	//SiftFeatureDetector detector(100);
	SurfFeatureDetector detector(100);
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

	int fourcc = CV_FOURCC('D', 'I', 'V', 'X');
	double fps = 24;
	VideoWriter outputVideo("outputVideo.avi", fourcc, fps, size, true);

	if (!outputVideo.isOpened())
		return -1;

	if (fourcc != -1)
	{
		imshow("frame", NULL);
		waitKey(100);
	}

	int delay = 1000 / fps;
	Mat mask;
	Mat dstImage, frame;

	namedWindow("matchImage");
	for (;;) {
		inputVideo >> frame;
		if (frame.empty())
			break;

		//	dstImage.copyTo(frame);
		cvtColor(frame, frame, COLOR_BGR2GRAY);
		//			GaussianBlur(frame, frame, Size(5, 5), 0.5);

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

		Mat matchImage;
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
			//count++;
			line(matchImage, sceneP[i], sceneP[(i + 1) % 4], Scalar(255, 0, 0), 4);
		}

		outputVideo << matchImage;
		imshow("matchImage", matchImage);

		goodMatches.clear();
	}
	waitKey();
	return 0;
}
