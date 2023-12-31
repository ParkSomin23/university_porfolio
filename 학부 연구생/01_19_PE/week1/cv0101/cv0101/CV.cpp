#include "pch.h"
#include "opencv.hpp"
using namespace cv;
using namespace std;

int main()
{
#include "pch.h"
#include "opencv.hpp"
	using namespace cv;
	using namespace std;
	/*
	template<> inline void Ptr<FILE>::delete_obj() {
		fclose(obj);
	}*/

	int main()
	{
		//0201
		/*
		Mat A1(1, 2, DataType<uchar>::type);

		A1.at<uchar>(0, 0) = 1;
		A1.at<uchar>(0, 1) = 2;
		cout << "A1" << A1 << endl;
		cout << "depth=" << A1.depth() << ","
			<< "channels=" << A1.channels() << endl;

		Mat A2(1, 2, DataType<Vec<uchar,3>>::type);
		A2.at<Vec<uchar, 3>>(0, 0) = Vec3d(10, 20, 30);
		A2.at<Vec<uchar, 3>>(0, 1) = Vec3d(40, 50, 60);
		cout << "A2" << A2 << endl;
		cout << "depth=" << A2.depth() << ","
			<< "channels=" << A2.channels() << endl;

		Mat B(1, 2, DataType<float>::type);
		B.at<float>(0, 0) = 10.0f;
		B.at<float>(0, 1) = 20.0f;
		cout << "B" << B << endl;
		cout << "depth=" << B.depth() << "," << "channels=" << B.channels() << endl;

		Mat C(1, 2, DataType<Point>::type);
		C.at<Point>(0, 0) = Point(100, 100);
		C.at<Point>(0, 1) = Point(200, 200);
		cout << "C" << C << endl;
		cout << "depth=" << C.depth() << "," << "channels=" << C.channels() << endl;

		Mat D(1, 2, DataType<complex<double>>::type);
		D.at<complex<double>>(0, 0) = complex<double>(10.0, 20.0);
		D.at<complex<double>>(0, 1) = complex<double>(10.0, 20.0);
		cout << "D" << D << endl;
		cout << "depth=" << D.depth() << "," << "channels=" << D.channels() << endl;
		*/

		//0202
		/*Point2f pt1(0.1f, 0.2f), pt2(0.3f, 0.4f);

		Point pt3 = (pt1 + pt2) * 10.0f;
		Point pt4 = (pt1 - pt2) * 10.0f;
		Point pt5 = Point(10, 10);
		Point2f pt6 = Point2f(10.0f, 10.0f);

		cout << "pt1:(" << pt1.x << "," << pt1.y << ")" << endl;
		cout << "pt2:(" << pt2.x << "," << pt2.y << ")" << endl;
		cout << "pt3:(" << pt3.x << "," << pt3.y << ")" << endl;
		cout << "pt4:(" << pt4.x << "," << pt4.y << ")" << endl;
		cout << "pt5:(" << pt5.x << "," << pt5.y << ")" << endl;
		cout << "pt6:(" << pt6.x << "," << pt6.y << ")" << endl;

		if (pt1 == pt2)
			cout << "equal" << endl;
		else
			cout << "not equal" << endl;

		float fValue = pt1.dot(pt2);
		cout << "fValue:" << fValue << endl;

		double normValue = norm(pt1);
		cout << "normValue:" << normValue << endl;

		Point pt(150, 150);
		Rect rect(100, 100, 200, 200);

		if (pt.inside(rect))
			cout << "inside" << endl;
		else
			cout << "outside" << endl;*/

			//0205
			/*Rect rt1(100, 100, 320, 240), rt2(200, 200, 320, 240);
			Point pt1(100, 100);
			Size size(100, 100);

			Rect rt3 = rt1 + pt1;
			Rect rt4 = rt1 + size;

			cout << "rt1:(" << rt1.x << "," << rt1.y << "," << rt1.width << "," << rt1.height << ")" << endl;
			cout << "rt1:" << rt1 << endl;
			cout << "rt2:" << rt2 << endl;
			cout << "rt3:" << rt3 << endl;
			cout << "rt4:" << rt4 << endl;

			Point ptTopLeft = rt1.tl();
			Point ptBottomRight = rt1.br();
			cout << "ptTopLeft in rt1:" << ptTopLeft << endl;
			cout << "ptBottomRight in rt1:" << ptBottomRight << endl;

			Point pt2(200, 200);
			if (rt1.contains(pt2))
				cout << "pt2 is inside point in rt1" << endl;

			Rect rt5 = rt1 & rt2;
			Rect rt6 = rt1 | rt2;
			cout << "rt5:" << rt5 << endl;
			cout << "rt6" << rt6 << endl;

			if (rt1 != rt2)
				cout << "not same" << endl;

			Mat img(600, 800, CV_8UC3);
			namedWindow("image", WINDOW_AUTOSIZE);

			rectangle(img, rt1, Scalar(255, 0, 0), 2);
			rectangle(img, rt2, Scalar(0, 255, 0), 2);
			rectangle(img, rt5, Scalar(0, 0, 255), 2);
			imshow("image", img);
			waitKey();
			rectangle(img, rt6, Scalar(0, 0, 1), 1);
			circle(img, pt2, 5, Scalar(255, 0, 255), 2);
			imshow("image", img);
			waitKey();*/

			//0206
			/*Point2f ptCenter(200.0f, 200.0f);
			Size size(100, 200);

			RotatedRect rt1(ptCenter, size, 135.0f);

			Point2f points[4];
			rt1.points(points);
			Rect rt2 = rt1.boundingRect();

			cout << "rt1:ptCenter(" << rt1.center.x << "," << rt1.center.y << "),"
				<< "size = (" << rt1.size.width << "," << rt1.size.height <<")" << endl;
			cout << "rt2:ptCenter(" << rt2.x << "," << rt2.y << "),"
				<< "size = (" << rt2.width << "," << rt2.height << ")" << endl;

			for (int i = 0; i < 4; i++)
				cout << "points[" << i << "]=" << points[i] << endl;

			Mat image(400, 400, CV_8UC3, Scalar(255, 255, 255));
			for (int i = 0; i < 4; i++)
				line(image, points[i], points[(i + 1) % 4], Scalar(0, 0, 255));
			rectangle(image, rt2, Scalar(255, 0, 0));
			circle(image, ptCenter, 5, Scalar(255, 0, 255), 2);
			imshow("image", image);
			waitKey();*/

			//0216
			/*Ptr<IplImage> Image(cvLoadImage("lena.jpg", IMREAD_GRAYSCALE));
			if (Image.empty())
				return -1;

			cvSaveImage("lena.bmp", Image);
			cvNamedWindow("Image", CV_WINDOW_AUTOSIZE);
			cvShowImage("Image", Image);
			cvWaitKey(0);
			cvDestroyAllWindows();
			*/

			//0217
			/*Ptr<CvMat> matA(cvCreateMat(2, 3, CV_32FC1));

			CV_MAT_ELEM(*matA, float, 0, 0) = 1.0f;
			CV_MAT_ELEM(*matA, float, 0, 1) = 2.0f;
			CV_MAT_ELEM(*matA, float, 0, 2) = 3.0f;


			CV_MAT_ELEM(*matA, float, 1, 0) = 4.0f;
			CV_MAT_ELEM(*matA, float, 1, 1) = 5.0f;
			CV_MAT_ELEM(*matA, float, 1, 2) = 6.0f;

			Mat A = cvarrToMat(matA);
			cout << "A=" << A << endl;*/

			//0218
			/*CvMat *pA = cvCreateMat(2, 3, CV_32FC1);
			Ptr<CvMat> matA(pA);

			CV_MAT_ELEM(*matA, float, 0, 0) = 1.0f;
			CV_MAT_ELEM(*matA, float, 0, 1) = 2.0f;
			CV_MAT_ELEM(*matA, float, 0, 2) = 3.0f;


			CV_MAT_ELEM(*matA, float, 1, 0) = 4.0f;
			CV_MAT_ELEM(*matA, float, 1, 1) = 5.0f;
			CV_MAT_ELEM(*matA, float, 1, 2) = 6.0f;

			Mat A = cvarrToMat(matA);
			cout << "A=" << A << endl;

			Ptr<FILE>outFile(fopen("matA.txt", "w"));

			if (outFile.empty())
				return -1;

			int x, y;
			for (y = 0; y < matA->rows; y++) {
				for (x = 0; x < matA->cols; x++)
					fprintf(outFile, "%6.2f", cvmGet(matA, y, x));
				fprintf(outFile, "\n");
			}*/

			//0221
			/*int sizes[] = { 2,3,4 };
			Mat B(3, sizes, CV_32FC1, Scalar(0));

			for (int i = 0; i < B.size[0]; i++) {
				cout << "\nB[" << i << "]" << endl;
				for (int j = 0; j < B.size[1]; j++) {
					for (int k = 0; k < B.size[2]; k++) {
						cout << B.at<float>(i, j, k);
						if (k != B.size[2] - 1)
							cout << ",";
						else
							cout << ";";
					}
					cout << endl;
				}
			}*/

			//0224
			/*Mat srcImage;
			srcImage.create(512, 512, CV_8UC3);

			for (int i = 0; i < srcImage.rows; i++)
				for (int j = 0; j < srcImage.cols; j++)
					srcImage.at<Vec3b>(i, j) = Vec3b(255, 0, 255);

			imshow("srcImage", srcImage);
			waitKey();*/

			//0225
			/*Mat A(4, 5, CV_32FC3);
			cout << "*A.refcount=" << *A.refcount << endl;

			Mat B = A;
			cout << "*A.refcount=" << *A.refcount << endl;
			cout << "*B.refcount=" << *B.refcount << endl;

			A.at<Vec3f>(0, 0) = Vec3f(0.75, 1.0, 10.0);
			cout << "A.data=" << hex << (int *)A.data << endl;
			cout << "B.data=" << hex << (int *)B.data << endl;

			cout << "A.data[0]=" << *(float*)A.data << endl;
			cout << "A.data[4]=" << *(float*)(A.data+4) << endl;
			cout << "A.data[8]=" << *(float*)(A.data+8) << endl;

			cout << "B.data[0]=" << *(float*)B.data << endl;
			cout << "B.data[4]=" << *(float*)(B.data + 4) << endl;
			cout << "B.data[8]=" << *(float*)(B.data + 8) << endl;

			cout << "A.isContinupus()=" << A.isContinuous() << endl;
			cout << "A.total()"<<dec << A.total() << endl;
			cout << "A.elemSize()=" << A.elemSize() << endl;
			cout << "A.elemSize1()=" << A.elemSize1() << endl;
			cout << "A.type()=" << A.type() << endl;
			cout << "A.depth()=" << A.depth() << endl;
			cout << "A.channels()=" << A.channels() << endl;

			cout << "A.step=" << A.step << endl;
			cout << "A.step1()=" << A.step1() << endl;
			cout << "A.empty()=" << A.empty() << endl;
			cout << "A.size()=" << A.size() << endl;*/

			//0227
			/*Mat A(3, 3, CV_32F);
			int idx[2];
			for(int i=0; i<A.rows; i++)
				for (int j = 0; j < A.cols; j++) {
					//A.at<float>(i, j) = i * A.cols + j;
					A.at<float>(Point(i,j)) = i * A.cols + j;
				}

			cout << A << endl;*/

			//2029
			/*Mat A(3, 3, CV_32F);
			for (int i = 0; i < A.rows; i++) {
				float* ptrA = A.ptr<float>(i);
				for (int j = 0; j < A.cols; j++)
					ptrA[j] = i * A.cols + j;
			}
			cout << A << endl;*/

		return 0;

	}

	return 0;

}