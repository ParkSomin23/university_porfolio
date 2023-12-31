#include "pch.h"
#include <opencv.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <iostream>
using namespace std;
using namespace cv;

bool isFound = false;
bool isTracking = false;

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

	Mat currImage, prevImage;

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

	TermCriteria criteria = TermCriteria(TermCriteria::COUNT + TermCriteria::EPS, 10, 0.01);
	Size winSize(11, 11);

	vector<Point2f> prevPoints;
	vector<Point2f> currPoints;
	vector<Point2f> boundPoints;

	Mat frame, dstImage;
	int k = 2;

	Mat mask(size, CV_8U);

	for (;;) {
		inputVideo >> dstImage;
		if (dstImage.empty())
			break;

		if (!isFound) {
			int count = 0;

			dstImage.copyTo(frame);
			cvtColor(dstImage, frame, COLOR_BGR2GRAY);
			GaussianBlur(frame, frame, Size(5, 5), 0.5);

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
				count++;
				line(matchImage, sceneP[i], sceneP[(i + 1) % 4], Scalar(255, 0, 0), 4);
			}

			outputVideo << matchImage;
			imshow("matchImage", matchImage);

			goodMatches.clear();

			if (count >= 4) {
				int w = abs(sceneP[1].x - sceneP[0].x);
				int h = abs(sceneP[3].y - sceneP[0].y);
				mask(Rect(sceneP[0].x, sceneP[0].y, w, h)) = 1;
				isFound = true;
				isTracking = true;
				count = -1;
			}
		}

		if (isTracking) {
			double qualityLevel = 0.001;
			double minDIstance = 10;
			int blockSize = 3;
			prevPoints.clear();

			cornerSubPix(prevImage, prevPoints, winSize, Size(-1, -1), criteria);

			DrawTrackingPoints(prevPoints, dstImage);

			RotatedRect minRect = minAreaRect(prevPoints);
			Point2f rectPoints[4];
			minRect.points(rectPoints);
			for (int i = 0; i < 4; i++)
				boundPoints.push_back(rectPoints[i]);

			outputVideo << dstImage;
			isTracking = false;
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
	}
	return 0;
}
