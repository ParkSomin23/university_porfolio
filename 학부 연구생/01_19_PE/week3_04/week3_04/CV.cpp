#include "pch.h"
#include "opencv.hpp"
#include <time.h>
using namespace cv;
using namespace std;

#define RADIAN(x) ((x)*(3.14159265f/180.0f))
#define FLIP_Y(y) ((dstImage.size().height-1)-(y))

int main()
{
	//0414
	/*double dataA[] = { 0.0,1.0,2.0,3.0 };
	Mat A(1, 4, CV_64F, dataA);
	cout << "A=" << A << endl;

	Mat dst1;
	exp(A, dst1);
	cout << "dst1=" << dst1 << endl;

	Mat dst2;
	log(A, dst2);
	cout << "dst2=" << dst2 << endl;

	Mat dst3;
	pow(A, 2.0, dst3);
	cout << "dst3=" << dst3 << endl;

	Mat dst4;
	sqrt(A, dst4);
	cout << "dst4=" << dst4 << endl;*/

	//0415
	/*double dataX[] = { 0.0,10.0,10.0,0.0 };
	double dataY[] = { 0.0,0.0,10.0,10.0 };

	Mat X(1, 4, CV_64F, dataX);
	Mat Y(1, 4, CV_64F, dataY);
	cout << "X=" << X << endl;
	cout << "Y=" << Y << endl;

	Mat mag;
	magnitude(X, Y, mag);
	cout << "mag=" << mag << endl;

	Mat angle1;
	phase(X, Y, angle1);
	cout << "angle1=" << angle1 << endl;

	Mat angle2;
	phase(X, Y, angle2, true);
	cout << "angle2=" << angle2 << endl;

	Mat mag3, angle3;
	cartToPolar(X, Y, mag3, angle3);
	cout << "mag3=" << mag3 << endl;
	cout << "angle3=" << angle3 << endl;

	Mat X3, Y3;
	polarToCart(mag3, angle3, X3, Y3);
	cout << "X3=" << X3 << endl;
	cout << "Y3=" << Y3 << endl;*/

	//0416
	/*double dataA[] = { 1.0,-6.0,11.0,-6.0};
	double dataB[] = { -6.0,11.0,-6.0 };

	Mat A(1, 4, CV_64F, dataA);
	Mat B(1, 3, CV_64F, dataB);
	cout << "A=" << A << endl;
	cout << "B=" <<B << endl;

	Mat X1;
	solveCubic(A, X1);
	cout << "X1=" << X1 << endl;

	Mat X2;
	solveCubic(B, X2);
	cout << "X2=" << X2 << endl;

	Mat A1, X3;
	flip(A, A1, 1);
	cout << "A1=" << A1 << endl;

	solvePoly(A1, X3);
	cout << "X3.size()=" << X3.size() << endl;
	cout << "X3.channels()=" << X3.channels() << endl;
	cout << "X3=" << X3 << endl;*/

	//0417
	/*float dataA[] = { 10,0,30,40,50,60 };
	
	Mat A(2, 3, CV_32F, dataA);
	cout << "A=" << A << endl;

	int nCount = countNonZero(A);
	cout << "nCount=" << nCount << endl;

	cout << "sum(A)=" << sum(A) << endl;
	cout << "mean(A)=" << mean(A) << endl;

	Scalar avg, stddev;
	meanStdDev(A, avg, stddev);
	cout << "avg=" << avg << endl;
	cout << "stddev=" << stddev << endl;
	
	double minVal, maxVal;
	int minIdx[2], maxIdx[2];
	minMaxIdx(A, &minVal, &maxVal, minIdx, maxIdx);
	cout << "minVal=" << minVal << endl;
	cout << "minIdx =[" << minIdx[0] << "," << minIdx[1] << "]" << endl;
	cout << "maxVal=" << maxVal << endl;
	cout<< "maxIdx =[" << maxIdx[0] << "," << maxIdx[1] << "]" << endl;

	Point minLoc, maxLoc;
	minMaxLoc(A, &minVal, &maxVal, &minLoc, &maxLoc);
	cout << "minVal=" << minVal << endl;
	cout << "minLoc=" << minLoc << endl;
	cout << "maxVal=" << maxVal << endl;
	cout << "maxLoc=" << maxLoc << endl;*/

	//0418
	/*float dataA[] = { 1,2,3,4,5,6 };

	Mat A(2, 3, CV_32F, dataA);
	cout << "A=" << A << endl;

	Mat dst1;
	reduce(A, dst1, 0, CV_REDUCE_SUM);
	cout << "dst1=" << dst1 << endl;

	Mat dst2;
	reduce(A, dst2, 1, CV_REDUCE_SUM);
	cout << "dst2 ="<< dst2 << endl;

	Mat dst3;
	reduce(A, dst3, 0, CV_REDUCE_AVG);
	cout << "dst3=" << dst3 << endl;

	Mat dst4;
	reduce(A, dst4, 1, CV_REDUCE_AVG);
	cout << "dst4=" << dst4 << endl;

	Mat dst5;
	reduce(A, dst5, 0, CV_REDUCE_MIN);
	cout << "dst5=" << dst5 << endl;

	Mat dst6;
	reduce(A, dst6, 1, CV_REDUCE_MIN);
	cout << "dst6=" << dst6 << endl;

	Mat dst7;
	reduce(A, dst7, 0, CV_REDUCE_MAX);
	cout << "dst7=" << dst7 << endl;

	Mat dst8;
	reduce(A, dst8, 1, CV_REDUCE_MAX);
	cout << "dst8=" << dst8 << endl;*/

	//0419
	/*float dataA[] = { 6,7,9,8,2,1,4,3 };

	Mat A(2, 3, CV_32F, dataA);
	cout << "A=" << A << endl;

	Mat dst1;
	cv::sort(A, dst1, SORT_EVERY_ROW + SORT_ASCENDING);
	cout << "dst1=" << dst1 << endl;

	Mat dst2;
	cv::sortIdx(A, dst2, SORT_EVERY_ROW + SORT_ASCENDING);
	cout << "dst2=" << dst2 << endl;

	Mat dst3;
	cv::sort(A, dst3, SORT_EVERY_ROW + SORT_DESCENDING);
	cout << "dst3=" << dst3 << endl;

	Mat dst4;
	cv::sortIdx(A, dst4, SORT_EVERY_ROW + SORT_DESCENDING);
	cout << "dst4=" << dst4 << endl;

	Mat dst5;
	cv::sort(A, dst5, SORT_EVERY_COLUMN + SORT_ASCENDING);
	cout << "dst5=" << dst5 << endl;

	Mat dst6;
	cv::sortIdx(A, dst6, SORT_EVERY_COLUMN + SORT_ASCENDING);
	cout << "dst6=" << dst6 << endl;

	Mat dst7;
	cv::sort(A, dst7, SORT_EVERY_COLUMN + SORT_DESCENDING);
	cout << "dst7=" << dst7 << endl;

	Mat dst8;
	cv::sortIdx(A, dst8, SORT_EVERY_COLUMN + SORT_DESCENDING);
	cout << "dst8=" << dst8 << endl;*/

	//0420
	/*float dataA[] = { 1,2,3,4,5,6,7,8 };
	Mat A(2, 4, CV_32F, dataA);
	cout << "A=" << A << endl;

	Mat dst1 = A.clone();
	randShuffle(dst1);
	cout << "dst1=" << dst1 << endl;

	Mat dst2=A.clone();
	randShuffle(dst2, 10);
	cout << "dst2=" << dst2 << endl;*/

	//0421
	/*Mat A1(3, 3, CV_32F);
	setIdentity(A1);
	cout << "A1=" << A1 << endl;

	Mat A2(3, 3, CV_32F);
	setIdentity(A2, 5);
	cout << "A2=" << A2 << endl;

	Mat A3 = Mat::eye(3, 3, CV_32F) * 5;
	cout << "A3=" << A3 << endl;

	float dataB[] = { 1,2,3,4,5,6,7,8,9 };
	Mat B(3, 3, CV_32F, dataB);
	cout << "B=" << B << endl;

	Mat B1 = B.clone();
	completeSymm(B1);
	cout << "B1=" << B1 << endl;

	Mat B2 = B.clone();
	completeSymm(B2, true);
	cout << "B2=" << B2 << endl;*/

	//0422
	/*float dataA[] = { -1,-2,-3,4,5,6 };
	float dataB[] = { 1,2,3,4,5,6 };
	Mat A(2, 3, CV_32F, dataA);
	Mat B(2, 3, CV_32F, dataB);
	cout << "A=" << A << endl;
	cout << "B=" << B << endl;

	double aNormL2 = norm(A);
	double aNormL1 = norm(A, NORM_L1);
	double aNormInf = norm(A, NORM_INF);
	cout << "aNormL2=" << aNormL2 << endl;
	cout << "aNormL1=" << aNormL1 << endl;
	cout << "aNormInf=" << aNormInf << endl;

	double bNormL2 = norm(B);
	double bNormL1 = norm(B, NORM_L1);
	double bNormInf = norm(B, NORM_INF);
	cout << "bNormL2=" << bNormL2 << endl;
	cout << "bNormL1=" << bNormL1 << endl;
	cout << "bNormInf=" << bNormInf << endl;

	double abNormL2 = norm(A,B);
	double abNormL1 = norm(A,B, NORM_L1);
	double abNormInf = norm(A,B, NORM_INF);
	cout << "abNormL2=" << abNormL2 << endl;
	cout << "abNormL1=" << abNormL1 << endl;
	cout << "abNormInf=" << abNormInf << endl;

	double rNormL2 = norm(A, B,NORM_L2+NORM_RELATIVE);
	double rNormL1 = norm(A, B, NORM_L1+ NORM_RELATIVE);
	double rNormInf = norm(A, B, NORM_INF + NORM_RELATIVE);
	cout << "rNormL2=" << rNormL2 << endl;
	cout << "rNormL1=" << rNormL1 << endl;
	cout << "rNormInf=" << rNormInf << endl;

	Mat dst1;
	normalize(A, dst1);
	cout << "dst1=" << dst1 << endl;
	double dstNorm1 = norm(dst1);
	cout << "dstNorm1=" << dstNorm1 << endl;

	Mat dst2;
	normalize(A, dst2, 1.0, 2.0, NORM_MINMAX);
	cout << "dst2=" << dst2 << endl;*/

	//0423
	/*float dataA[] = { 2,-1,-1,1 };
	float dataB[] = { 1,1,1,2 };

	Mat A(2, 2, CV_32F, dataA);
	Mat B(2, 2, CV_32F, dataB);
	cout << "A=" << A << endl;
	cout << "B=" << B << endl;

	Mat dst1;
	gemm(A, B, 1.0, noArray(), 0, dst1);
	cout << "dst1=" << dst1 << endl;

	Mat dst2;
	Mat C = Mat::eye(2, 2, CV_32F);
	gemm(A, B
, 2.0, C, 3, dst2);
	cout << "dst2=" << dst2 << endl;

	Mat dst3 = 2 * A*B + 3 * C;
	cout << "dst3=" << dst3 << endl;*/

	//0424
	/*Point3f arrP[] = {Point3f(100,200,1), Point3f(400,200,1), Point3f(400,300,1),Point3f(100,300,1)};
	Point3f arrQ[4];
	Mat P(1, 4, CV_32FC3, arrP);
	Mat Q(1, 4, CV_32FC3, arrQ);
	cout << "P=" << P << endl;
	cout << "P.size()=" << P.size() << endl;
	cout << "P.channels()=" << P.channels() << endl;

	float theta = RADIAN(30.0f);
	float c = cos(theta);
	float s = sin(theta);
	float cx = 250.0f;
	float cy = 250.0f;
	float dataM[9] = { c,-s,-cx * c + cy * s + cx,
					s,c,-cx * s - cy * c + cy,
					0,0,1 };
	Mat M(3, 3, CV_32F, dataM);
	cout << "M=" << M << endl;

	transform(P, Q, M);
	cout << "Q=" << Q << endl;
	cout << "Q.size()=" << Q.size() << endl;
	cout << "Q.channels()=" << Q.channels() << endl;

	Mat dstImage(512, 512, CV_8UC3, Scalar(255, 255, 255));
	Size size = dstImage.size();
	circle(dstImage, Point((int)cx, (int)FLIP_Y(cy)), 5, Scalar(0, 0, 255));

	line(dstImage, Point((int)cx, (int)FLIP_Y(cy) - 200), Point((int)cx, (int)FLIP_Y(cy) + 200), Scalar(0,0,0));

	line(dstImage, Point((int)cx - 200, (int)FLIP_Y(cy)), Point((int)cx + 200, (int)FLIP_Y(cy)), Scalar(0, 0, 0));

	int fontFace = CV_FONT_HERSHEY_SIMPLEX;
	putText(dstImage, "x'", Point(size.width - 50, size.height / 2), fontFace, 1, Scalar(0, 0, 0));
	putText(dstImage, "y'", Point(size.width/2, 50), fontFace, 1, Scalar(0, 0, 0));

	line(dstImage, Point(0, 0), Point(0, size.height - 1), Scalar(0, 0, 0), 2);
	line(dstImage, Point(0, size.height - 1), Point(size.width - 1, size.height - 1), Scalar(0, 0, 0), 2);
	putText(dstImage, "X", Point(size.width-50, size.height-50), fontFace, 1, Scalar(0, 0, 0));
	putText(dstImage, "Y", Point(30, 50), fontFace, 1, Scalar(0, 0, 0));
	putText(dstImage, "(0,0)", Point(10, size.height-10), fontFace, 1, Scalar(0, 0, 0));

	int i2;
	Point p1, p2;
	for (int i = 0; i < 4; i++) {
		i2 = (i + 1) % 4;
		p1 = Point(cvRound(arrP[i].x), FLIP_Y(cvRound(arrP[i].y)));
		p2 = Point(cvRound(arrP[i2].x), FLIP_Y(cvRound(arrP[i2].y)));
		line(dstImage, p1, p2, Scalar(0, 0, 255));

		p1 = Point(cvRound(arrQ[i].x), FLIP_Y(cvRound(arrQ[i].y)));
		p2 = Point(cvRound(arrQ[i2].x), FLIP_Y(cvRound(arrQ[i2].y)));
		line(dstImage, p1, p2, Scalar(0, 0, 255));

	}
	imshow("d", dstImage);
	waitKey();*/

	//0425
	/*Scalar ex(100, 200);
	cout << ex << endl << endl;

	float dataM1[] = { 1,0,0,
						0,1,0,
						0,0,2 };
	Mat M1(3, 3, CV_32F, dataM1);
	cout << "M1=" << M1 << endl;

	Point arr1 = Point(200, 100);
	Mat A1(1, 1, CV_32FC2, Scalar(arr1.x, arr1.y));
	cout << "A1=" << A1 << endl;

	Mat dst1;
	perspectiveTransform(A1, dst1, M1);
	cout << "dst1=" << dst1 << endl;

	Point3f arr2 = Point3f(200, 100, 1);
	Mat M2 = Mat::eye(4, 4, CV_32F);
	M2.at<float>(3, 3) = 2;
	cout << "M2=" << M2 << endl;

	Mat A2(1, 1, CV_32FC3, Scalar(arr2.x, arr2.y, arr2.z));
	cout << "A2=" << A2 << endl;

	Mat dst2;
	perspectiveTransform(A2, dst2, M2);
	cout << "dst2=" << dst2 << endl;*/

	//0426
	/*float dataX[] = { 0,0,0,
					1,0,0,
					1,1,0,
					1,0,1 };
	Mat X(4, 3, CV_32F, dataX);
	cout << "X=" << X << endl;

	Mat mX;
	reduce(X, mX, 0, CV_REDUCE_AVG);
	cout << "mX=" << mX << endl;

	Mat Cx;
	mulTransposed(X, Cx, true, mX, 1.0 / X.rows);
	cout << "Cx=" << Cx << endl;

	float data[] = {-0.75,-0.25,-0.25,
					0.25,-0.25,-0.25,
					0.25,0.75,-0.25,
					0.25,-0.25,0.75};

	Mat sub(4, 3, CV_32F, data);
	Mat transSub;
	
	transpose(sub, transSub);
	
	Mat dst3;
	dst3 = transSub * sub *1 / 4;
	cout << endl << "sub=" << sub << endl;
	cout << "transSub=" << transSub << endl;
	cout << "mul=" << dst3 << endl;*/

	//0427
	/*float dataA[] = { -2, 2, -3,
					-1, 1, 3,
					2, 0, -1 };
	Mat A(3, 3, CV_32F, dataA);
	cout << "A=" << A << endl;
	cout << "trace(A)=" << trace(A) << endl;

	Mat tA;
	transpose(A, tA);
	cout << "tA=" << tA << endl;

	double det = determinant(A);
	cout << "det(A)=" << det << endl;*/

	//0428
	/*float dataA[] = {2,-1,1,3,3,9,3,3,5};

	Mat A(3, 3, CV_32F, dataA);
	cout << "A=" << A << endl;

	Mat invLU;
	double dRet1 = invert(A, invLU);
	cout << "invLU=" << invLU << endl;
	cout << "dRet1=" << dRet1 << endl;;
	cout << "A*invLU=" << A * invLU << endl;

	Mat invSVD;
	double dRet2 = invert(A, invSVD,DECOMP_SVD);
	cout << "invSVD=" << invSVD << endl;
	cout << "dRet2=" << dRet2 << endl;;
	cout << "A*invSVD=" << A * invSVD << endl;

	Mat invCHO;
	double dRet3 = invert(A, invCHO, DECOMP_CHOLESKY);
	cout << "invCHO=" << invCHO << endl;
	cout << "dRet3=" << dRet3 << endl;;
	cout << "A*invCHO=" << A * invCHO << endl;

	float dataB[] = { -1, 0, 4 };

	Mat B(3, 1, CV_32F, dataB);
	cout << "B=" << B << endl;

	Mat X1 = invLU * B;
	cout << "X1=" << X1 << endl;

	Mat X2 = invSVD * B;
	cout << "X2=" << X2 << endl;

	Mat X3 = invCHO * B;
	cout << "X3=" << X3 << endl;*/

	//0429
	/*float dataA[] = { 2,-1,1,3,3,9,3,3,5 };

	Mat A(3, 3, CV_32F, dataA);
	cout << "A=" << A << endl;

	float dataB[] = {-1,0,4};
	Mat B(3, 1, CV_32F, dataB);
	cout << "B=" << B << endl;

	Mat X1;
	solve(A, B, X1);
	cout << "X1=" << X1 << endl;

	Mat X2;
	solve(A, B, X2, DECOMP_SVD);
	cout << "X2=" << X2 << endl;

	Mat X3;
	solve(A, B, X3, DECOMP_CHOLESKY);
	cout << "X3=" << X3 << endl;

	Mat X4;
	solve(A, B, X4, DECOMP_EIG);
	cout << "X4=" << X4 << endl;

	Mat X5;
	solve(A, B, X5, DECOMP_QR);
	cout << "X5=" << X5 << endl;*/

	//0430
	/*float dataA[] = {1,0,-1,0,1,0,-1,0,1};
	Mat A(3, 3, CV_32F, dataA);
	cout << "A=" << A << endl;

	Mat eigenvalues;
	eigen(A, eigenvalues);
	cout << "eigenvalues=" << eigenvalues << endl;

	Mat eigenvectors;
	eigen(A, eigenvalues, eigenvectors);
	cout << "eigenvalues=" << eigenvalues << endl;
	cout << "eigenvectors=" << eigenvectors << endl;*/

	//0431
	/*float dataX[] = {0,0,0,1,0,0,1,1,0,1,0,1};
	Mat X(4, 3, CV_32F, dataX);
	cout << "X=" << X << endl;

	Mat covar, mean;
	calcCovarMatrix(X, covar, mean, COVAR_NORMAL + COVAR_ROWS + COVAR_SCALE);
	cout << "mean=" << mean << endl;
	cout << "covar=" << covar << endl << endl;

	Mat Y[4];
	for (int i = 0; i < X.rows; i++)
		Y[i] = X.row(i);
	Mat covar2, mean2;
	calcCovarMatrix(Y, X.rows, covar2, mean2, COVAR_NORMAL + COVAR_ROWS + COVAR_SCALE);
	cout << "mean2=" << mean2 << endl;
	cout << "covar2=" << covar2 << endl;*/

	//0432
	/*float dataX[] = { 0,1,1,1,
		    		0,0,1,0,
					0,0,0,1 };
	Mat X(3, 4, CV_32F, dataX);
	cout << "X=" << X << endl;

	Mat covar, mean;
	calcCovarMatrix(X, covar, mean, COVAR_NORMAL + COVAR_COLS + COVAR_SCALE);
	cout << "mean=" << mean << endl;
	cout << "covar=" << covar << endl << endl;

	Mat Y[4];
	for (int i = 0; i < X.cols; i++)
		Y[i] = X.col(i);
	Mat covar2, mean2;
	calcCovarMatrix(Y, X.cols, covar2, mean2, COVAR_NORMAL + COVAR_COLS + COVAR_SCALE);
	cout << "mean2=" << mean2 << endl;
	cout << "covar2=" << covar2 << endl;*/

	//0433
	/*double dataX[] = { 10,0,1,
					1,10,0,
					10,10,0,
					1,0,10,
					0,1,1 };
	Mat X(5, 3, CV_64F, dataX);
	cout << "X=" << X << endl;

	Mat cX, mX;
	calcCovarMatrix(X, cX, mX, COVAR_NORMAL + COVAR_COLS);
	cout << "mX=" << mX << endl;
	cout << "cX=" << cX << endl;

	Mat eVals;
	Mat eVects;
	eigen(cX, eVals, eVects);
	cout << "eVals=\n" << eVals << endl;
	cout << "eVects=\n" << eVects << endl <<endl;

	Mat cX2, mX2;
	calcCovarMatrix(X, cX2, mX2, COVAR_SCRAMBLED + COVAR_COLS);
	cout << "mX2=" << mX2 << endl;
	cout << "cX2=" << cX2 << endl <<endl;

	Mat eVals2;
	Mat eVects2;
	eigen(cX2, eVals2, eVects2);
	cout << "eVals2=" << eVals2 << endl;
	cout << "eVects2=" << eVects2 << endl<<endl;

	Mat A(X.rows, X.cols, CV_64F);
	for (int i = 0; i < A.cols; i++)
		A.col(i) = X.col(i) - mX;
	Mat eVects3 = A * eVects2.t();

	Mat a;
	for (int i = 0; i < eVects3.cols; i++) {
		a = eVects3.col(i);
		normalize(a, a);
	}
	cout << "eVects3.t()=" << eVects3.t() << endl;*/

	//0434
	/*double dataX[] = { 10,0,1,
					1,10,0,
					10,10,0,
					1,0,10,
					0,1,1 };
	Mat X(5, 3, CV_64F, dataX);
	cout << "X=" << X << endl;

	Mat mX;
	reduce(X, mX, 1, CV_REDUCE_AVG);
	cout << "mX=" << mX << endl;

	Mat A(X.rows, X.cols, CV_64F);
	for (int i = 0; i < A.cols; i++)
		A.col(i) = X.col(i)-mX;
	Mat cX = A * A.t();
	cout << "cX=" << cX << endl << endl;

	Mat eVals;
	Mat eVects;
	eigen(cX, eVals, eVects);
	cout << "eVals=\n" << eVals << endl;
	cout << "eVects=\n" << eVects << endl<<endl;

	Mat cX2 = A.t()*A;
	cout << "cX2=" << cX2 << endl << endl;

	Mat eVals2, eVects2;
	eigen(cX2, eVals2, eVects2);
	cout << "eVals2=" << eVals2 << endl;
	cout << "eVects2=" << eVects2 << endl << endl;

	Mat A2(X.rows, X.cols, CV_64F);
	for (int i = 0; i < A.cols; i++)
		A2.col(i) = A.col(i) - mX;
	Mat eVects3 = A * eVects2.t();

	Mat a;
	for (int i = 0; i < eVects3.cols; i++)
	{
		a = eVects3.col(i);
		normalize(a, a);
	}
	cout << "eVects3.t()=" << eVects3.t() << endl;*/

	//0435
	/*double dataX[] = { 0,0,0,100,100,150,-100,-150,
						0,50,-50,0,30,100,-20,-100 };
	Mat X(2, 8, CV_64F, dataX);
	cout << "X=" << X << endl;

	Mat cX, mX;
	calcCovarMatrix(X, cX, mX, COVAR_NORMAL + COVAR_COLS);
	cout << "mX=" << mX << endl;
	cout << "cX=" << cX << endl << endl;

	Mat invCx;
	invert(cX, invCx);
	cout << "invCx=" << invCx << endl << endl;
	Mat vec1 = (Mat_<double>(2, 1) << 0, 50);
	Mat vec2 = (Mat_<double>(2, 1) << 1, 100);

	double fDistance = Mahalanobis(vec1, vec2, invCx);
	cout << "fDistance=" << fDistance << endl;

	Mat dstImage(512, 512, CV_8UC3, Scalar::all(255));
	Point ptCenter(dstImage.cols / 2, dstImage.rows / 2);

	int x, y;
	for(y=0; y<dstImage.cols; y++)
		for (x = 0; x < dstImage.rows; x++) {
			vec2.at<double>(0, 0) = x - ptCenter.x;
			vec2.at<double>(1, 0) = y - ptCenter.y;
			fDistance = Mahalanobis(mX, vec2, invCx);
			
			if (fDistance < 0.1)
				dstImage.at<Vec3b>(FLIP_Y(y), x) = Vec3b(50, 50, 50);
			else if (fDistance < 0.3)
				dstImage.at<Vec3b>(FLIP_Y(y), x) = Vec3b(100, 100, 100);
			else if (fDistance < 0.8)
				dstImage.at<Vec3b>(FLIP_Y(y), x) = Vec3b(200, 200, 200);
			else
				dstImage.at<Vec3b>(FLIP_Y(y), x) = Vec3b(255,255,255);
		}

	Point pt;
	for (x = 0; x < X.cols; x++) {
		pt.x = X.at<double>(0, x) + ptCenter.x;
		pt.y = X.at<double>(1, x) + ptCenter.y;
		pt.y = FLIP_Y(pt.y);
		circle(dstImage, pt, 3, Scalar(0, 0, 255), 3);
	}

	Point pt1, pt2;
	pt1 = Point(0, ptCenter.y);
	pt2 = Point(dstImage.cols - 1, ptCenter.y);
	line(dstImage, pt1, pt2, Scalar(0, 0, 0));

	pt1 = Point(ptCenter.x, 0);
	pt2 = Point(ptCenter.x, dstImage.rows - 1);
	line(dstImage, pt1, pt2, Scalar(0, 0, 0));

	Mat eVals, eVects;
	eigen(cX, eVals, eVects);
	cout << "eVals=" << eVals << endl;
	cout << "eVects=" << eVects << endl << endl;

	double scale = sqrt(eVals.at<double>(0, 0));
	double x1, x2, y1, y2;
	x1 = scale * eVects.at<double>(0, 0);
	y1 = scale * eVects.at<double>(0, 1);
	x2 = -x1;
	y2 = -y1;

	x1 += mX.at<double>(0, 0) + ptCenter.x;
	y1 += mX.at<double>(1, 0) + ptCenter.y;
	x2 += mX.at<double>(0, 0) + ptCenter.x;
	y2 += mX.at<double>(1, 0) + ptCenter.y;

	pt1 = Point(cvRound(x1), FLIP_Y(cvRound(y1)));
	pt2 = Point(cvRound(x2), FLIP_Y(cvRound(y2)));
	line(dstImage, pt1, pt2, Scalar(255, 0, 0), 2);

	scale = sqrt(eVals.at<double>(1, 0));
	x1 = scale * eVects.at<double>(1, 0);
	y1 = scale * eVects.at<double>(1, 1);
	x2 = -x1;
	y2 = -y1;

	x1 += mX.at<double>(0, 0) + ptCenter.x;
	y1 += mX.at<double>(1, 0) + ptCenter.y;
	x2 += mX.at<double>(0, 0) + ptCenter.x;
	y2 += mX.at<double>(1, 0) + ptCenter.y;

	pt1 = Point(cvRound(x1), FLIP_Y(cvRound(y1)));
	pt2 = Point(cvRound(x2), FLIP_Y(cvRound(y2)));
	line(dstImage, pt1, pt2, Scalar(255, 0, 0), 2);
	imshow("d", dstImage);
	waitKey();*/

	//RNG 함수
	//0436
	/*Mat dstImage(512, 512, CV_8UC3, Scalar::all(255));

	int nPoints = 100;
	Mat randPoints(1, nPoints, CV_32SC2);
	theRNG().state = time(NULL);
	randu(randPoints, Scalar::all(0), Scalar(dstImage.cols, dstImage.rows));
	for (int x = 0; x < randPoints.cols; x++) {
		Point pt = randPoints.at<Point>(0, x);
		circle(dstImage, pt, 3, Scalar(0, 0, 0));
	}
	imshow("d", dstImage);
	waitKey();*/

	//0437
	/*Mat dstImage(512, 512, CV_8UC3, Scalar::all(255));

	int nPoints = 100;
	Mat randPoints(1, nPoints, CV_32SC2);
	theRNG().state = time(NULL);
	Scalar mean = Scalar(256, 256);
	Scalar stddev = Scalar(50, 50);
	randn(randPoints, mean,stddev);
	for (int x = 0; x < randPoints.cols; x++) {
		Point pt = randPoints.at<Point>(0, x);
		circle(dstImage, pt, 3, Scalar(0, 0, 0));
	}
	circle(dstImage, Point(mean.val[0], mean.val[1]), 3, Scalar(0, 0, 255), 3);
	imshow("d", dstImage);
	waitKey();*/

	//0438 0439
	/*Mat dstImage(512, 512, CV_8UC3, Scalar::all(255));

	int nPoints = 100;
	Mat randPoints(1, nPoints, CV_32SC2);

	RNG& rng = theRNG();
	rng.state = time(NULL);

	//Scalar a = Scalar::all(0);
	//Scalar b = Scalar(dstImage.cols, dstImage.rows);
	//rng.fill(randPoints, RNG::UNIFORM, a, b);

	Scalar mean = Scalar(256, 256);
	Scalar stddev = Scalar(50, 50);
	rng.fill(randPoints, RNG::NORMAL, mean, stddev);

	for (int x = 0; x < randPoints.cols; x++) {
		Point pt = randPoints.at<Point>(0, x);
		circle(dstImage, pt, 3, Scalar(0, 0, 0));
	}
	circle(dstImage, Point(mean.val[0], mean.val[1]), 3, Scalar(0, 0, 255), 3);
	imshow("d", dstImage);
	waitKey();*/

	//0440
	/*double dataA[] = { 1,0,0,0,2,
						0,0,3,0,0,
						0,0,0,0,0,
						0,4,0,0,0 };
	Mat A(4, 5, CV_64F, dataA);
	cout << "A=" << A << endl;

	Mat A1 = A.clone();
	SVD svd(A1, SVD::MODIFY_A + SVD::FULL_UV);
	cout << "svd.u=" << svd.u << endl;
	cout << "svd.w=" << svd.w << endl;
	cout << "svd.vt=" << svd.vt << endl;

	Mat W = Mat::zeros(A.size(), A.type());
	for (int i = 0; i < svd.w.rows; i++)
		W.at<double>(i, i) = svd.w.at<double>(i, 0);
	cout << "W=" << W << endl;

	Mat A2 = svd.u*W*svd.vt;
	cout << "A2=" << A2 << endl;*/

	//0441
	/*double dataA[] = { 2,-1,1,3,3,9,3,3,5 };
	Mat A(3, 3, CV_64F, dataA);
	cout << "A=" << A << endl;

	Mat B = (Mat_<double>(3, 1) << -1, 0, 4);
	cout << "B=" << B << endl;

	SVD svd(A, SVD::MODIFY_A + SVD::FULL_UV);
	cout << "svd.u=" << svd.u << endl;
	cout << "svd.w=" << svd.w << endl;
	cout << "svd.vt=" << svd.vt << endl;

	Mat X;
	svd.backSubst(B, X);
	cout << "X=" << X << endl;*/

	//0442
	/*double dataX[] = { 0,0,0,100,100,150,-100,-150,
						0,50,-50,0,30,100,-20,-100 };
	Mat X(2, 8, CV_64F, dataX);
	cout << "X=" << X << endl;

	Mat cX, mX;
	calcCovarMatrix(X, cX, mX, COVAR_NORMAL + COVAR_COLS);
	cout << "mX=" << mX << endl;
	cout << "cX=" << cX << endl<<endl;

	Mat eValsX;
	Mat eVectsX;
	eigen(cX, eValsX, eVectsX);
	cout << "eValsX=" << eValsX << endl;
	cout << "eVectsX=" << eVectsX << endl << endl;

	Mat X1 = X.clone();
	for (int x = 0; x < X1.cols; x++)
		X1.col(x) = X1.col(x) - mX;
	Mat A = eVectsX.clone();
	Mat Y = A * X1;
	cout << "Y=" << Y << endl;

	Mat X2 = A.t() * Y;
	for (int x = 0; x < X2.cols; x++)
		X2.col(x) = X2.col(x) + mX;
	cout << "X2=" << X2 << endl;

	Mat cY, mY;
	calcCovarMatrix(Y, cY, mY, COVAR_NORMAL + COVAR_COLS);
	cout << "mY=" << mY << endl;
	cout << "cY=" << cY << endl;

	Mat eValsY;
	Mat eVectsY;
	eigen(cY, eValsY, eVectsY);
	cout << "eValsY=" << eValsY << endl;
	cout << "eVectsY=" << eVectsY << endl << endl;

	Mat invCx;
	invert(cX, invCx);
	Mat invCy;
	invert(cY, invCy);

	Mat dstImage(512, 512, CV_8UC3, Scalar::all(255));
	Point ptCenter(dstImage.cols / 2, dstImage.rows / 2);

	int x, y;
	Mat vec2(2, 1, CV_64F);
	double fDistance1, fDistance2;
	for(y=0;y<dstImage.rows;y++)
		for (x = 0; x < dstImage.cols; x++) {
			vec2.at<double>(0, 0) = x - ptCenter.x;
			vec2.at<double>(1, 0) = y - ptCenter.y;
			fDistance1 = Mahalanobis(mX, vec2, invCx);
			if (0.7 <= fDistance1 && fDistance1 <= 0.8)
				dstImage.at<Vec3b>(FLIP_Y(y), x) = Vec3b(0, 0, 255);

			fDistance2 = Mahalanobis(mY, vec2, invCy);
			if (0.7 <= fDistance2 && fDistance2 <= 0.8)
				dstImage.at<Vec3b>(FLIP_Y(y), x) = Vec3b(255, 0, 0);
		}

	Point pt1, pt2;
	for (x = 0; x < X.cols; x++) {
		pt1.x = X.at<double>(0, x) + ptCenter.x;
		pt1.y = X.at<double>(1, x) + ptCenter.y;
		pt1.y = FLIP_Y(pt1.y);
		circle(dstImage, pt1, 3, Scalar(0, 0, 255), 3);

		pt2.x = Y.at<double>(0, x) + ptCenter.x;
		pt2.y = Y.at<double>(1, x) + ptCenter.y;
		pt2.y = FLIP_Y(pt2.y);
		circle(dstImage, pt2, 3, Scalar(255, 0, 0), 3);
	}

	pt1.x = cvRound(mX.at<double>(0, 0)) + ptCenter.x;
	pt1.y = cvRound(mX.at<double>(1, 0)) + ptCenter.y;
	pt1.y = FLIP_Y(pt1.y);
	circle(dstImage, pt1, 3, Scalar(255, 0, 255), 3);

	pt2.x = cvRound(mX.at<double>(0, 0)) + ptCenter.x;
	pt2.y = cvRound(mX.at<double>(1, 0)) + ptCenter.y;
	pt2.y = FLIP_Y(pt2.y);
	circle(dstImage, pt2, 3, Scalar(0, 0, 0), 3);

	pt1 = Point(0, ptCenter.y);
	pt2 = Point(dstImage.cols - 1, ptCenter.y);
	line(dstImage, pt1, pt2, Scalar(0, 0, 0), 2);

	pt1 = Point(ptCenter.x,0);
	pt2 = Point(ptCenter.x, dstImage.rows - 1);
	line(dstImage, pt1, pt2, Scalar(0, 0, 0), 2);


	double scale = sqrt(eValsX.at<double>(0, 0));
	double x1, x2, y1, y2;
	x1 = scale * eVectsX.at<double>(0, 0);
	y1 = scale * eVectsX.at<double>(0, 1);
	x2 = -x1;
	y2 = -y1;

	x1 += mX.at<double>(0, 0) + ptCenter.x;
	y1 += mX.at<double>(1, 0) + ptCenter.y;
	x2 += mX.at<double>(0, 0) + ptCenter.x;
	y2 += mX.at<double>(1, 0) + ptCenter.y;
	
	pt1 = Point(cvRound(x1), FLIP_Y(cvRound(y1)));
	pt2 = Point(cvRound(x2), FLIP_Y(cvRound(y2)));
	line(dstImage, pt1, pt2, Scalar(0, 0, 255), 2);

	//
	scale = sqrt(eValsX.at<double>(1, 0));
	x1 = scale * eVectsX.at<double>(1, 0);
	y1 = scale * eVectsX.at<double>(1, 1);
	x2 = -x1;
	y2 = -y1;


	x1 += mX.at<double>(0, 0) + ptCenter.x;
	y1 += mX.at<double>(1, 0) + ptCenter.y;
	x2 += mX.at<double>(0, 0) + ptCenter.x;
	y2 += mX.at<double>(1, 0) + ptCenter.y;

	pt1 = Point(cvRound(x1), FLIP_Y(cvRound(y1)));
	pt2 = Point(cvRound(x2), FLIP_Y(cvRound(y2)));
	line(dstImage, pt1, pt2, Scalar(0, 255, 0), 2);
	
	imshow("d", dstImage);
	waitKey();*/

	//0443
	/*double dataX[] = { 0,0,0,100,100,150,-100,-150,
					0,50,-50,0,30,100,-20,-100 };
Mat X(2, 8, CV_64F, dataX);
cout << "X=" << X << endl;

Mat mX;
reduce(X, mX, 1, CV_REDUCE_AVG);
cout << "mX=" << mX << endl;

PCA pca(X, mX, CV_PCA_DATA_AS_COL);
Mat Y;
pca.project(X, Y);
cout << "Y=" << Y << endl;
Mat mY;
reduce(Y, mY, 1, CV_REDUCE_AVG);
cout << "mY=" << mY << endl;

Mat X2;
pca.backProject(Y, X2);
cout << "X2=" << X2<<endl;
cout << "pca.mean=" << pca.mean << endl;
cout << "pca.eigenvalues=" << pca.eigenvalues << endl;
cout << "pca.eigenvectors=" << pca.eigenvectors << endl;

Mat dstImage(512, 512, CV_8UC3, Scalar::all(255));
Point ptCenter(dstImage.cols / 2, dstImage.rows / 2);

Point pt1, pt2;
for (int x = 0; x < X.cols; x++) {
	pt1.x = X.at<double>(0, x) + ptCenter.x;
	pt1.y = X.at<double>(1, x) + ptCenter.y;
	pt1.y = FLIP_Y(pt1.y);
	circle(dstImage, pt1, 3, Scalar(0, 0, 255), 3);

	pt2.x = Y.at<double>(0, x) + ptCenter.x;
	pt2.y = Y.at<double>(1, x) + ptCenter.y;
	pt2.y = FLIP_Y(pt2.y);
	circle(dstImage, pt2, 3, Scalar(255, 0, 0), 3);
}

pt1.x = cvRound(mX.at<double>(0, 0)) + ptCenter.x;
pt1.y = cvRound(mX.at<double>(1, 0)) + ptCenter.y;
pt1.y = FLIP_Y(pt1.y);
circle(dstImage, pt1, 3, Scalar(255, 0, 255), 3);

pt2.x = cvRound(mX.at<double>(0, 0)) + ptCenter.x;
pt2.y = cvRound(mX.at<double>(1, 0)) + ptCenter.y;
pt2.y = FLIP_Y(pt2.y);
circle(dstImage, pt2, 3, Scalar(0, 0, 0), 3);

pt1 = Point(0, ptCenter.y);
pt2 = Point(dstImage.cols - 1, ptCenter.y);
line(dstImage, pt1, pt2, Scalar(0, 0, 0));

pt1 = Point(ptCenter.x, 0);
pt2 = Point(ptCenter.x, dstImage.rows - 1);
line(dstImage, pt1, pt2, Scalar(0, 0, 0));

double scale = sqrt(pca.eigenvalues.at<double>(0,0)*X.cols);
double x1, x2, y1, y2;
x1 = scale * pca.eigenvectors.at<double>(0, 0);
y1 = scale * pca.eigenvectors.at<double>(0, 1);
x2 = -x1;
y2 = -y1;

x1 += mX.at<double>(0, 0) + ptCenter.x;
y1 += mX.at<double>(1, 0) + ptCenter.y;
x2 += mX.at<double>(0, 0) + ptCenter.x;
y2 += mX.at<double>(1, 0) + ptCenter.y;

pt1 = Point(cvRound(x1), FLIP_Y(cvRound(y1)));
pt2 = Point(cvRound(x2), FLIP_Y(cvRound(y2)));
line(dstImage, pt1, pt2, Scalar(0, 0, 255), 2);

//
scale = sqrt(pca.eigenvalues.at<double>(1, 0)*X.cols);
x1 = scale * pca.eigenvectors.at<double>(1, 0);
y1 = scale * pca.eigenvectors.at<double>(1, 1);
x2 = -x1;
y2 = -y1;


x1 += mX.at<double>(0, 0) + ptCenter.x;
y1 += mX.at<double>(1, 0) + ptCenter.y;
x2 += mX.at<double>(0, 0) + ptCenter.x;
y2 += mX.at<double>(1, 0) + ptCenter.y;

pt1 = Point(cvRound(x1), FLIP_Y(cvRound(y1)));
pt2 = Point(cvRound(x2), FLIP_Y(cvRound(y2)));
line(dstImage, pt1, pt2, Scalar(0, 255, 0), 2);

imshow("d", dstImage);
waitKey();*/

	//0444
	Mat srcImage = imread("lena.jpg");
	if (srcImage.empty())
		return -1;
	cout << "srcImage.type()=" << srcImage.type() << endl;
	vector<Mat> bgrPlanes;
	split(srcImage, bgrPlanes);
	imshow("bgrPlanes[0]", bgrPlanes[0]);
	imshow("bgrPlanes[1]", bgrPlanes[1]);
	imshow("bgrPlanes[2]", bgrPlanes[2]);

	Mat X = srcImage.reshape(1, srcImage.rows*srcImage.cols);
	cout << "X.size()=" << X.size() << endl;
	PCA pca(X, noArray(), CV_PCA_DATA_AS_ROW);

	Mat Y;
	pca.project(X, Y);
	cout << "Y.size()=" << Y.size() << endl;

	Mat Y2 = Y.reshape(3, srcImage.rows);
	cout << "Y2.size()=" << Y2.size() << endl;

	vector<Mat> yPlanes;
	split(Y2, yPlanes);
	cout << "yPlanes[0].type()=" << yPlanes[0].type() << endl;

	yPlanes[0].convertTo(yPlanes[0], CV_8U);
	yPlanes[1].convertTo(yPlanes[1], CV_8U);
	yPlanes[2].convertTo(yPlanes[2], CV_8U);
	cout << "yPlanes[0].type()=" << yPlanes[0].type() << endl;

	imshow("0", yPlanes[0]);
	imshow("1", yPlanes[1]);
	imshow("2", yPlanes[2]);
	waitKey();
	return 0;

}