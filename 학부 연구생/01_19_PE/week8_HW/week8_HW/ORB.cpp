#include "pch.h"
#include <opencv.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <iostream>
using namespace std;
using namespace cv;

bool isFound = false;

int main() {
	VideoCapture inputVideo(0);
	Mat srcImage = imread("circleTracking.jpg", IMREAD_GRAYSCALE);

	if (srcImage.empty() || !inputVideo.isOpened())
		return -1;

	//detect keypoints
	vector<KeyPoint> keyPoints1, keypoints2;
	Mat descriptors1, descriptors2;

	ORB(1000)(srcImage, noArray(), keyPoints1, descriptors1);
	
	int k = 2;
	Mat indices;
	Mat dists;

	Size size = Size((int)inputVideo.get(CV_CAP_PROP_FRAME_WIDTH), (int)inputVideo.get(CV_CAP_PROP_FRAME_HEIGHT));
	int fourcc = CV_FOURCC('D', 'I', 'V', 'X');
	double fps = 24;
	VideoWriter outputVideo("outputVideo.avi", fourcc, fps, size, true);

	if (!outputVideo.isOpened())
		return -1;

	if (fourcc != -1)
	{
		imshow("matchImage", NULL);
		waitKey(100);
	}

	int delay = 1000 / fps;
	Mat frame;

	while (!isFound) {
		inputVideo >> frame;
		if (frame.empty())
			break;
		cvtColor(frame, frame, COLOR_BGR2GRAY);

		ORB(1000)(frame, noArray(), keypoints2, descriptors2);
		flann::Index flannIndex(descriptors2, flann::LshIndexParams(12, 20, 2), cvflann::FLANN_DIST_HAMMING);
		flannIndex.knnSearch(descriptors1, indices, dists, k, flann::SearchParams());

		vector<DMatch> goodMatches;
		float nndrRatio = 0.6f;

		for (int i = 0; i < descriptors1.rows; i++) {
			float d1, d2;
			d1 = (float)dists.at<int>(i, 0);
			d2 = (float)dists.at<int>(i, 1);

			if (indices.at<int>(i, 0) >= 0 && indices.at<int>(i, 1) >= 0 && d1 < -nndrRatio * d2) {
				DMatch match(i, indices.at<int>(i, 0), d1);
				goodMatches.push_back(match);
			}
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
		for (int i = 0; i < 4; i++)
			line(matchImage, sceneP[i], sceneP[(i + 1) % 4], Scalar(255, 0, 0), 4);

		outputVideo << matchImage;
		imshow("matchImage", matchImage);

		goodMatches.clear();

		int ckey = waitKey(delay);
		if (ckey == 27) break;
	}
	return 0;
}