#include "pch.h"
#include "opencv.hpp"
#include <iomanip>
using namespace cv;
using namespace std;

//0901, 3
//vector<Point> FindLocalMaxima(Mat& src);

//0904
vector<Point2f> FindLocalMaxima(Mat& src);

//0910
void onMouse(int event, int x, int y, int flags, void *param);
vector<Point> g_points;

//0916
vector<vector<Point>> myFindContours(Mat &srcImage);

//0918
void PrintMat(const char *strName, Mat A);

//0919
typedef enum { HORZ2, VERT2, CENT3, DIAG4 }HAAR_TYPE;
double HaarLikeFfeature(Mat &sumA, Size windowSize, HAAR_TYPE haarType);

int main()
{
	//0901
	/*Mat srcImage = imread("CornerTest.jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;

	Mat cornerMap;
	preCornerDetect(srcImage, cornerMap, 3);

	cornerMap = abs(cornerMap);
	threshold(cornerMap, cornerMap, 0.01, 0, THRESH_TOZERO);

	vector<Point>cornerPoints = FindLocalMaxima(cornerMap);
	cout << "cornerPoints.size() = " << cornerPoints.size() << endl;

	Mat dstImage(srcImage.size(), CV_8UC3);
	cvtColor(srcImage, dstImage, COLOR_GRAY2BGR);

	vector<Point>::const_iterator it;
	for (it = cornerPoints.begin(); it != cornerPoints.end(); it++) {
		circle(dstImage, *it, 5, Scalar(0, 0, 255), 2);
	}

	imshow("dstImage", dstImage);
	waitKey();*/

	//0902
	/*Mat srcImage = imread("CornerTest.jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;

	int blockSize = 5;
	int kSize = 3;
	Mat eigenVal;
	cornerMinEigenVal(srcImage, eigenVal, blockSize, kSize);

	Mat dstImage(srcImage.size(), CV_8UC3);
	cvtColor(srcImage, dstImage, COLOR_GRAY2BGR);

	float eval;
	for (int y = 0; y < eigenVal.rows; y++)
		for (int x = 0; x < eigenVal.cols; x++) {
			eval = eigenVal.at<float>(y, x);
			if (eval > 0.2) {
				circle(dstImage, Point(x, y), 5, Scalar(0, 0, 255), 2);
				cout << "eval(" << x << "," << y << ")=" << eval << endl;
			}
		}
		imshow("dstImage", dstImage);*/

		//0903
		/*Mat srcImage = imread("CornerTest.jpg", IMREAD_GRAYSCALE);
				if (srcImage.empty())
					return -1;

				int blockSize = 5;
				int ksize = 3;
				double k = 0.01;

				Mat R;
				cornerHarris(srcImage, R, blockSize, ksize, k);
				threshold(R, R, 0.01, 0, THRESH_TOZERO);

				vector<Point> cornerPoints = FindLocalMaxima(R);
				cout << "cornerPoints.size=" << cornerPoints.size() << endl;

				Mat dstImage(srcImage.size(), CV_8UC3);
				cvtColor(srcImage, dstImage, COLOR_GRAY2BGR);

				vector<Point>::const_iterator it;
				for (it = cornerPoints.begin(); it != cornerPoints.end(); it++) {
					circle(dstImage, *it, 5, Scalar(0, 0, 255), 2);
					int x = (*it).x;
					int y = (*it).y;
					float fvalue = R.at<float>(y, x);
					cout << "cornerPoints(" << (*it).x << "," << (*it).y << ")=" << fvalue << endl;
				}
				imshow("d", dstImage);*/

				//0905
				/*Mat srcImage = imread("CornerTest.jpg", IMREAD_GRAYSCALE);
							if (srcImage.empty())
								return -1;
							int blockSize = 5;
							int ksize = 3;
							double k = 0.01;

							Mat R;
							cornerHarris(srcImage, R, blockSize, ksize, k);
							threshold(R, R, 0.01, 0, THRESH_TOZERO);

							vector<Point2f> cornerPoints = FindLocalMaxima(R);
							cout << "cornerPoints.size()=" << cornerPoints.size() << endl;

							Size winSizw(3, 3);
							Size zeroZone(-1, -1);
							TermCriteria criteria(TermCriteria::COUNT + TermCriteria::EPS, 10, 0.01);
							cornerSubPix(srcImage, cornerPoints, winSizw, zeroZone, criteria);

							Mat dstImage(srcImage.size(), CV_8UC3);
							cvtColor(srcImage, dstImage, COLOR_GRAY2BGR);

							vector<Point2f>::const_iterator it;
							for (it = cornerPoints.begin(); it != cornerPoints.end(); it++) {
								circle(dstImage, *it, 5, Scalar(0, 0, 255), 2);
								int x = cvRound((*it).x);
								int y = cvRound((*it).y);
								float fvalue = R.at<float>(y, x);
								cout << "cornerPoints(" << (*it).x << "," << (*it).y << ")=" << fvalue << endl;
							}
							imshow("d", dstImage);*/

							//0906
							/*Mat srcImage = imread("CornerTest.jpg", IMREAD_GRAYSCALE);
											if (srcImage.empty())
												return -1;

											int maxCorners = 8;
											double quailtyLevel = 0.001;
											double minDistnace = 10;
											int blockSize = 3;
											bool useHarrisDetector = true;
											double k = 0.04;

											vector<Point> cornerPoints;
											goodFeaturesToTrack(srcImage, cornerPoints, maxCorners, quailtyLevel, minDistnace, noArray(), blockSize, useHarrisDetector, k);
											cout << "size()=" << cornerPoints.size() << endl;

											Mat dstImage(srcImage.size(), CV_8UC3);
											cvtColor(srcImage, dstImage, COLOR_GRAY2BGR);

											vector<Point>::const_iterator it;
											for (it = cornerPoints.begin(); it != cornerPoints.end(); it++) {
												circle(dstImage, *it, 5, Scalar(0, 0, 255), 2);
												cout << "CornerPoints(" << (*it).x << "," << (*it).y << ")" << endl;
											}
											imshow("d", dstImage);*/

											//0907
											/*Mat srcImage = imread("momentTest.jpg", IMREAD_GRAYSCALE);
																if (srcImage.empty())
																	return -1;
																Moments M = moments(srcImage, true);

																cout << "spatial moments" << endl;
																cout << "M.m00=" << M.m00 << endl;
																cout << "M.m10=" << M.m10 << endl;
																cout << "M.m20=" << M.m20 << endl;
																cout << "M.m30=" << M.m30 << endl;

																cout << "M.m01=" << M.m01 << endl;
																cout << "M.m11=" << M.m11 << endl;
																cout << "M.m21=" << M.m21 << endl;

																cout << "M.m02=" << M.m02 << endl;
																cout << "M.m12=" << M.m12 << endl;
																cout << "M.m03=" << M.m03 << endl;

																Point2f center;
																center.x = M.m10 / M.m00;
																center.y = M.m01 / M.m00;
																cout << "mass center=" << center << endl;

																Mat dstImage;
																cvtColor(srcImage, dstImage, COLOR_GRAY2BGR);
																circle(dstImage, center, 5, Scalar(0, 0, 255), -1);
																imshow("d", dstImage);

																cout << "centeral moments" << endl;
																cout << "M.mu00=" << M.m00 << endl;
																cout << "M.mu10=" << 0 << endl;
																cout << "M.mu20=" << M.mu20 << endl;
																cout << "M.mu30=" << M.mu30 << endl;

																cout << "M.mu01=" << 0 << endl;
																cout << "M.mu11=" << M.mu11 << endl;
																cout << "M.mu21=" << M.mu21 << endl;

																cout << "M.mu02=" << M.mu02 << endl;
																cout << "M.mu12=" << M.mu12 << endl;
																cout << "M.mu03=" << M.mu03 << endl;

																cout << "central normalized moments" << endl;
																cout << "M.nu00=" << 1 << endl;
																cout << "M.nu10=" << 0 << endl;
																cout << "M.nu20=" << M.mu20 << endl;
																cout << "M.nu30=" << M.mu30 << endl;

																cout << "M.nu01=" << 0 << endl;
																cout << "M.nu11=" << M.mu11 << endl;
																cout << "M.nu21=" << M.mu21 << endl;

																cout << "M.nu02=" << M.mu02 << endl;
																cout << "M.nu12=" << M.mu12 << endl;
																cout << "M.nu03=" << M.mu03 << endl;

																Mat hu;
																HuMoments(M, hu);
																cout << "Hu's moments=" << endl;
																for (int i = 0; i < hu.rows; i++) {
																	cout << "hu[" << i << "]=";
																	cout << hu.at<double>(i) << endl;
																}*/

																//0908
																/*Mat srcImage = imread("momentTest.jpg", IMREAD_GRAYSCALE);
																					if (srcImage.empty())
																						return -1;

																					Mat dstImage;
																					cvtColor(srcImage, dstImage, COLOR_GRAY2BGR);

																					threshold(srcImage, srcImage, 200, 255, THRESH_BINARY);

																					int mode = RETR_LIST;
																					int method = CHAIN_APPROX_SIMPLE;

																					vector<vector<Point>> contours;
																					findContours(srcImage, contours, mode, method);
																					cout << "contours.size()=" << contours.size() << endl;

																					for (int k = 0; k < contours.size(); k++) {

																						Scalar color(rand() & 255, rand() & 255, rand() & 255);
																						drawContours(dstImage, contours, k, color, 4);
																						cout << "contours[" << k << "]'s boundary moments" << endl;

																						Moments M = moments(contours[k]);
																						cout << "spatial moments" << endl;
																						cout << "M.m00=" << M.m00 << endl;
																						cout << "M.m10=" << M.m10 << endl;
																						cout << "M.m20=" << M.m20 << endl;
																						cout << "M.m30=" << M.m30 << endl;

																						cout << "M.m01=" << M.m01 << endl;
																						cout << "M.m11=" << M.m11 << endl;
																						cout << "M.m21=" << M.m21 << endl;

																						cout << "M.m02=" << M.m02 << endl;
																						cout << "M.m12=" << M.m12 << endl;
																						cout << "M.m03=" << M.m03 << endl;

																						Point2f center;
																						center.x = M.m10 / M.m00;
																						center.y = M.m01 / M.m00;
																						cout << "mass center=" << center << endl;

																						circle(dstImage, center, 5, Scalar(0, 0, 255), -1);
																						imshow("d", dstImage);

																						cout << "centeral moments" << endl;
																						cout << "M.mu00=" << M.m00 << endl;
																						cout << "M.mu10=" << 0 << endl;
																						cout << "M.mu20=" << M.mu20 << endl;
																						cout << "M.mu30=" << M.mu30 << endl;

																						cout << "M.mu01=" << 0 << endl;
																						cout << "M.mu11=" << M.mu11 << endl;
																						cout << "M.mu21=" << M.mu21 << endl;

																						cout << "M.mu02=" << M.mu02 << endl;
																						cout << "M.mu12=" << M.mu12 << endl;
																						cout << "M.mu03=" << M.mu03 << endl;

																						cout << "central normalized moments" << endl;
																						cout << "M.nu00=" << 1 << endl;
																						cout << "M.nu10=" << 0 << endl;
																						cout << "M.nu20=" << M.mu20 << endl;
																						cout << "M.nu30=" << M.mu30 << endl;

																						cout << "M.nu01=" << 0 << endl;
																						cout << "M.nu11=" << M.mu11 << endl;
																						cout << "M.nu21=" << M.mu21 << endl;

																						cout << "M.nu02=" << M.mu02 << endl;
																						cout << "M.nu12=" << M.mu12 << endl;
																						cout << "M.nu03=" << M.mu03 << endl;

																						Mat hu;
																						HuMoments(M, hu);
																						cout << "Hu's moments=" << endl;
																						for (int i = 0; i < hu.rows; i++) {
																							cout << "hu[" << i << "]=";
																							cout << hu.at<double>(i) << endl;
																						}
																					}*/

																					//0909
																					/*Mat srcImage = imread("momentTest.jpg", IMREAD_GRAYSCALE);
																										if (srcImage.empty())
																											return -1;
																										Mat dstImage;
																										cvtColor(srcImage, dstImage, COLOR_GRAY2BGR);
																										threshold(srcImage, srcImage, 200, 255, THRESH_BINARY);

																										int mode = RETR_LIST;
																										int method = CHAIN_APPROX_SIMPLE;

																										vector<vector<Point>> contours;
																										findContours(srcImage, contours, mode, method);
																										cout << "contours.size()=" << contours.size() << endl;

																										for (int k = 0; k < contours.size(); k++) {
																											drawContours(dstImage, contours, k, Scalar(0, 0, 255), 4);
																											cout << "contours[" << k << "]'s boundary moments" << endl;

																											Moments M = moments(contours[k]);
																											Point2f center;
																											center.x = M.m10 / M.m00;
																											center.y = M.m01 / M.m00;
																											cout << "mass Center=" << center << endl;
																											circle(dstImage, center, 5, Scalar(0, 0, 255), -1);

																											Mat hu;
																											HuMoments(M, hu);
																											cout << "Hu's 7 moments(contours[k])" << endl;
																											for (int i = 0; i < hu.rows; i++) {
																												cout << "hu[" << i << "]=";
																												cout << hu.at<double>(i) << endl;
																											}

																											cout << endl << "contour2=transform(contours[k])" << endl;
																											double angle = 45.0;
																											double scale = 0.5;
																											Point t(0, 0);
																											cout << "angle=" << angle << endl;
																											cout << "scale=" << scale << endl;
																											cout << "translation-" << t << endl;

																											Mat rot = getRotationMatrix2D(center, angle, scale);
																											rot.col(2).at<double>(0) += t.x;
																											rot.col(2).at<double>(1) += t.y;

																											Mat points(contours[k]);
																											transform(points, points, rot);

																											vector<Point> contour2;
																											points.copyTo(contour2);
																											drawContours(dstImage, vector<vector<Point>>(1, contour2), 0, Scalar(0, 255, 0), 4);

																											Moments M2 = moments(contour2);
																											Point2f center2;
																											center2.x = M2.m10 / M2.m00;
																											center2.y = M2.m01 / M2.m00;
																											cout << "mass center2=" << center2 << endl;
																											circle(dstImage, center2, 5, Scalar(0, 255, 0), -1);

																											Mat hu2;
																											HuMoments(M2, hu2);
																											cout << endl << "Hu's 7 moments(contour2) = " << endl;
																											for (int i = 0; i < hu.rows; i++) {
																												cout << "hu2[" << i << "]=";
																												cout << hu2.at<double>(i) << endl;
																											}
																											double distError = norm(hu, hu2);
																											cout << endl << "distError=" << distError << endl;
																											imshow("dstImage", dstImage);
																										}
																										waitKey();*/

																										//0910
																										/*Mat dstImage(512, 512, CV_8UC3, Scalar::all(255));
																										imshow("dstImage", dstImage);
																										setMouseCallback("dstImage", onMouse, (void*)&dstImage);

																										bool closed = false;
																										bool bEscKey = false;
																										while (!bEscKey) {
																											int nKey = waitKey(0);
																											switch (nKey) {
																												case 27:
																													bEscKey = true;
																													break;
																												case 'r':
																													g_points.clear();
																													dstImage = Scalar::all(255);
																													break;
																												case ' ':
																													if (g_points.size() < 1)
																														break;
																													cout << "g_points.size() = " << g_points.size() << endl;
																													const Point *pts = (const Point*)g_points.data();
																													int npts = g_points.size();
																													polylines(dstImage, &pts, &npts, 1, closed, Scalar(255, 0, 0), 2);

																													double length = arcLength(Mat(g_points), closed);
																													cout << "arcLength=" << length << endl;

																													double area = contourArea(g_points, true);
																													cout << "contourArea=" << area << endl;

																													Rect rect = boundingRect(g_points);
																													rectangle(dstImage, rect, Scalar(0, 0, 255), 2);
																													Point2f center;
																													float radius;
																													minEnclosingCircle(g_points, center, radius);
																													circle(dstImage, center, radius, Scalar(0, 255, 0), 2);
																													RotatedRect minRect = minAreaRect(g_points);
																													Point2f rectPoints[4];
																													minRect.points(rectPoints);
																													for (int j = 0; j < 4; j++)
																														line(dstImage, rectPoints[j], rectPoints[(j + 1) % 4], Scalar(255, 0, 255), 2);
																													break;
																												}
																												imshow("dstImage", dstImage);
																											}*/

																											//0911
																											/*Mat dstImage(512, 512, CV_8UC3, Scalar::all(255));
																																imshow("dstImage", dstImage);
																																setMouseCallback("dstImage", onMouse, (void*)&dstImage);

																																int npts;
																																const Point *pts;
																																Point ptStart, ptEnd;
																																float s = 1000;
																																int distType = CV_DIST_L2;
																																Vec4f lineFit;

																																vector<Point> approxCurve;
																																double epsilon = 50;
																																bool closed = false;
																																bool bEscKey = false;

																																while (!bEscKey) {
																																	int nKey = waitKey(0);
																																	switch (nKey) {
																																	case 27:
																																		bEscKey = true;
																																		break;
																																	case 'r':
																																		g_points.clear();
																																		dstImage = Scalar::all(255);
																																		break;
																																	case '1':
																																		if (g_points.size() < 1)
																																			break;
																																		dstImage = Scalar::all(255);
																																		npts = g_points.size();
																																		pts = (Point*)g_points.data();
																																		polylines(dstImage, &pts, &npts, 1, closed, Scalar(0, 255, 0), 2);

																																		fitLine(g_points, lineFit, distType, 0, 0.01, 0.01);
																																		ptStart.x = cvRound(s*lineFit[0] + lineFit[2]);
																																		ptStart.y = cvRound(s*lineFit[1] + lineFit[3]);
																																		ptEnd.x = cvRound(-s*lineFit[0] + lineFit[2]);
																																		ptEnd.y = cvRound(-s * lineFit[1] + lineFit[3]);
																																		line(dstImage, ptStart, ptEnd, Scalar(255, 0, 0), 2);
																																		break;
																																	case '2':
																																		if (g_points.size() < 1)
																																			break;
																																		dstImage = Scalar::all(255);
																																		cout << "g_points.size() = " << g_points.size() << endl;
																																		npts = g_points.size();
																																		pts = (Point*)g_points.data();
																																		polylines(dstImage, &pts, &npts, 1, closed, Scalar(255, 0, 0), 2);

																																		approxPolyDP(g_points, approxCurve, epsilon, closed);
																																		cout << "approxCurve.size()=" << approxCurve.size() << endl;
																																		pts = (const Point*)approxCurve.data();
																																		npts = approxCurve.size();
																																		polylines(dstImage, &pts, &npts, 1, closed, Scalar(0, 0, 255), 2);
																																		break;
																																	case '3':
																																		if (g_points.size() < 1)
																																			break;
																																		dstImage = Scalar::all(255);
																																		cout << "g_points.size() = " << g_points.size() << endl;
																																		npts = g_points.size();
																																		pts = (Point *)g_points.data();
																																		polylines(dstImage, &pts, &npts, 1, closed, Scalar(0, 0, 255), 2);

																																		RotatedRect rect;
																																		rect = fitEllipse(g_points);
																																		ellipse(dstImage, rect, Scalar(0, 0, 255), 2);
																																		break;
																																	}
																																	imshow("dstImage", dstImage);
																																}*/

																																//0912
																																/*Mat dstImage(512, 512, CV_8UC3, Scalar::all(255));
																																					imshow("dstImage", dstImage);
																																					setMouseCallback("dstImage", onMouse, (void*)&dstImage);

																																					bool bEscKey = false;

																																					while (!bEscKey) {
																																						int nKey = waitKey(0);
																																						switch (nKey) {
																																						case 27:
																																							bEscKey = true;
																																							break;
																																						case 'r':
																																							g_points.clear();
																																							dstImage = Scalar::all(255);
																																							break;
																																						}
																																						imshow("dstImage", dstImage);
																																					}*/

																																					//0913
																																					/*Mat dstImage(512, 512, CV_8UC3, Scalar::all(255));
																																										imshow("dstImage", dstImage);
																																										setMouseCallback("dstImage", onMouse, (void*)&dstImage);

																																										bool bEscKey = false;

																																										while (!bEscKey) {
																																											int nKey = waitKey(0);
																																											switch (nKey) {
																																											case 27:
																																												bEscKey = true;
																																												break;
																																											case 'r':
																																												g_points.clear();
																																												dstImage = Scalar::all(255);
																																												break;
																																											case ' ':
																																												if (g_points.size() < 1)
																																													break;
																																												cout << "isContourConvex(g_points)=" << isContourConvex(g_points) << endl;
																																												vector<Point> hull;
																																												convexHull(g_points, hull);
																																												cout << "g_points.size()=" << g_points.size() << endl;
																																												cout << "hull.size()=" << hull.size() << endl;
																																												drawContours(dstImage, vector<vector<Point>>(1, hull), 0, Scalar(255, 0, 0), 2);
																																												cout << "isContourConvex(hull)=" << isContourConvex(hull) << endl;
																																												break;
																																											}
																																											imshow("dstImage", dstImage);
																																										}*/

																																										//0914
																																										/*Mat dstImage(512, 512, CV_8UC3, Scalar::all(255));
																																														imshow("dstImage", dstImage);
																																														setMouseCallback("dstImage", onMouse, (void*)&dstImage);

																																														vector<int>hull;
																																														vector<Point>ptsHull;
																																														vector<Vec4i>defects;
																																														bool bEscKey = false;

																																														while (!bEscKey) {
																																															int nKey = waitKey(0);
																																															switch (nKey) {
																																															case 27:
																																																bEscKey = true;
																																																break;
																																															case 'r':
																																																g_points.clear();
																																																dstImage = Scalar::all(255);
																																																break;
																																															case ' ':
																																																if (g_points.size() < 1)
																																																	break;

																																																cout << "g_points.size()=" << g_points.size() << endl;

																																																convexHull(g_points, hull);
																																																cout << "hull.size()=" << hull.size() << endl;

																																																ptsHull.clear();
																																																for (int k = 0; k < hull.size(); k++) {
																																																	int i = hull[k];
																																																	ptsHull.push_back(g_points[i]);
																																																}
																																																drawContours(dstImage, vector<vector<Point>>(1, ptsHull), 0, Scalar(255, 0, 0), 2);

																																																convexityDefects(g_points, hull, defects);
																																																for (int k = 0; k < defects.size(); k++) {
																																																	Vec4i v = defects[k];
																																																	Point ptStart = g_points[v[0]];
																																																	Point ptEnd = g_points[v[1]];
																																																	Point ptFar = g_points[v[2]];
																																																	float depth = v[3] / 256.0;
																																																	if (depth > 10) {
																																																		line(dstImage, ptStart, ptFar, Scalar(0, 255, 0), 2);
																																																		line(dstImage, ptEnd, ptFar, Scalar(0, 255, 0), 2);
																																																		circle(dstImage, ptStart, 6, Scalar(0, 0, 255), 2);
																																																		circle(dstImage, ptEnd, 6, Scalar(0, 0, 255), 2);
																																																		circle(dstImage, ptFar, 6, Scalar(0, 0, 255), 2);
																																																	}
																																																}
																																																cout << "defects.size()=" << defects.size() << endl;
																																																break;
																																															}
																																															imshow("dstImage", dstImage);
																																														}*/

																																														//0915
																																														/*Mat srcImage = imread("hand.jpg");
																																														Mat dstImage = srcImage.clone();
																																														GaussianBlur(srcImage, srcImage, Size(3, 3), 0.0);

																																														Mat hsvImage;
																																														cvtColor(srcImage, hsvImage, COLOR_BGR2HSV);
																																														imshow("hsvImage", hsvImage);

																																														Mat bImage;
																																														Scalar lowerb(0, 40, 0);
																																														Scalar upperb(20, 180, 255);
																																														inRange(hsvImage, lowerb, upperb, bImage);
																																														imshow("b", bImage);

																																														erode(bImage, bImage, Mat());
																																														dilate(bImage, bImage, cv::Mat(), Point(-1, -1), 2);
																																														imshow("bImage", bImage);

																																														vector<vector<Point>> contours;
																																														findContours(bImage, contours, noArray(), RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
																																														cout << "contours.size()=" << contours.size() << endl;
																																														if (contours.size() < 1)
																																															return 0;
																																														int maxK = 0;
																																														double maxArea = contourArea(contours[0]);
																																														for (int k = 1; k < contours.size(); k++) {
																																															double area = contourArea(contours[k]);
																																															if (area > maxArea) {
																																																maxK = k;
																																																maxArea = area;
																																															}
																																														}
																																														vector<Point> handContour = contours[maxK];
																																														//vector<Point>handContour(contours[maxK].size());
																																														//copy(contours[maxK].begin(), contours[maxK].end(), handContour.begin());

																																														vector<int> hull;
																																														convexHull(handContour, hull);
																																														cout << "hull.size()=" << hull.size() << endl;

																																														vector<Point> ptsHull;
																																														for (int k = 0; k < hull.size(); k++) {
																																															int i = hull[k];
																																															ptsHull.push_back(handContour[i]);
																																														}
																																														drawContours(dstImage, vector<vector<Point>>(1, ptsHull), 0, Scalar(255, 0, 0), 2);

																																														vector<Vec4i> defects;
																																														convexityDefects(handContour, hull, defects);
																																														for (int k = 0; k < defects.size(); k++) {
																																															Vec4i v = defects[k];
																																															Point ptStart = handContour[v[0]];
																																															Point ptEnd = handContour[v[1]];
																																															Point ptFar = handContour[v[2]];
																																															float depth = v[3] / 256.0;
																																															if (depth > 10) {
																																																line(dstImage, ptStart, ptFar, Scalar(0, 255, 0), 2);
																																																line(dstImage, ptEnd, ptFar, Scalar(0, 255, 0), 2);
																																																circle(dstImage, ptStart, 6, Scalar(0, 0, 255), 2);
																																																circle(dstImage, ptEnd, 6, Scalar(0, 255, 255), 2);
																																																circle(dstImage, ptFar, 6, Scalar(255, 0, 255), 2);
																																															}
																																														}
																																														cout << "defects.size()=" << defects.size() << endl;
																																														imshow("dstImage", dstImage);
																																														waitKey();*/

																																														//0916
	Mat refImage = imread("refShapes.jpg", IMREAD_GRAYSCALE);
	if (refImage.empty())
		return -1;
	Mat testImage = imread("testShapes3.jpg", IMREAD_GRAYSCALE);
	if (testImage.empty())
		return -1;

	Scalar colorTable[] = { Scalar(0,0,255),Scalar(0,255,0),Scalar(255,0,0) };
	vector<vector<Point>> refContours = myFindContours(refImage);
	vector<vector<Point> > testContours = myFindContours(testImage);

	cout << "refContours.size()=" << refContours.size() << endl;
	cout << "testContours.size()=" << testContours.size() << endl;

	if (refContours.size() < 1 || refContours.size() < 1)
		return 0;

	Mat refRGB;
	cvtColor(refImage, refRGB, COLOR_GRAY2BGR);
	for (int k = 0; k < refContours.size(); k++)
		drawContours(refRGB, refContours, k, colorTable[k], 2);
	imshow("refRGB", refRGB);

	Mat testRGB;
	cvtColor(testImage, testRGB, COLOR_GRAY2BGR);

	int minK;
	double minD;
	int method = 2;
	for (int i = 0; i < testContours.size(); i++) {
		minK = 0;
		minD = matchShapes(refContours[0], testContours[i], method, 0);

		for (int k = 1; k < refContours.size(); k++) {
			double d = matchShapes(refContours[k], testContours[i], method, 0);
			if (d < minD) {
				minD = d;
				minK = k;
			}
		}
		drawContours(testRGB, testContours, i, colorTable[minK], 2);
		cout << "minK=" << minK << endl;
	}
	imshow("testRGB", testRGB);
	waitKey(0);

	//0917
	/*Mat refImage = imread("refShapes.jpg", IMREAD_GRAYSCALE);
	if (refImage.empty())
		return -1;
	Scalar colorTable[] = { Scalar(0,0,255),Scalar(0,255,0),Scalar(255,0,0) };

	Mat dstImage(512, 512, CV_8UC3, Scalar::all(255));
	imshow("dstImage", dstImage);
	setMouseCallback("dstImage", onMouse, (void*)&dstImage);

	vector<vector<Point>> refContours = myFindContours(refImage);
	if (refContours.size() < 1)
		return 0;

	Mat refRGB;
	cvtColor(refImage, refRGB, COLOR_GRAY2BGR);
	for (int k = 0; k < refContours.size(); k++)
		drawContours(refRGB, refContours, k, colorTable[k], 2);
	imshow("refImage", refImage);

	int npts;
	const Point* pts;
	vector<Point> approxCurve;

	int method = 3;
	int minK;
	double minD;
	bool bEscKey = false;
	while (!bEscKey) {
		int nKey = waitKey(0);
		switch (nKey) {
		case 27:
			bEscKey = true;
			break;
		case 'r':
			g_points.clear();
			dstImage = Scalar::all(255);
			break;
		case ' ':
			if (g_points.size() < 1)
				break;
			approxCurve = g_points;

			minD = matchShapes(refContours[0], approxCurve, method, 0);
			minK = 0;
			for (int k = 1; k < refContours.size(); k++) {
				double d = matchShapes(refContours[k], approxCurve, method, 0);
				if (d < minD) {
					minD = d;
					minK = k;
				}
			}
			pts = (const Point*)approxCurve.data();
			npts = approxCurve.size();
			polylines(dstImage, &pts, &npts, 1, true, colorTable[minK], 4);
			break;
		}
		imshow("dstImage", dstImage);
	}

	waitKey();*/

	//0918
	/*uchar dataA[19] = { 1,2,3,4,
						5,6,7,8,
						9,10,11,12,
						13,14,15,16 };
	Mat A(4, 4, CV_8U, dataA);
	PrintMat("A=", A);

	Mat sumA, sqsumA, tiltedSumA;
	integral(A, sumA, sqsumA, tiltedSumA);

	PrintMat("sumA=", sumA);
	PrintMat("sqsumA=", sqsumA);
	PrintMat("tiltedSumA=", tiltedSumA);*/

	//0919
	/*uchar dataA[36] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36 };
	Mat A(6, 6, CV_8U, dataA);
	PrintMat("A=", A);

	Mat sumA;
	integral(A, sumA);
	PrintMat("sumA=", sumA);

	Size windowSize = A.size();
	double fH = HaarLikeFfeature(sumA, windowSize, HORZ2);
	double fV = HaarLikeFfeature(sumA, windowSize, VERT2);
	double fC = HaarLikeFfeature(sumA, windowSize, CENT3);
	double fD = HaarLikeFfeature(sumA, windowSize, DIAG4);

	cout << "fH=" << fH << endl;
	cout << "fV=" << fV << endl;
	cout << "fC=" << fC << endl;
	cout << "fD=" << fD << endl;
	cout << "fH=" << fH << endl;*/

	return 0;

}

