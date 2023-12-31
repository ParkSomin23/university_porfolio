#include "pch.h"
#include "opencv.hpp"
#include "opencv2/nonfree/nonfree.hpp"
using namespace std;
using namespace cv;

int main() {
	
	Mat dstImage(512, 512, CV_8UC3, Scalar(255, 255, 255));

	imshow("dstImage", dstImage);
	cvSetMouseCallback("dstImage", onMouse, (void *)&dstImage);

	waitKey();

	return 0;
}

void onMouse(int event, int x, int y, int flags, void *param) {

	Mat *pMat = (Mat*)param;
	Mat image = Mat(*pMat);
	switch (event)
	{
	case EVENT_LBUTTONDOWN:
		circle(image, Point(x, y), 5, Scalar(255, 0, 0), 5);
		break;
	default:
		break;
	}
	imshow("dstImage", image);
}