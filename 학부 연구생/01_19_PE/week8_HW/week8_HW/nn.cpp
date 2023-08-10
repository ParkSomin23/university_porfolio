#include "pch.h"
#include <opencv.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int main() {
	//VideoCapture capture(0);
	VideoCapture capture("ddd.mp4");
	Mat srcImage = imread("circleTracking.jpg", IMREAD_GRAYSCALE);
	if (!capture.isOpened()||srcImage.empty())
		return 0;
	Size size = Size((int)capture.get(CV_CAP_PROP_FRAME_WIDTH), (int)capture.get(CV_CAP_PROP_FRAME_HEIGHT));
	cout << "size=" << size << endl;

	//points
	//detect keypoints
	vector<KeyPoint> keyPoints1, keypoints2;

	SurfFeatureDetector detector(500);
	detector.detect(srcImage, keyPoints1);

	//descriptors
	Mat descriptors1, descriptors2;
	SurfDescriptorExtractor extractor;
	extractor.compute(srcImage, keyPoints1, descriptors1);

	//matching
	vector<DMatch> matches;
	FlannBasedMatcher matcher;


	imshow("frame", NULL);
	waitKey(100);

	int delay = 30;
	int frameNum = -1;
	Mat frame, grayImage, edgeImage;
	namedWindow("dstROI");
	
	Mat matchImage;
	namedWindow("matchImage");

	Mat mask;
	Mat dstROI;

	Rect bRect;

	//////////////////////////
	for (;;) {
		capture >> frame;
		cvtColor(frame, grayImage, COLOR_BGR2GRAY);
		
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
		
		bRect = boundingRect(sceneP);
		//bRect = minAreaRect(sceneP);
		//cout << sceneP[0] << "     " << sceneP[1] << "     " << sceneP[2] << "     " << sceneP[3] << endl;
		//static Rect selection = Rect(cvRound(sceneP[0].x), cvRound(sceneP[0].y), cvRound(abs(sceneP[0].x - sceneP[2].x)), cvRound(abs(sceneP[0].y - sceneP[2].y)));
		
		if (10 < bRect.width && 10<bRect.height) {

			if (bRect.width + bRect.x >= frame.cols)
				bRect.width = frame.cols-bRect.x-10;
			if (bRect.height + bRect.y >= frame.rows)
				bRect.height = frame.rows-bRect.y-10;

			dstROI = frame(bRect);
			rectangle(matchImage, bRect, Scalar(0, 255, 0), 8);
			//bitwise_xor(dstROI, Scalar::all(255), matchImage);
		}
		//imshow("frame", frame);
		imshow("matchImage", matchImage);

		goodMatches.clear();
		int cKey = waitKey(delay);
		if (cKey == 27) break;

		cout << bRect.width*bRect.height << endl;
		if (bRect.width*bRect.height > 80000) {
			break;
		}
	}

	return 0;
}