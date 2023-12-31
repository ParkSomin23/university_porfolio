#include "pch.h"
#include "opencv.hpp"
#include "opencv2/nonfree/nonfree.hpp"
using namespace std;
using namespace cv;

int main() {

	//1001
	Mat srcImage = imread("cornerTest.jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;
	//GaussianBlur(srcImage, srcImage, Size(5, 5), 0.0);

	vector<KeyPoint> keypoints;

	int type = FastFeatureDetector::TYPE_9_16;
	FASTX(srcImage, keypoints, 10, true, type);

	FastFeatureDetector fastF(10, true);
	fastF.detect(srcImage, keypoints);
	cout << "keypoints.size()=" << keypoints.size() << endl;

//	KeyPointsFilter::removeDuplicated(keypoints);
//	cout << "removeDuplicated keypoints.size()=" << keypoints.size() << endl;

//	KeyPointsFilter::runByKeypointSize(keypoints,10);
//	cout << "runByKeypointSize keypoints.size()=" << keypoints.size() << endl;

	KeyPointsFilter::retainBest(keypoints,10);
	cout << "retainBest keypoints.size()=" << keypoints.size() << endl;

	Mat dstImage(srcImage.size(), CV_8UC3);
	cvtColor(srcImage, dstImage, COLOR_GRAY2BGR);

	KeyPoint element;
	for (int k = 0; k < keypoints.size(); k++) {
		element = keypoints[k];
		cout << element.pt << "," << element.response;
		cout << "/" << element.angle;
		cout << "!" << element.size;
		cout << "@" << element.class_id << endl;
		circle(dstImage, element.pt, cvRound(element.size / 2), Scalar(0, 0, 255), 2);
	}
	drawKeypoints(srcImage, keypoints, dstImage);
	imshow("dstImage", dstImage);
	waitKey();

	//1002
	/*//Mat srcImage = imread("shapes.jpg", IMREAD_GRAYSCALE);
	Mat srcImage = imread("pattern.jpg", IMREAD_GRAYSCALE);
	//Mat srcImage = imread("lena.jpg", IMREAD_GRAYSCALE);
	//Mat srcImage = imread("book.jpg", IMREAD_GRAYSCALE);

	if (srcImage.empty())
		return -1;
	GaussianBlur(srcImage, srcImage, Size(5, 5), 0.0);

	vector<vector<Point>> msers;

	MSER(10)(srcImage, msers);
	cout << "msers.size()=" << msers.size() << endl;

	Mat dstImage(srcImage.size(), CV_8UC3);
	cvtColor(srcImage, dstImage, COLOR_GRAY2BGR);

	for (int k = 0; k < msers.size(); k++) {
		RotatedRect box = fitEllipse(msers[k]);
		ellipse(dstImage, box, Scalar(rand() % 256, rand() % 256, rand() % 256), 2);
	}
	imshow("dstImage", dstImage);
	waitKey();*/

	//1003
	/*Mat srcImage = imread("blobTest.jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;
	GaussianBlur(srcImage, srcImage, Size(5, 5), 0.0);

	vector<KeyPoint> keypoints;

	SimpleBlobDetector::Params params = SimpleBlobDetector::Params();
	params.blobColor = 0;
	params.thresholdStep = 5;
	params.minThreshold = 50;
	params.maxThreshold = 200;
	params.minDistBetweenBlobs = 5;

	params.filterByColor = false;
	params.filterByArea = true;
	params.filterByInertia = true;
	params.filterByCircularity = true;
	params.filterByConvexity = true;

	SimpleBlobDetector blobF(params);
	blobF.detect(srcImage, keypoints);
	cout << "keypoints.size()=" << keypoints.size() << endl;

	Mat dstImage(srcImage.size(), CV_8UC3);
	cvtColor(srcImage, dstImage, COLOR_GRAY2BGR);
	drawKeypoints(srcImage, keypoints, dstImage);

	KeyPointsFilter::removeDuplicated(keypoints);
	cout << "removeDuplicated keypoints.size()=" << keypoints.size() << endl;

	KeyPointsFilter::runByKeypointSize(keypoints, 10);
	cout << "runByKeypointSize keypoints.size()=" << keypoints.size() << endl;

	KeyPointsFilter::retainBest(keypoints, 10);
	cout << "retainBest keypoints.size()=" << keypoints.size() << endl;

	KeyPoint element;
	for (int k = 0; k < keypoints.size(); k++) {
		element = keypoints[k];
		circle(dstImage, element.pt, cvRound(element.size), Scalar(0, 0, 255), 2);
	}
	imshow("dstImage", dstImage);
	waitKey();*/

	//1004
	/*//Mat srcImage = imread("shapes.jpg", IMREAD_GRAYSCALE);
	//Mat srcImage = imread("pattern.jpg", IMREAD_GRAYSCALE);
	//Mat srcImage = imread("lena.jpg", IMREAD_GRAYSCALE);
	Mat srcImage = imread("book.jpg", IMREAD_GRAYSCALE);

	if (srcImage.empty())
		return -1;
	//GaussianBlur(srcImage, srcImage, Size(5, 5), 0.0);

	vector<KeyPoint> keypoints;

	GFTTDetector goodF(200, 0.01, 1, 5, true);
	goodF.detect(srcImage, keypoints);
	cout << "keypoints.size()=" << keypoints.size() << endl;

	Mat dstImage(srcImage.size(), CV_8UC3);
	cvtColor(srcImage, dstImage, COLOR_GRAY2BGR);
	drawKeypoints(srcImage, keypoints, dstImage);

	KeyPoint element;
	for (int k = 0; k < keypoints.size(); k++) {
		element = keypoints[k];
		circle(dstImage, element.pt, cvRound(element.size / 2), Scalar(0, 0, 255), 2);
	}
	imshow("dstImage", dstImage);
	waitKey();*/

	//1005
	/*//Mat srcImage = imread("shapes.jpg", IMREAD_GRAYSCALE);
	//Mat srcImage = imread("pattern.jpg", IMREAD_GRAYSCALE);
	//Mat srcImage = imread("lena.jpg", IMREAD_GRAYSCALE);
	Mat srcImage = imread("book.jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;
	GaussianBlur(srcImage, srcImage, Size(5, 5), 0.0);

	vector<KeyPoint> keypoints;
	//StarDetector(srcImage, keypoints);
	StarDetector starF;
	starF.detect(srcImage, keypoints);

	cout << "keypoints.size()=" << keypoints.size() << endl;

	Mat dstImage(srcImage.size(), CV_8UC3);
	cvtColor(srcImage, dstImage, COLOR_GRAY2BGR);
	drawKeypoints(srcImage, keypoints, dstImage);

	KeyPointsFilter::removeDuplicated(keypoints);
	cout << "keypoints.size()=" << keypoints.size() << endl;

	KeyPointsFilter::runByKeypointSize(keypoints, 30);
	cout << "keypoints.size()=" << keypoints.size() << endl;

	KeyPointsFilter::retainBest(keypoints, 100);
	cout << "keypoints.size()=" << keypoints.size() << endl;

	KeyPoint element;
	for (int k = 0; k < keypoints.size(); k++) {
		element = keypoints[k];
		cout << element.pt << "," << element.response << "," << element.angle << "," << element.size;
		cout << "," << element.class_id << endl;
		circle(dstImage, element.pt, cvRound(element.size/2), Scalar(0, 0, 255), 2);
	}
	imshow("dstImage", dstImage);
	waitKey();*/

	//1006
	/*//Mat srcImage = imread("pattern.jpg", IMREAD_GRAYSCALE);
	Mat srcImage = imread("shapes.jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;
	vector<KeyPoint> keypoints;
	DenseFeatureDetector denseF(20, 2, 0.2, 50);
	denseF.detect(srcImage, keypoints);
	cout << "keypoints.size()=" << keypoints.size() << endl;

	Mat dstImage(srcImage.size(), CV_8UC3);
	cvtColor(srcImage, dstImage, COLOR_GRAY2BGR);
	drawKeypoints(srcImage, keypoints, dstImage);

	KeyPoint element;
	for (int k = 0; k < keypoints.size(); k++) {
		element = keypoints[k];
		Scalar color;
		if (element.size == 20)
			color = Scalar(0, 0, 255);
		else
			color = Scalar(255, 0, 0);
		circle(dstImage, element.pt, cvRound(element.size / 2), color, 2);
	}
	imshow("dstImage", dstImage);
	waitKey();*/

	//1007	
	/*Mat srcImage = imread("cornerTest.jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;
	GaussianBlur(srcImage, srcImage, Size(5, 5), 0.0);

	vector<KeyPoint>keypoints;
	FastFeatureDetector fastF(10, true);
	fastF.detect(srcImage, keypoints);
	cout << "keypoints.size()=" << keypoints.size() << endl;

	KeyPointsFilter::removeDuplicated(keypoints);
	KeyPointsFilter::retainBest(keypoints, 10);
	cout << "keypoints.size()=" << keypoints.size() << endl;

	BriefDescriptorExtractor brief(16);
	Mat descripter;
	brief.compute(srcImage, keypoints, descripter);

	FileStorage fs("Keypoints.yml", FileStorage::WRITE);
	write(fs, "keypoints", keypoints);
	write(fs, "descripter", descripter);
	fs.release();

	Mat dstImage(srcImage.size(), CV_8UC3);
	cvtColor(srcImage, dstImage, COLOR_GRAY2BGR);
	drawKeypoints(srcImage, keypoints, dstImage);

	KeyPoint element;
	for (int k = 0; k < keypoints.size(); k++) {
		element = keypoints[k];
		circle(dstImage, element.pt, cvRound(element.size / 2), Scalar(0,0,255), 2);
	}
	imshow("dstImage", dstImage);
	waitKey();*/

	//1008
	/*Mat srcImage = imread("cornerTest.jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;
	GaussianBlur(srcImage, srcImage, Size(5, 5), 0.0);

	vector<KeyPoint> keypoints;
	FastFeatureDetector fastF(10, true);
	fastF.detect(srcImage, keypoints);

	KeyPointsFilter::removeDuplicated(keypoints);
	KeyPointsFilter::retainBest(keypoints, 10);
	cout << "keypoints.size()=" << keypoints.size() << endl;

	Mat dstimage(srcImage.size(), CV_8UC3);
	cvtColor(srcImage, dstimage, COLOR_GRAY2BGR);
	drawKeypoints(srcImage, keypoints, dstimage);
	imshow("dstImage", dstimage);

	FileStorage fs1("Keypoints1.yml", FileStorage::WRITE);
	write(fs1, "keypoints", keypoints);
	fs1.release();

	FREAK freak;
	Mat descriptors;
	freak.compute(srcImage, keypoints, descriptors);

	FileStorage fs("Keypoints2.yml", FileStorage::WRITE);
	write(fs, "keypoints", keypoints);
	write(fs, "descriptors", descriptors);
	fs.release();

	waitKey();*/

	//1009
	/*Mat srcImage = imread("cornerTest.jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;
	GaussianBlur(srcImage, srcImage, Size(5, 5), 0.0);

	vector<KeyPoint> keypoints;
	Mat descriptors;

	ORB(10)(srcImage, noArray(), keypoints, descriptors);
	cout << "keypoints.size()=" << keypoints.size() << endl;

	FileStorage fs("Keypoints_9.yml", FileStorage::WRITE);
	write(fs, "keypoints", keypoints);
	write(fs, "descriptors", descriptors);
	fs.release();

	Mat dstImage(srcImage.size(), CV_8UC3);
	cvtColor(srcImage, dstImage, COLOR_GRAY2BGR);
	drawKeypoints(srcImage, keypoints, dstImage);

	KeyPoint element;
	for (int k = 0; k < keypoints.size(); k++) {
		element = keypoints[k];
		RotatedRect rRect = RotatedRect(element.pt, Size2f(element.size, element.size), element.angle);
		Point2f vertices[4];
		rRect.points(vertices);
		for (int i = 0; i < 4; i++)
			line(dstImage, vertices[i], vertices[(i + 1) % 4], Scalar(0, 255, 0), 2);

		circle(dstImage, element.pt, cvRound(element.size / 2), Scalar(rand() % 256, rand() % 256, rand() % 256), 2);
	}
	imshow("dstImage", dstImage);
	waitKey();*/

	//1010
	/*Mat srcImage = imread("cornerTest.jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;
	GaussianBlur(srcImage, srcImage, Size(5, 5), 0.0);

	vector<KeyPoint> keypoints;
	Mat descriptos;

	BRISK bristF;
	bristF(srcImage, noArray(), keypoints, descriptos);
	cout << "keypoints.size()=" << keypoints.size() << endl;

	KeyPointsFilter::removeDuplicated(keypoints);
	KeyPointsFilter::retainBest(keypoints, 20);
	cout << "keypoints.size()=" << keypoints.size() << endl;
	bristF.compute(srcImage, keypoints, descriptos);

	FileStorage fs("Keypoints_BRISK.yml", FileStorage::WRITE);
	write(fs, "keypoints", keypoints);
	write(fs, "descriptos", descriptos);
	fs.release();

	Mat dstImgae(srcImage.size(), CV_8UC3);
	cvtColor(srcImage, dstImgae, COLOR_GRAY2BGR);
	drawKeypoints(srcImage, keypoints, dstImgae);

	KeyPoint element;
	for (int k = 0; k < keypoints.size(); k++) {
		element = keypoints[k];
		RotatedRect rRect = RotatedRect(element.pt, Size2f(element.size, element.size), element.angle);
		Point2f vertices[4];
		rRect.points(vertices);
		for (int i = 0; i < 4; i++)
			line(dstImgae, vertices[i], vertices[(i + 1) % 4], Scalar(0, 255, 0), 2);

		circle(dstImgae, element.pt, cvRound(element.size / 2), Scalar(rand() % 256, rand() % 256, rand() % 256), 2);
	}
	imshow("dstImgae", dstImgae);
	waitKey();*/

	//1011
	/*Mat srcImage = imread("cornerTest.jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;
	GaussianBlur(srcImage, srcImage, Size(5, 5), 0.0);

	vector<KeyPoint> keypoints;
	Mat descriptors;

	SIFT siftF(10, 5);
	siftF.detect(srcImage, keypoints);
	cout << "keypoints.size()=" << keypoints.size() << endl;

	FileStorage fs("Keypoints_SIFT.yml", FileStorage::WRITE);
	write(fs, "keypoints", keypoints);
	write(fs, "descriptors", descriptors);
	fs.release();

	Mat dstImage(srcImage.size(), CV_8UC3);
	cvtColor(srcImage, dstImage, COLOR_GRAY2BGR);
	drawKeypoints(srcImage, keypoints, dstImage);

	KeyPoint element;
	for (int k = 0; k < keypoints.size(); k++) {
		element = keypoints[k];
		RotatedRect rRect = RotatedRect(element.pt, Size2f(element.size, element.size), element.angle);
		Point2f vertices[4];
		rRect.points(vertices);
		for (int i = 0; i < 4; i++)
			line(dstImage, vertices[i], vertices[(i + 1) % 4], Scalar(rand() % 256, rand() % 256, rand() % 256), 2);
	}
	imshow("dstImage", dstImage);
	waitKey();*/

	//1012
	/*Mat srcImage = imread("cornerTest.jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;

	vector<KeyPoint> keypoints;
	Mat descriptors;

	SurfFeatureDetector surF(1000);
	surF.detect(srcImage, keypoints);

	KeyPointsFilter::retainBest(keypoints,100);
	cout << "keypoints.size()=" << keypoints.size() << endl;

	surF.compute(srcImage, keypoints, descriptors);

	FileStorage fs("Keypoints_SURF.yml", FileStorage::WRITE);
	write(fs, "keypoints", keypoints);
	write(fs, "descriptors", descriptors);
	fs.release();

	Mat dstImage(srcImage.size(), CV_8UC3);
	cvtColor(srcImage, dstImage, COLOR_GRAY2BGR);
	drawKeypoints(srcImage, keypoints, dstImage);

	KeyPoint element;
	for (int k = 0; k < keypoints.size(); k++) {
		element = keypoints[k];
		RotatedRect rRect = RotatedRect(element.pt, Size2f(element.size, element.size), element.angle);
		Point2f vertices[4];
		rRect.points(vertices);
		for (int i = 0; i < 4; i++) {
			line(dstImage, vertices[i], vertices[(i + 1) % 4], Scalar(rand() % 256, rand() % 256, rand() % 256), 2);
		}
	}

	imshow("dstImage", dstImage);
	waitKey();*/

	//1013
	/*Mat srcImage1 = imread("cup1.jpg", IMREAD_GRAYSCALE);
	Mat srcImage2 = imread("cup2_2.jpg", IMREAD_GRAYSCALE);
	if(srcImage1.empty() || srcImage2.empty())
		return -1;
	vector<KeyPoint> keypoints1, keypoints2;

	FastFeatureDetector fastF(10, true);
	fastF.detect(srcImage1, keypoints1);
	fastF.detect(srcImage2, keypoints2);
	cout << "keypoints1.size()=" << keypoints1.size() << endl;
	cout << "keypoints2.size()=" << keypoints2.size() << endl;

	Mat descriptor1, descriptor2;

	FREAK extractor;
	//BriefDescriptorExtractor extractor;
	extractor.compute(srcImage1, keypoints1, descriptor1);
	extractor.compute(srcImage2, keypoints2, descriptor2);

	vector<DMatch> matches;
	BFMatcher matcher(NORM_HAMMING);
	matcher.match(descriptor1, descriptor2, matches);

	cout << "maches.size()=" << matches.size() << endl;
	if (matches.size() < 4)
		return 0;
	double minDist, maxDist;
	minDist = maxDist = matches[0].distance;
	for (int i = 1; i < matches.size(); i++) {
		double dist = matches[i].distance;
		if (dist < minDist) minDist = dist;
		if (dist > maxDist) maxDist = dist;
	}
	cout << "minDist=" << minDist << endl;
	cout << "maxDist=" << maxDist << endl;

	vector<DMatch> goodMatches;
	double fTh = 2 * minDist;
	for (int i = 0; i < matches.size(); i++) {
		if (matches[i].distance <= max(fTh, 0.02))
			goodMatches.push_back(matches[i]);
	}
	cout << "goodMatches.size()=" << goodMatches.size() << endl;
	if (goodMatches.size() < 4)
		return 0;

	Mat imgMatches;
	drawMatches(srcImage1, keypoints1, srcImage2, keypoints2, goodMatches, imgMatches, Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	vector<Point2f> obj;
	vector<Point2f> scene;
	for (int i = 0; i < goodMatches.size(); i++) {
		obj.push_back(keypoints1[goodMatches[i].queryIdx].pt);
		scene.push_back(keypoints2[goodMatches[i].trainIdx].pt);
	}
	Mat H = findHomography(obj, scene, CV_RANSAC);

	vector<Point2f> objP(4);
	objP[0] = cvPoint(0, 0);
	objP[1] = cvPoint(srcImage1.cols, 0);
	objP[2] = cvPoint(srcImage1.cols, srcImage1.rows);
	objP[3] = cvPoint(0, srcImage1.rows);

	vector<Point2f> sceneP(4);
	perspectiveTransform(objP, sceneP, H);

	for (int i = 0; i < 4; i++) {
		sceneP[i] += Point2f(srcImage1.cols, 0);
	}
	for (int i = 0; i < 4; i++)
		line(imgMatches, sceneP[i], sceneP[(i + 1) % 4], Scalar(255, 0, 0), 4);
	imshow("imgMatches", imgMatches);
	waitKey();*/

	//1014
	/*Mat srcImage1 = imread("cup1.jpg", IMREAD_GRAYSCALE);
	Mat srcImage2 = imread("cup2_1.jpg", IMREAD_GRAYSCALE);
	if (srcImage1.empty() || srcImage2.empty())
		return -1;

	vector<KeyPoint> keypoints1, keypoints2;
	Mat descriptor1, descriptor2;

	//BRISK()(srcImage1, noArray(), keypoints1, descriptor1);
	//BRISK()(srcImage2, noArray(), keypoints2, descriptor2);

	ORB(1000)(srcImage1, noArray(), keypoints1, descriptor1);
	ORB(1000)(srcImage2, noArray(), keypoints2, descriptor2);

	vector<DMatch> matches;
	BFMatcher matcher(NORM_HAMMING);;
	matcher.match(descriptor1, descriptor2, matches);

	cout << "matches.size()=" << matches.size() << endl;
	if (matches.size()<4)
		return 0;

	double minDist, maxDist;
	minDist = maxDist = matches[0].distance;
	for (int i = 1; i < matches.size(); i++) {
		double dist = matches[i].distance;
		if (dist < minDist)	minDist = dist;
		if (dist > maxDist)	maxDist = dist;
	}
	cout << "minDist=" << minDist << endl;
	cout << "maxDist=" << maxDist << endl;

	vector<DMatch> goodMatches;
	double fTh = 4 * minDist;
	for (int i = 0; i < matches.size(); i++) {
		if (matches[i].distance <= max(fTh, 0.02))
			goodMatches.push_back(matches[i]);
	}
	cout << "goodMatches.size()=" << goodMatches.size() << endl;
	if (goodMatches.size() < 4)
		return 0;

	Mat imgMatches;
	drawMatches(srcImage1, keypoints1, srcImage2, keypoints2, goodMatches, imgMatches, Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	vector<Point2f> obj;
	vector<Point2f> scene;
	for (int i = 0; i < goodMatches.size(); i++) {
		obj.push_back(keypoints1[goodMatches[i].queryIdx].pt);
		scene.push_back(keypoints2[goodMatches[i].trainIdx].pt);
	}
	Mat H = findHomography(obj, scene, RANSAC);

	vector<Point2f> objF(4);
	objF[0] = Point2f(0, 0);
	objF[1] = Point2f(srcImage1.cols, 0);
	objF[2] = Point2f(srcImage1.cols, srcImage1.rows);
	objF[3] = Point2f(0, srcImage1.rows);

	vector<Point2f> sceneF(4);
	perspectiveTransform(objF, sceneF, H);

	for (int i = 0; i < 4; i++)
		sceneF[i] += Point2f(srcImage1.cols, 0);

	for (int i = 0; i < 4; i++)
		line(imgMatches, sceneF[i], sceneF[(i + 1) % 4], Scalar(255, 0, 0), 4);

	imshow("imgMateces", imgMatches);
	waitKey();*/

	//1015
	/*Mat srcImage1 = imread("cup1.jpg", IMREAD_GRAYSCALE);
	Mat srcImage2 = imread("cup2_2.jpg", IMREAD_GRAYSCALE);
	if (srcImage1.empty() || srcImage2.empty())
		return -1;

	vector<KeyPoint> keypoints1, keypoints2;

	//SiftFeatureDetector detector(500, 5);
	SurfFeatureDetector detector(400);
	detector.detect(srcImage1, keypoints1);
	detector.detect(srcImage2, keypoints2);

	Mat descriptor1, descriptor2;
	//SiftDescriptorExtractor extractor;
	SurfDescriptorExtractor extractor;

	extractor.compute(srcImage1, keypoints1, descriptor1);
	extractor.compute(srcImage2, keypoints2, descriptor2);

	vector<DMatch> matches;
	BFMatcher matcher(NORM_L2);
	matcher.match(descriptor1, descriptor2, matches);

	cout << "matches.size()=" << matches.size() << endl;
	if (matches.size() < 4)
		return 0;

	double minDist, maxDist;
	minDist = maxDist = matches[0].distance;
	for (int i = 1; i < matches.size(); i++) {
		double dist = matches[i].distance;
		if (dist < minDist)	minDist = dist;
		if (dist > maxDist)	maxDist = dist;
	}
	cout << "minDist=" << minDist << endl;
	cout << "maxDist=" << maxDist << endl;

	vector<DMatch> goodMatches;
	double fTh = 4 * minDist;
	for (int i = 0; i < matches.size(); i++) {
		if (matches[i].distance <= max(fTh, 0.02))
			goodMatches.push_back(matches[i]);
	}
	cout << "goodMatches.size()=" << goodMatches.size() << endl;
	if (goodMatches.size() < 4)
		return 0;

	Mat imgMatches;
	drawMatches(srcImage1, keypoints1, srcImage2, keypoints2, goodMatches, imgMatches, Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	vector<Point2f> obj;
	vector<Point2f> scene;
	for (int i = 0; i < goodMatches.size(); i++) {
		obj.push_back(keypoints1[goodMatches[i].queryIdx].pt);
		scene.push_back(keypoints2[goodMatches[i].trainIdx].pt);
	}
	Mat H = findHomography(obj, scene, RANSAC);

	vector<Point2f> objF(4);
	objF[0] = Point2f(0, 0);
	objF[1] = Point2f(srcImage1.cols, 0);
	objF[2] = Point2f(srcImage1.cols, srcImage1.rows);
	objF[3] = Point2f(0, srcImage1.rows);

	vector<Point2f> sceneF(4);
	perspectiveTransform(objF, sceneF, H);

	for (int i = 0; i < 4; i++)
		sceneF[i] += Point2f(srcImage1.cols, 0);

	for (int i = 0; i < 4; i++)
		line(imgMatches, sceneF[i], sceneF[(i + 1) % 4], Scalar(255, 0, 0), 4);

	imshow("imgMateces", imgMatches);
	waitKey();*/

	//1016
	/*Mat srcImage1 = imread("cup1.jpg", IMREAD_GRAYSCALE);
	Mat srcImage2 = imread("cup2_2.jpg", IMREAD_GRAYSCALE);
	if (srcImage1.empty() || srcImage2.empty())
		return -1;

	vector<KeyPoint> keypoints1, keypoints2;

	//SiftFeatureDetector detector(500, 5);
	SurfFeatureDetector detector(400);
	detector.detect(srcImage1, keypoints1);
	detector.detect(srcImage2, keypoints2);

	Mat descriptor1, descriptor2;
	//SiftDescriptorExtractor extractor;
	SurfDescriptorExtractor extractor;

	extractor.compute(srcImage1, keypoints1, descriptor1);
	extractor.compute(srcImage2, keypoints2, descriptor2);

	vector<DMatch> matches;
	//BFMatcher matcher(NORM_L2);
	FlannBasedMatcher matcher;
	matcher.match(descriptor1, descriptor2, matches);

	cout << "matches.size()=" << matches.size() << endl;
	if (matches.size() < 4)
		return 0;

	double minDist, maxDist;
	minDist = maxDist = matches[0].distance;
	for (int i = 1; i < matches.size(); i++) {
		double dist = matches[i].distance;
		if (dist < minDist)	minDist = dist;
		if (dist > maxDist)	maxDist = dist;
	}
	cout << "minDist=" << minDist << endl;
	cout << "maxDist=" << maxDist << endl;

	vector<DMatch> goodMatches;
	double fTh = 4 * minDist;
	for (int i = 0; i < matches.size(); i++) {
		if (matches[i].distance <= max(fTh, 0.02))
			goodMatches.push_back(matches[i]);
	}
	cout << "goodMatches.size()=" << goodMatches.size() << endl;
	if (goodMatches.size() < 4)
		return 0;

	Mat imgMatches;
	drawMatches(srcImage1, keypoints1, srcImage2, keypoints2, goodMatches, imgMatches, Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	vector<Point2f> obj;
	vector<Point2f> scene;
	for (int i = 0; i < goodMatches.size(); i++) {
		obj.push_back(keypoints1[goodMatches[i].queryIdx].pt);
		scene.push_back(keypoints2[goodMatches[i].trainIdx].pt);
	}
	Mat H = findHomography(obj, scene, RANSAC);

	vector<Point2f> objF(4);
	objF[0] = Point2f(0, 0);
	objF[1] = Point2f(srcImage1.cols, 0);
	objF[2] = Point2f(srcImage1.cols, srcImage1.rows);
	objF[3] = Point2f(0, srcImage1.rows);

	vector<Point2f> sceneF(4);
	perspectiveTransform(objF, sceneF, H);

	for (int i = 0; i < 4; i++)
		sceneF[i] += Point2f(srcImage1.cols, 0);

	for (int i = 0; i < 4; i++)
		line(imgMatches, sceneF[i], sceneF[(i + 1) % 4], Scalar(255, 0, 0), 4);

	imshow("imgMateces", imgMatches);
	waitKey();*/

	//1017
	/*Mat srcImage1 = imread("cup1.jpg", IMREAD_GRAYSCALE);
	Mat srcImage2 = imread("cup2_2.jpg", IMREAD_GRAYSCALE);
	if (srcImage1.empty() || srcImage2.empty())
		return -1;

	vector<KeyPoint> keypoints1, keypoints2;

	SiftFeatureDetector detector(500, 5);
	//SurfFeatureDetector detector(400);
	detector.detect(srcImage1, keypoints1);
	detector.detect(srcImage2, keypoints2);

	Mat descriptor1, descriptor2;
	SiftDescriptorExtractor extractor;
	//SurfDescriptorExtractor extractor;

	extractor.compute(srcImage1, keypoints1, descriptor1);
	extractor.compute(srcImage2, keypoints2, descriptor2);


	//Diff
	vector<vector<DMatch>> matches;

	int k = 2;
	//BFMatcher matcher(NORM_L2);
	FlannBasedMatcher matcher;
	matcher.knnMatch(descriptor1, descriptor2, matches, k);

	cout << "matches.size()=" << matches.size() << endl;

	vector<DMatch> goodMatches;
	float nndrRatio = 0.4f;
	for (int i = 0; i < matches.size(); i++) {
		cout << "matches[i].size()=" << matches[i].size() << endl;
		if (matches.at(i).size()==2 && matches.at(i).at(0).distance <= nndrRatio*matches.at(i).at(1).distance)
			goodMatches.push_back(matches[i][0]);
	}
	cout << "goodMatches.size()=" << goodMatches.size() << endl;
	if (goodMatches.size() < 4)
		return 0;

	Mat imgMatches;
	drawMatches(srcImage1, keypoints1, srcImage2, keypoints2, goodMatches, imgMatches, Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	vector<Point2f> obj;
	vector<Point2f> scene;
	for (int i = 0; i < goodMatches.size(); i++) {
		obj.push_back(keypoints1[goodMatches[i].queryIdx].pt);
		scene.push_back(keypoints2[goodMatches[i].trainIdx].pt);
	}
	Mat H = findHomography(obj, scene, RANSAC);

	vector<Point2f> objF(4);
	objF[0] = Point2f(0, 0);
	objF[1] = Point2f(srcImage1.cols, 0);
	objF[2] = Point2f(srcImage1.cols, srcImage1.rows);
	objF[3] = Point2f(0, srcImage1.rows);

	vector<Point2f> sceneF(4);
	perspectiveTransform(objF, sceneF, H);

	for (int i = 0; i < 4; i++)
		sceneF[i] += Point2f(srcImage1.cols, 0);

	for (int i = 0; i < 4; i++)
		line(imgMatches, sceneF[i], sceneF[(i + 1) % 4], Scalar(255, 0, 0), 4);

	imshow("imgMateces", imgMatches);
	waitKey();*/

	//1018
	/*Mat srcImage1 = imread("cup1.jpg", IMREAD_GRAYSCALE);
	Mat srcImage2 = imread("cup2_1.jpg", IMREAD_GRAYSCALE);
	if (srcImage1.empty() || srcImage2.empty())
		return -1;

	vector<KeyPoint> keypoints1, keypoints2;
	Mat descriptor1, descriptor2;

	ORB(1000)(srcImage1, noArray(), keypoints1, descriptor1);
	ORB(1000)(srcImage2, noArray(), keypoints2, descriptor2);
	cout << "keypoints1.size()=" << keypoints1.size() << endl;
	cout << "keypoints2.size()=" << keypoints2.size() << endl;

	//Diff
	vector<vector<DMatch>> matches;

	int k = 2;
	BFMatcher matcher(NORM_HAMMING);
	matcher.knnMatch(descriptor1, descriptor2, matches, k);

	cout << "matches.size()=" << matches.size() << endl;

	vector<DMatch> goodMatches;
	float nndrRatio = 0.6f;
	for (int i = 0; i < matches.size(); i++) {
		cout << "matches[i].size()=" << matches[i].size() << endl;
		if (matches.at(i).size() == 2 && matches.at(i).at(0).distance <= nndrRatio * matches.at(i).at(1).distance)
			goodMatches.push_back(matches[i][0]);
	}
	cout << "goodMatches.size()=" << goodMatches.size() << endl;
	if (goodMatches.size() < 4)
		return 0;

	Mat imgMatches;
	drawMatches(srcImage1, keypoints1, srcImage2, keypoints2, goodMatches, imgMatches, Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	vector<Point2f> obj;
	vector<Point2f> scene;
	for (int i = 0; i < goodMatches.size(); i++) {
		obj.push_back(keypoints1[goodMatches[i].queryIdx].pt);
		scene.push_back(keypoints2[goodMatches[i].trainIdx].pt);
	}
	Mat H = findHomography(obj, scene, RANSAC);

	vector<Point2f> objF(4);
	objF[0] = Point2f(0, 0);
	objF[1] = Point2f(srcImage1.cols, 0);
	objF[2] = Point2f(srcImage1.cols, srcImage1.rows);
	objF[3] = Point2f(0, srcImage1.rows);

	vector<Point2f> sceneF(4);
	perspectiveTransform(objF, sceneF, H);

	for (int i = 0; i < 4; i++)
		sceneF[i] += Point2f(srcImage1.cols, 0);

	for (int i = 0; i < 4; i++)
		line(imgMatches, sceneF[i], sceneF[(i + 1) % 4], Scalar(255, 0, 0), 4);

	imshow("imgMateces", imgMatches);
	waitKey();*/

	//1019
	/*Mat srcImage1 = imread("cup1.jpg", IMREAD_GRAYSCALE);
	Mat srcImage2 = imread("cup2_2.jpg", IMREAD_GRAYSCALE);
	if (srcImage1.empty() || srcImage2.empty())
		return -1;

	vector<KeyPoint> keypoints1, keypoints2;
	Mat descriptor1, descriptor2;

	ORB(1000)(srcImage1, noArray(), keypoints1, descriptor1);
	ORB(1000)(srcImage2, noArray(), keypoints2, descriptor2);
	cout << "keypoints1.size()=" << keypoints1.size() << endl;
	cout << "keypoints2.size()=" << keypoints2.size() << endl;

	//Diff
	vector<vector<DMatch>> matches;

	int k = 2;
	Mat indices;
	Mat dists;
	flann::Index flannIndex(descriptor2, flann::LshIndexParams(12, 20, 2), cvflann::FLANN_DIST_HAMMING);
	flannIndex.knnSearch(descriptor1, indices, dists, k, flann::SearchParams());

	vector<DMatch> goodMatches;
	float nndrRatio = 0.6f;
	for (int i = 0; i < descriptor1.rows; i++) {
		float d1, d2;
		d1 = (float)dists.at<int>(i, 0);
		d2 = (float)dists.at<int>(i, 1);

		if (indices.at<int>(i, 0) >= 0 && indices.at<int>(i, 1) >= 0 && d1 <= nndrRatio * d2) {
			DMatch match(i, indices.at<int>(i, 0), d1);
			goodMatches.push_back(match);
		}

	}
	cout << "goodMatches.size()=" << goodMatches.size() << endl;
	if (goodMatches.size() < 4)
		return 0;

	Mat imgMatches;
	drawMatches(srcImage1, keypoints1, srcImage2, keypoints2, goodMatches, imgMatches, Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	vector<Point2f> obj;
	vector<Point2f> scene;
	for (int i = 0; i < goodMatches.size(); i++) {
		obj.push_back(keypoints1[goodMatches[i].queryIdx].pt);
		scene.push_back(keypoints2[goodMatches[i].trainIdx].pt);
	}
	Mat H = findHomography(obj, scene, RANSAC);

	vector<Point2f> objF(4);
	objF[0] = Point2f(0, 0);
	objF[1] = Point2f(srcImage1.cols, 0);
	objF[2] = Point2f(srcImage1.cols, srcImage1.rows);
	objF[3] = Point2f(0, srcImage1.rows);

	vector<Point2f> sceneF(4);
	perspectiveTransform(objF, sceneF, H);

	for (int i = 0; i < 4; i++)
		sceneF[i] += Point2f(srcImage1.cols, 0);

	for (int i = 0; i < 4; i++)
		line(imgMatches, sceneF[i], sceneF[(i + 1) % 4], Scalar(255, 0, 0), 4);

	imshow("imgMateces", imgMatches);
	waitKey();*/

	//1020
	/*Mat srcImage1 = imread("cup1.jpg", IMREAD_GRAYSCALE);
	Mat srcImage2 = imread("cup2_2.jpg", IMREAD_GRAYSCALE);
	if (srcImage1.empty() || srcImage2.empty())
		return -1;

	vector<KeyPoint> keypoints1, keypoints2;

	SurfFeatureDetector detector(400);
	detector.detect(srcImage1, keypoints1);
	detector.detect(srcImage2, keypoints2);

	Mat descriptor1, descriptor2;
	SurfDescriptorExtractor extractor;

	extractor.compute(srcImage1, keypoints1, descriptor1);
	extractor.compute(srcImage2, keypoints2, descriptor2);


	//Diff
	vector<vector<DMatch>> matches;

	float maxDistance = 0.5;
	//BFMatcher matcher(NORM_L2);
	FlannBasedMatcher matcher;
	matcher.radiusMatch(descriptor1, descriptor2, matches, maxDistance);
	cout << "matches.size()=" << matches.size() << endl;

	vector<DMatch> goodMatches;
	for (int i = 0; i < matches.size(); i++) {
		goodMatches.clear();
		cout << "matches[" << i << "].size()=" << matches[i].size() << endl;
		for (int j = 0; j < matches[i].size(); j++) {
			goodMatches.push_back(matches[i][j]);
		}

		cout << "goodMatches.size()=" << goodMatches.size() << endl;

		Mat imgMatches;
		drawMatches(srcImage1, keypoints1, srcImage2, keypoints2, goodMatches, imgMatches, Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

		Point ptCenter1, ptCenter2;
		if (matches[i].size() >0) {
			ptCenter1 = keypoints2[matches[i][0].trainIdx].pt;
			ptCenter1 += Point(srcImage1.cols, 0);
			circle(imgMatches, ptCenter1, 5, Scalar(0, 0, 255), 2);
		}
		if (matches[i].size() > 1) {
			ptCenter2 = keypoints2[matches[i][1].trainIdx].pt;
			ptCenter2 += Point(srcImage1.cols, 0);
			circle(imgMatches, ptCenter2, 5, Scalar(255, 0, 0), 2);
		}

		imshow("imgMatches", imgMatches);
		waitKey();
	}*/
	
	//1021
	

	return 0;

}