//0901, 3
/*vector<Point> FindLocalMaxima(Mat& src) {
	Mat dilated;
	Mat localMax;
	Size size(11, 11);
	Mat rectKernel = getStructuringElement(MORPH_RECT, size);

	dilate(src, dilated, rectKernel);
	localMax = (src == dilated);
	imshow("localMax", localMax);


	Mat eroded;
	Mat localMin;
	erode(src, eroded, rectKernel);
	localMin = (src > eroded);
	imshow("localMin", localMin);

	localMax = (localMax & localMin);
	imshow("localMax2", localMax);

	vector<Point> points;
	for(int i=0; i<localMax.rows; i++)
		for (int j = 0; j < localMax.cols; j++) {
			uchar uValue = localMax.at<uchar>(i, j);
			if (uValue)
				points.push_back(Point(j, i));
		}

	return points;
}*/

//0904
/*vector<Point2f> FindLocalMaxima(Mat& src) {
	Mat dilated;
	Mat localMax;

	dilate(src, dilated, Mat());
	localMax = (src == dilated);
	imshow("localMax", localMax);


	Mat eroded;
	Mat localMin;
	erode(src, eroded, Mat());
	localMin = (src > eroded);
	imshow("localMin", localMin);

	localMax = (localMax & localMin);
	imshow("localMax2", localMax);

	vector<Point2f> points;
	for (int i = 0; i < localMax.rows; i++)
		for (int j = 0; j < localMax.cols; j++) {
			uchar uValue = localMax.at<uchar>(i, j);
			if (uValue)
				points.push_back(Point(j, i));
		}

	return points;
}*/

