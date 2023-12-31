#include "pch.h"
#include "opencv.hpp"
using namespace cv;
using namespace std;

Mat srcImage;

static void clickMouse(int event, int x, int y, int flags, void *param) {
	Mat *pMat = (Mat*)param;
	Mat image = Mat(*pMat);

	if (event == EVENT_LBUTTONDOWN) {
		Vec3b color = srcImage.at<Vec3b>(y, x);

		Mat colorMat(color);
	
		Mat hsvImage;
		cvtColor(srcImage, hsvImage, COLOR_BGR2HSV);
		vector<Mat>planes;
		split(hsvImage, planes);
		Mat hueImage = planes[0];

		Rect roi(x-3, y-3, 3, 3);
		rectangle(srcImage, roi, Scalar(0, 0, 255), 2);
		Mat roiImage = hueImage(roi);

		int histSize = 256;
		float hValue[] = { 0,256 };
		const float * ranges[] = { hValue };
		int channels = 0;
		int dims = 1;

		Mat hist;
		calcHist(&roiImage, 1, &channels, Mat(), hist, dims, &histSize, ranges);

		Mat hueImage2;
		hueImage.convertTo(hueImage2, CV_32F);

		Mat backProject;
		calcBackProject(&hueImage2, 1, &channels, hist, backProject, ranges);

		double minVal, maxVal;
		minMaxLoc(backProject, &minVal, &maxVal);
		cout << "minVal=" << minVal << endl;
		cout << "maxVal=" << maxVal << endl;

		Mat backProject2;
		normalize(backProject, backProject2, 0, 255, NORM_MINMAX, CV_8U);

		Mat result;
		bitwise_and(srcImage, srcImage, result, backProject2);

		Mat result2;
		Size size(3, 3);
		Mat kenel = getStructuringElement(MORPH_ELLIPSE, size);
		morphologyEx(result, result2, MORPH_CLOSE, kenel, Point(-1, -1), 2);

		imshow("src", srcImage);
		imshow("backProject2", backProject2);
		imshow("result", result);
		imshow("result2", result2);
	}
}

int main()
{	
	srcImage = imread("fruits.jpg");
	if (srcImage.empty())
		return -1;

	Mat result(srcImage.rows,srcImage.cols,srcImage.type());

	cout << srcImage.type() << endl;

	imshow("srcImage", srcImage);
	imshow("result", result);

	setMouseCallback("srcImage", clickMouse, (void*)&result);

	imshow("result", result);
	
	waitKey();

	return 0;

}