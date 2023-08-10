#include "pch.h"
#include "opencv.hpp"
#include "opencv2/nonfree/nonfree.hpp"
using namespace std;
using namespace cv;

Rect selection;
bool bLButtonDown = false;
typedef enum { INIT, CALC_HIST, TRACKING } STATUS;
STATUS trackingMode = INIT;

/*void OnMouse(int mevent, int x, int y, int flags, void *param) {
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
}*/

//1217
#define DIST_TH 0.4


int msssain(){
	VideoCapture inputVideo("ddd.mp4");
	Mat dstImage = imread("trackingCircle.jpg", IMREAD_GRAYSCALE);
	if (!inputVideo.isOpened())
		return 0;
	Size size = Size((int)inputVideo.get(CV_CAP_PROP_FRAME_WIDTH), (int)inputVideo.get(CV_CAP_PROP_FRAME_HEIGHT));
	size = Size(size.width / 2, size.height / 2);

	int fps = (int)inputVideo.get(CV_CAP_PROP_FPS);
	if (fps <= 0) fps = 24;



	Mat srcImage;
	srcImage.copyTo(dstImage);
	////////////////////////////////
	//points
	//detect keypoints
	vector<KeyPoint> keyPoints1, keypoints2;

	SurfFeatureDetector detector(300);
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
		inputVideo >> frame;
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

		if (10 < bRect.width && 10 < bRect.height) {

			if (bRect.width + bRect.x >= frame.cols)
				bRect.width = frame.cols - bRect.x - 10;
			if (bRect.height + bRect.y >= frame.rows)
				bRect.height = frame.rows - bRect.y - 10;

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





	selection = bRect;
	mask(bRect) = 1;
	//selection = Rect(0, 0, dstImage.cols, dstImage.rows);
	if (selection.width > 0 && selection.height > 0)
		trackingMode = CALC_HIST;

	/*Mat dstImage;
	namedWindow("dstImage");
	setMouseCallback("dstImage", OnMouse, (void*)&dstImage);*/

	//namedWindow("dstImage");

	int histSize = 8;
	float valueRange[] = { 0,180 };
	const float* ranges[] = { valueRange };
	int channels = 0;
	Mat hist, backProject;

	TermCriteria criteria = TermCriteria(TermCriteria::COUNT + TermCriteria::EPS, 10, 2);
	Rect trackWindow;
	//int delay = 1000 / fps;
	Mat hImage, hsvImage;

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
		/*if (0 < selection.width && 0 < selection.height) {
			Mat dstROI = dstImage(selection);
			bitwise_xor(dstROI, Scalar::all(255), dstROI);
		}*/
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
				trackWindow = Rect(ptPredicted.x - selection.width / 2.0, ptPredicted.y - selection.height / 2.0, selection.width, selection.height);
				pt1 = Point(ptPredicted.x - trackWindow.width / 2.0, ptPredicted.y - trackWindow.height / 2.0);
				pt2 = Point(ptPredicted.x + trackWindow.width / 2.0, ptPredicted.y + trackWindow.height / 2.0);
				rectangle(dstImage, pt1, pt2, Scalar(0, 255, 0), 2);
				circle(dstImage, ptPredicted, 5, Scalar(0, 255, 0), 2);

			}
		}
		imshow("dstImage", dstImage);
		//outputVideo << dstImage;

		int ckey = waitKey(delay);
		if (ckey == 27) break;
	}

	return 0;
}