//0910, 11, 13, 14, 17
void onMouse(int event, int x, int y, int flags, void *param) {
	Mat *data = (Mat*)param;
	Mat dstImage = *data;
	switch (event) {
	case EVENT_MOUSEMOVE:
		if (flags & EVENT_FLAG_LBUTTON) {
			circle(dstImage, Point(x, y), 4, Scalar::all(0), -1);
			g_points.push_back(Point(x, y));
		}
		break;
	}
	imshow("dstImage", dstImage);
}

//0912
/*void onMouse(int event, int x, int y, int flags, void *param) {
	Mat *data = (Mat*)param;
	Mat dstImage = *data;

	int npts;
	const Point *pts;
	double dist;

	switch (event) {
	case EVENT_MOUSEMOVE:
		if (flags & EVENT_FLAG_LBUTTON) {
			circle(dstImage, Point(x, y), 4, Scalar::all(0), -1);
			g_points.push_back(Point(x, y));
		}
		break;
	case EVENT_FLAG_RBUTTON:
		dstImage = Scalar::all(255);
		circle(dstImage, Point(x, y), 4, Scalar::all(0), -1);

		npts = g_points.size();
		pts = (Point*)g_points.data();
		polylines(dstImage, &pts, &npts, 1, true, Scalar(255, 0, 0), 2);
		dist = pointPolygonTest(g_points, Point(x, y), true);
		cout << "dist=" << dist << endl;
		if (dist > 0)
			circle(dstImage, Point(x, y), 5, Scalar(0, 255, 0), 4);
		else if (dist < 0)
			circle(dstImage, Point(x, y), 5, Scalar(0,0,255), 4);
		else
			circle(dstImage, Point(x, y), 5, Scalar(255,255,0), 4);
		break;
	}
	imshow("dstImage", dstImage);
}*/

