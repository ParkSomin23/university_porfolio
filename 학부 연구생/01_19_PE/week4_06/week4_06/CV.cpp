#include "pch.h"
#include "opencv.hpp"
#include <iomanip>
using namespace cv;
using namespace std;

void ZeroCrossing(Mat &src, Mat& dst, int threshold);
void Printmat(const char*strName, Mat m);

int main()
{
	/*uchar dataA[] = {1,2,4,5,2,1,
					 3,6,6,9,0,3,
					 1,8,3,7,2,5,
					 2,9,8,9,9,1,
					 3,9,8,8,7,2,
					 4,9,9,9,9,3};
	Mat A(6, 6, CV_8U, dataA);
	cout << "A=" << A << endl;*/

	//0601
	/*int border = 2;

	Mat B;
	copyMakeBorder(A, B, border, border, border, border, BORDER_CONSTANT, 0);
	cout << "B=" << B << endl;

	Mat C;
	copyMakeBorder(A, C, border, border, border, border, BORDER_REPLICATE);
	cout << "C=" << C << endl;

	Mat D;
	copyMakeBorder(A, D, border, border, border, border, BORDER_REFLECT);
	cout << "D=" << D << endl;

	Mat E;
	copyMakeBorder(A, E, border, border, border, border, BORDER_REFLECT101);
	cout << "E=" << E << endl;

	Mat F;
	copyMakeBorder(A, F, border, border, border, border, BORDER_WRAP);
	cout << "F=" << F << endl;*/

	//0602
	/*int border = 2;

	Mat B;
	copyMakeBorder(A, B, border, border, border, border, BORDER_REPLICATE);
	cout << "B=" << B << endl;

	cout << endl << A.rows << endl;
	cout << borderInterpolate(4, A.rows, BORDER_REPLICATE)<<endl;

	cout << "borderInterpolate" << endl;
	for (int y = -border; y < A.rows + border; y++) {
		for (int x = -border; x < A.cols + border; x++) {
			float val = A.at<uchar>(borderInterpolate(y, A.rows, BORDER_REPLICATE), borderInterpolate(x, A.cols, BORDER_REPLICATE));
			cout << val << ",";
		}
		cout << endl;
	}*/

	//0603
	/*Mat avgKernel = (Mat_<float>(3, 3) << 1. / 9., 1. / 9., 1. / 9.,
										  1. / 9., 1. / 9., 1. / 9.,
										  1. / 9., 1. / 9., 1. / 9.);
	Point anchor(-1, -1);
	Mat B;
	filter2D(A, B, -1, avgKernel, anchor);
	cout << "B=" << B << endl;

	anchor = Point(1, 1);
	Mat C;
	filter2D(A, C, -1, avgKernel, anchor);
	cout << "C=" << C << endl;

	Point newAnchor = Point(avgKernel.cols - anchor.x - 1, avgKernel.rows - anchor.y - 1);
	Mat D;
	Mat flipKernel;
	flip(avgKernel, flipKernel, -1);
	filter2D(A, D, -1, flipKernel, anchor);
	cout << "D=" << D << endl;*/

	//0604
	/*Mat avgX = (Mat_<float>(1, 3) << 1. / 3., 1. / 3., 1. / 3.);
	Mat avgY = (Mat_<float>(3, 1) << 1. / 3., 1. / 3., 1. / 3.);

	Mat B, C;
	filter2D(A, B, -1, avgX);
	cout << "B=" << B << endl;
	filter2D(B, C, -1, avgY);
	cout << "C=" << C << endl;

	Mat D;
	sepFilter2D(A, D, -1, avgX, avgY);
	cout << "D=" << D << endl;*/

	//0605
	/*Mat srcImage = imread("lena.jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;

	Size ksize(21, 21);
	Mat avgKernel = Mat::ones(ksize, CV_32F);
	avgKernel /= avgKernel.total();
	Mat avgImage;
	filter2D(srcImage, avgImage, -1, avgKernel);
	imshow("1", avgImage);

	Mat avgX = Mat::ones(1, ksize.width, CV_32F);
	Mat avgY = Mat::ones(1, ksize.height, CV_32F);
	avgX /= avgX.total();
	avgY /= avgY.total();

	Mat angImage2;
	sepFilter2D(srcImage, angImage2, -1, avgX, avgY);
	imshow("2", angImage2);*/

	//0605_히스토그램 비교 실패
	/*Mat his1, his2;
	int histSize = 256;
	float valueRange[] = { 0,256 };
	const float *ranges[] = { valueRange };
	int channels = 0;
	int dims = 1;

	calcHist(&avgImage, 1, &channels, Mat(), his1, dims, &histSize, ranges);
	normalize(his1, his1, 1, 0, NORM_L1, CV_32F);
	calcHist(&angImage2, 1, &channels, Mat(), his2, dims, &histSize, ranges);
	normalize(his2, his2, 1, 0, NORM_L1, CV_32F);

	double dis1 = compareHist(avgImage, angImage2, 0);

	cout <<dis1<<endl;
	//cout << compareHist(avgImage, angImage2, 1) << endl;
	//cout <<compareHist(avgImage, angImage2, 2)<<endl;
	//cout<<compareHist(avgImage, angImage2, 3)<<endl;
	*/

	//0606
	/*uchar dataA[] = { 1,2,4,5,2,1,
					 3,6,6,9,0,3,
					 1,8,3,7,2,5,
					 2,9,8,9,9,1,
					 3,9,8,8,7,2,
					4,9,9,9,9,3 };
	Mat A(6, 6, CV_8U, dataA);
	cout << "A=" << A << endl;

	int border = 1;
	Mat B;
	copyMakeBorder(A, B, border, border, border, border, BORDER_REFLECT101);
	cout << "B=" << B << endl;

	Size ksize(border * 2 + 1, border * 2 + 1);
	Point anchor(-1, -1);
	Mat dst1;
	boxFilter(A, dst1, -1, ksize, anchor, false);
	cout << "dst1=" << dst1 << endl;

	Mat dst2;
	boxFilter(A, dst2, -1, ksize, anchor, true);
	cout << "dst2=" << dst2 << endl;

	Mat dst3;
	int d = ksize.width;
	double sigmaColor = 2.0;
	double sigmaSpace = 2.0;
	bilateralFilter(A, dst3, 3, d, sigmaColor, sigmaSpace);
	cout << "dst3=" << dst3 << endl;

	Mat dst4;
	bilateralFilter(A, dst4, 3, -1, sigmaColor, sigmaSpace);
	cout << "dst4=" << dst4 << endl;*/

	//0607
/*	Mat srcImage = imread("lena.jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;
	imshow("s", srcImage);

	int border = 3;
	Size ksize(2 * border + 1, 2 * border + 1);

	Mat dstImage1;
	boxFilter(srcImage, dstImage1, -1, ksize);
	imshow("1", dstImage1);

	Mat dstImage2;
	int d = ksize.width;
	double sigmaColot = 10.0;
	double sigmaSpace = 10.0;
	bilateralFilter(srcImage, dstImage2, d, sigmaColot, sigmaSpace);
	imshow("2", dstImage2);

	Mat dstImage3;
	bilateralFilter(srcImage, dstImage3, -1, sigmaColot, sigmaSpace);
	imshow("3", dstImage3);*/

	/*uchar dataA[] = { 1,2,4,5,2,1,
					 3,6,6,9,0,3,
					 1,8,3,7,2,5,
					 2,9,8,9,9,1,
					 3,9,8,8,7,2,
					4,9,9,9,9,3 };
	Mat A(6, 6, CV_8U, dataA);
	cout << "A=" << A << endl;*/

	//0608
	/*int border = 1;
	Mat B;
	copyMakeBorder(A, B, border, border, border, border, BORDER_REPLICATE);
	cout << "B=" << B << endl;
	int kSize = border * 2 + 1;
	Mat dst1;
	medianBlur(A, dst1, kSize);
	cout << "dst1=" << dst1 << endl;

	Mat dst2;
	blur(A, dst2, Size(kSize,kSize));
	cout << "dst2=" << dst2 << endl;*/

	//0609
	/*int kSize = 3;
	double sigma = 0.0;
	Mat kx = getGaussianKernel(kSize, sigma);
	cout << "kx=" << kx << endl;

	Mat ky = getGaussianKernel(kSize, sigma);
	cout << "ky=" << ky << endl;

	Mat kxy = ky * kx.t();
	cout << "sum(kxy)=" << sum(kxy) << endl;

	Mat dst1;
	sepFilter2D(A, dst1, -1, kx, ky);
	cout << "dst1=" << dst1 << endl;

	Mat dst2;
	filter2D(A, dst2, -1, kxy);
	cout << "dst2=" << dst2 << endl;

	Mat dst3;
	GaussianBlur(A, dst3, Size(kSize, kSize), 0.0, 0.0);
	cout << "dst3=" << dst3 << endl;*/

	//0610
	/*Mat srcImage = imread("lena.jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;

	int ksize = 7;
	Mat dstImage1;
	medianBlur(srcImage, dstImage1, ksize);
	imshow("1", dstImage1);

	Mat dstImage2;
	blur(srcImage, dstImage2, Size(ksize, ksize));
	imshow("2", dstImage2);

	Mat dstImage3;
	GaussianBlur(srcImage, dstImage3, Size(ksize, ksize), 0, 0);
	imshow("3", dstImage3);

	ksize = 11;
	Mat dstImage4;
	GaussianBlur(srcImage, dstImage4, Size(ksize, ksize), 0, 0);
	imshow("4", dstImage4);

	Mat kx = getGaussianKernel(ksize, 0.0);
	Mat ky = getGaussianKernel(ksize, 0.0);
	Mat kxy = ky * kx.t();

	Mat dstImage5;
	sepFilter2D(srcImage, dstImage5, -1, kx, ky);
	imshow("5", dstImage5);

	Mat dstImage6;
	filter2D(srcImage, dstImage6, -1, kxy);
	imshow("6", dstImage6);*/

	//0611
	/*uchar dataA[] = { 1,1,1,1,1,1,
					  1,1,1,1,1,1,
					  1,1,9,9,1,1,
					  1,1,9,9,1,1,
					  1,1,1,1,1,1,
					  1,1,1,1,1,1 };
	Mat A(6, 6, CV_8U, dataA);
	cout << "A=" << A << endl;

	int dx = 1, dy = 0;
	int ksize = 3;
	Mat kx, ky;
	getDerivKernels(kx, ky, dx, dy, ksize);
	cout << "kx=" << kx << endl;
	cout << "ky=" << ky << endl;

	Mat kxy = ky * kx.t();
	cout << "kxy=" << kxy << endl;

	int ddepth = CV_16S;
	Mat dst1;
	sepFilter2D(A, dst1, ddepth, kx, ky);
	cout << "dst1=" << dst1 << endl;

	Mat dst2;
	filter2D(A, dst2, ddepth, kxy);
	cout << "dst2=" << dst2 << endl;

	Mat dst3;
	Sobel(A, dst3, ddepth, dx, dy, ksize);
	cout << "dst3=" << dst3 << endl;

	Mat dst4;
	Sobel(A, dst4, ddepth, dx, dy, -1);
	cout << "dst4=" << dst4 << endl;

	Mat dst5;
	Scharr(A, dst5, ddepth, dx, dy);
	cout << "dst5=" << dst5 << endl;*/

	//0612
	/*//Mat srcImage = imread("rect.jpg", IMREAD_GRAYSCALE);
	Mat srcImage = imread("lena.jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;
	imshow("rect", srcImage);

	int ksize = 3;
	int ddepth = CV_32F;
	Mat dstGx, dstGy;
	Sobel(srcImage, dstGx, ddepth, 1, 0, ksize);
	Sobel(srcImage, dstGy, ddepth, 0, 1, ksize);

	int dtype = CV_8U;
	Mat dstImageGx;
	normalize(abs(dstGx), dstImageGx, 0, 255, NORM_MINMAX, dtype);

	imshow("dstImageGx", dstImageGx);

	Mat dstImageGy;
	normalize(abs(dstGy), dstImageGy, 0, 255, NORM_MINMAX, dtype);
	imshow("dstImageGy", dstImageGy);

	Mat dstMag;
	magnitude(dstGx, dstGy, dstMag);
	Mat dstImageGxy;
	normalize(dstMag, dstImageGxy, 0, 255, NORM_MINMAX, dtype);
	imshow("dstImageGxy", dstImageGxy);*/

	//0613
	/*uchar dataA[] = { 1,1,1,1,1,1,
					  1,1,1,1,1,1,
					  1,1,9,9,1,1,
					  1,1,9,9,1,1,
					  1,1,1,1,1,1,
					1,1,1,1,1,1 };
	Mat A(6, 6, CV_8U, dataA);
	cout << "A=" << A << endl;

	int ksize = 3;
	float K[2][9] = { {0,1,0,1,-4,1,0,1,0},
					  {2,0,2,0,-8,0,2,0,2} };
	Mat kernel(3, 3, CV_32F, K[ksize == 3]);

	int ddepth = CV_16S;
	Mat dst1;
	filter2D(A, dst1, ddepth, kernel);
	cout << "dst1=" << dst1 << endl;

	Mat dst2;
	Laplacian(A, dst2, ddepth, ksize);
	cout << "dst2=" << dst2 << endl;*/

	//0614
	/*//Mat srcImage = imread("rect.jpg", IMREAD_GRAYSCALE);
	Mat srcImage = imread("lena.jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;

	int ksize = 21;
	Mat blurImage;
	GaussianBlur(srcImage, blurImage, Size(ksize, ksize), 0.0);

	Mat lapImage;
	Laplacian(blurImage, lapImage, CV_32F, ksize);
	Mat dstImage;
	ZeroCrossing(lapImage, dstImage, 10);

	imshow("dst", dstImage);*/

	//0615
	/*//Mat srcImage = imread("rect.jpg", IMREAD_GRAYSCALE);
	Mat srcImage = imread("lena.jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;

	const int ksize =9;
	float logArr[ksize*ksize];
	int s, t, k = 0;
	float g;
	float sigma = 1.4f;//0.3f*(ksize / 2 - 1.0f) + 0.8f;
	for(s = -ksize/2; s<=ksize/2; s++)
		for (t = -ksize / 2; t <= ksize / 2; t++) {
			g = exp(-((float)s*s + (float)t*t) / (2 * sigma*sigma));
			g *= (1 - ((float)s*s + (float)t*t) / (2 * sigma*sigma));
			g /= (3.141592f*sigma*sigma*sigma*sigma);
			logArr[k++] = -g;
		}
	Mat logKernel(ksize, ksize, CV_32F, logArr);
	cout << "logKernel=" << logKernel << endl;

	Mat logImage;
	filter2D(srcImage, logImage, CV_32F, logKernel);

	Mat dstImage;
	ZeroCrossing(logImage, dstImage, 10);

	imshow("d", dstImage);

	Mat white2(512, 512, CV_8UC3, Scalar::all(255));
	imshow("w", white2);*/

	//0616
/*	Mat srcImage = imread("morphology.jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;
	imshow("src", srcImage);

	Size size(5, 5);
	Mat rectKernel = getStructuringElement(MORPH_RECT, size);
	cout << "rectKernel=" << rectKernel << endl;

	int iterations = 3;
	Point anchor(-1, -1);
	Mat erodeImage;
	erode(srcImage, erodeImage, rectKernel, anchor, iterations);
	imshow("erodeImage", erodeImage);

	Mat dilateImage;
	dilate(srcImage, dilateImage, rectKernel, anchor, iterations);
	imshow("dilateImage", dilateImage);

	Mat ellipseKernel = getStructuringElement(MORPH_ELLIPSE, size);
	cout << "ellipseKernel=" << ellipseKernel << endl;

	Mat erodeImage2;
	erode(srcImage, erodeImage2, ellipseKernel, anchor, iterations);
	imshow("erodeImage2", erodeImage2);

	Mat dilateImage2;
	dilate(srcImage, dilateImage2, ellipseKernel, anchor, iterations);
	imshow("dilateIMage2", dilateImage2);

	Mat crossKernel = getStructuringElement(MORPH_CROSS, size);
	cout << "crossKernel=" << crossKernel << endl;

	Mat erodeImage3;
	erode(srcImage, erodeImage3, crossKernel, anchor, iterations);
	imshow("erodeImage3", erodeImage3);

	Mat dilateImage3;
	dilate(srcImage, dilateImage3, crossKernel, anchor, iterations);
	imshow("dilateImage3", dilateImage3);*/

	//0617 - 18
	/*//Mat srcImage = imread("morphology.jpg", IMREAD_GRAYSCALE);
	Mat srcImage = imread("lena.jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;
	imshow("src", srcImage);

	Size size(5, 5);
	Mat rectKernel = getStructuringElement(MORPH_RECT, size);
	cout << "rectKernel=" << rectKernel << endl;

	int iterations = 5;
	Point archor(-1, -1);

	Mat openImage;
	morphologyEx(srcImage, openImage, MORPH_OPEN, rectKernel, archor, iterations);
	imshow("openImage", openImage);

	Mat closeImage;
	morphologyEx(srcImage, closeImage, MORPH_CLOSE, rectKernel, archor, iterations);
	imshow("closeImage", closeImage);

	iterations = 1;
	Mat gradientImage;
	morphologyEx(srcImage, gradientImage, MORPH_GRADIENT, rectKernel, archor, iterations);
	imshow("gradientImage", gradientImage);

	Mat tophatImage;
	morphologyEx(srcImage, tophatImage, MORPH_TOPHAT, rectKernel, archor, iterations);
	imshow("tophatImage", tophatImage);

	Mat blackhatImage;
	morphologyEx(srcImage, blackhatImage, MORPH_BLACKHAT, rectKernel, archor, iterations);
	imshow("blackhatImage", blackhatImage);*/

	/*float dataA[] = { 1,1,1,1,1,1,
					 1,1,1,1,1,1,
					1,1,9,9,1,1,
					1,1,9,9,1,1,
					1,1,1,1,1,1,
					1,1,1,1,1,1 };
	float dataB[] = { 9,9,1,
					9,9,1,
					1,1,1 };
	Mat A(6, 6, CV_32F, dataA);
	Printmat("A=", A);

	Mat B(3, 3, CV_32F, dataB);
	Printmat("B=", B);

	double minVal, maxVal;
	Point minLoc, maxLoc;
	Mat result;

	matchTemplate(A, B, result, TM_SQDIFF);
	Printmat("result:TM_SQDIFF=", result);
	minMaxLoc(result, &minVal, NULL, &minLoc, NULL);
	cout << "minVal=" << minVal << endl;
	cout << "minLoc=" << minLoc << endl;

	matchTemplate(A, B, result, TM_SQDIFF_NORMED);
	Printmat("result:TM_SQDIFF_NORMED=", result);
	minMaxLoc(result, &minVal, NULL, &minLoc, NULL);
	cout << "minVal=" << minVal << endl;
	cout << "minLoc=" << minLoc << endl;

	matchTemplate(A, B, result, TM_CCORR);
	Printmat("result:TM_CCORR=", result);
	minMaxLoc(result, NULL, &maxVal, NULL, &maxLoc);
	cout << "maxVal=" << maxVal << endl;
	cout << "maxLoc=" << maxLoc << endl;

	matchTemplate(A, B, result, TM_CCORR_NORMED);
	Printmat("result:TM_CCORR_NORMED=", result);
	minMaxLoc(result, NULL, &maxVal, NULL, &maxLoc);
	cout << "maxVal=" << maxVal << endl;
	cout << "maxLoc=" << maxLoc << endl;

	matchTemplate(A, B, result, TM_CCOEFF);
	Printmat("result:TM_CCOEFF=", result);
	minMaxLoc(result, NULL, &maxVal, NULL, &maxLoc);
	cout << "maxVal=" << maxVal << endl;
	cout << "maxLoc=" << maxLoc << endl;

	matchTemplate(A, B, result, TM_CCOEFF_NORMED);
	Printmat("result:TM_CCOEFF_NORMED=", result);
	minMaxLoc(result, NULL, &maxVal, NULL, &maxLoc);
	cout << "maxVal=" << maxVal << endl;
	cout << "maxLoc=" << maxLoc << endl;*/

	//0619
	Mat srcImage = imread("alphabet.bmp", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;
	Mat tImage1 = imread("A.bmp", IMREAD_GRAYSCALE);
	Mat tImage2 = imread("S.bmp", IMREAD_GRAYSCALE);
	Mat tImage3 = imread("b.bmp", IMREAD_GRAYSCALE);
	Mat tImage4 = imread("m.bmp", IMREAD_GRAYSCALE);
	if (tImage1.empty() || tImage2.empty() || tImage3.empty() || tImage4.empty())
		return -1;

	Mat dstImage;
	cvtColor(srcImage, dstImage, COLOR_GRAY2BGR);

	double minVal, maxVal;
	Point minLoc, maxLoc;
	Mat result;

	matchTemplate(srcImage, tImage1, result, TM_SQDIFF);
	minMaxLoc(result, &minVal, NULL, &minLoc, NULL);
	rectangle(dstImage, minLoc, Point(minLoc.x + tImage1.cols, minLoc.y + tImage1.rows), Scalar(0, 255, 0), 2);

	matchTemplate(srcImage, tImage2, result, TM_SQDIFF_NORMED);
	minMaxLoc(result, &minVal, NULL, &minLoc, NULL);
	rectangle(dstImage, minLoc, Point(minLoc.x + tImage2.cols, minLoc.y + tImage2.rows), Scalar(0, 255, 0), 2);

	matchTemplate(srcImage, tImage3, result, TM_CCORR_NORMED);
	minMaxLoc(result, NULL, &maxVal, NULL, &maxLoc);
	rectangle(dstImage, maxLoc, Point(maxLoc.x + tImage3.cols, maxLoc.y + tImage3.rows), Scalar(0, 255, 0), 2);

	matchTemplate(srcImage, tImage4, result, TM_CCOEFF_NORMED);
	minMaxLoc(result, NULL, &maxVal, NULL, &maxLoc);
	rectangle(dstImage, maxLoc, Point(maxLoc.x + tImage4.cols, maxLoc.y + tImage4.rows), Scalar(0, 255, 0), 2);

	imshow("d", dstImage);

	/*Mat src = imread("lena.jpg", IMREAD_GRAYSCALE);
	Mat dst1, dst2;
	Mat kernel = getStructuringElement(MORPH_CROSS, Size(3, 3));

	erode(src, dst1, kernel, Point(-1, -1), 3);
	imshow("erode", dst1);

	dilate(src, dst2, kernel, Point(-1, -1), 3);
	imshow("dilate", dst2);*/

	waitKey();
	return 0;
}

void Printmat(const char*strName, Mat m) {
	int x, y;
	float fValue;
	cout << endl << strName << endl;
	cout << setiosflags(ios::fixed);
	for (y = 0; y < m.rows; y++){
		for (x = 0; x < m.cols; x++) {
			fValue = m.at<float>(y, x);
			cout << setprecision(2) << setw(8) << fValue;
		}
		cout << endl;
	}
}

void ZeroCrossing(Mat &src, Mat& dst, int th) {
	int x, y;
	double a, b;

	Mat zeroCrossH(src.size(), CV_32F, Scalar::all(0));
	Mat_<float> _src(src);
	for(y=1;y<src.rows-1;y++)
		for (x = 1; x < src.cols - 1; x++) {
			a = _src(y, x);
			b = _src(y, x + 1);
			if (a == 0)
				a = _src(y, x - 1);
			if (a*b < 0)
				zeroCrossH.at<float>(y, x) = fabs(a) + fabs(b);
			else
				zeroCrossH.at <float>(y, x) = 0;
		}

	Mat zeroCrossV(src.size(), CV_32F, Scalar::all(0));
	for (y = 1; y < src.rows - 1; y++)
		for (x = 1; x < src.cols - 1; x++) {
			a = _src(y, x);
			b = _src(y + 1, x);
			if (a == 0)
				a = _src(y-1, x);
			if (a*b < 0)
				zeroCrossV.at<float>(y, x) = fabs(a) + fabs(b);
			else
				zeroCrossV.at <float>(y, x) = 0;
		}
	Mat zeroCross(src.size(), CV_32F, Scalar::all(0));
	add(zeroCrossH, zeroCrossV, zeroCross);
	threshold(zeroCross, dst, th, 255, THRESH_BINARY);
}