//0916
vector<vector<Point>> myFindContours(Mat &srcImage) {
	GaussianBlur(srcImage, srcImage, Size(3, 3), 0.0);
	Mat bImage;
	threshold(srcImage, bImage, 128, 255, THRESH_BINARY_INV + THRESH_OTSU);
	erode(bImage, bImage, Mat(), Point(-1, -1), 1);

	dilate(bImage, bImage, cv::Mat(), Point(-1, -1), 2);

	vector<vector<Point>> contours;
	findContours(bImage, contours, noArray(), RETR_EXTERNAL, CHAIN_APPROX_NONE);
	return contours;
}

//0918
void PrintMat(const char *strName, Mat A) {
	int x, y;
	uchar uValue;
	float fValue;
	double dValue;
	int iValue;

	cout << endl << endl << strName << endl;
	cout << setiosflags(ios::fixed);
	for (y = 0; y < A.rows; y++) {
		for (x = 0; x < A.cols; x++) {
			switch (A.type())
			{
			case CV_8U:
				uValue = A.at<uchar>(y, x);
				cout << setw(8) << (int)uValue;
				break;
			case CV_32S:
				iValue = A.at<int>(y, x);
				cout << setw(8) << iValue;
				break;
			case CV_32F:
				fValue = A.at<float>(y, x);
				cout << setprecision(2) << setw(8) << fValue;
				break;
			case CV_64F:
				dValue = A.at<double>(y, x);
				cout << setprecision(2) << setw(8) << dValue;
				break;
			}
		}
		cout << endl;
	}
	cout << endl;
}

//0919
double rectSum(Mat &sumA, Rect r) {
	Mat_<int> tmpSum(sumA);
	double a, b, c, d;
	a = tmpSum(r.y, r.x);
	b = tmpSum(r.y, r.x + r.width);
	c = tmpSum(r.y + r.height, r.x);
	d = tmpSum(r.y + r.height, r.x + r.width);

	return (a + d - b - c);
}

double HaarLikeFfeature(Mat &sumA, Size windowSize, HAAR_TYPE haarType) {
	double sum1, sum2, sum3, sum4;
	double fValue;

	Rect r1, r2, r3, r4;
	int width2 = windowSize.width / 2;
	int width3 = windowSize.width / 3;
	int height2 = windowSize.height / 2;
	int height3 = windowSize.height / 3;

	switch (haarType) {
	case HORZ2:
		//W
		r1 = Rect(0, 0, windowSize.width, height2);
		sum1 = rectSum(sumA, r1);

		//B
		r2 = Rect(0, height2, windowSize.width, height2);
		sum2 = rectSum(sumA, r2);
		fValue = sum1 - sum2;
		break;
	case VERT2:
		//B
		r1 = Rect(0, 0, width2, windowSize.height);
		sum1 = rectSum(sumA, r1);

		//W
		r2 = Rect(width2, 0, width2, windowSize.height);
		sum2 = rectSum(sumA, r2);
		fValue = sum2 - sum1;
		break;
	case CENT3:
		r1 = Rect(0, 0, width3, windowSize.height);
		sum1 = rectSum(sumA, r1);

		r2 = Rect(width3, 0, width3, windowSize.height);
		sum2 = rectSum(sumA, r2);

		r3 = Rect(width3 * 2, 0, width3, windowSize.height);
		sum3 = rectSum(sumA, r3);

		fValue = sum1 + sum3 - sum2;
		break;
	case DIAG4:
		r1 = Rect(0, 0, width2, height2);
		sum1 = rectSum(sumA, r1);

		r2 = Rect(width2, 0, width2, height2);
		sum2 = rectSum(sumA, r2);

		r3 = Rect(0, height2, width2, height2);
		sum3 = rectSum(sumA, r3);

		r4 = Rect(width2, height2, width2, height2);
		sum4 = rectSum(sumA, r4);

		fValue = sum2 + sum3 - sum1 - sum4;
		break;
	}
	return fValue;
}