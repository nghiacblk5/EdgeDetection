#include "SobelAndPrewitt.h"
int detectBySobel(Mat src, Mat &dst) {
	int xkernel[9] = { -1,0,1,-2,0,2,-1,0,1 };
	int ykernel[9] = { 1,2,1,0,0,0,-1,-2,-1 };
	int hx[9] = { -1,-1,-1,0,0,0,1,1,1 };
	int hy[9] = { -1,0,1,-1,0,1,-1,0,1 };
	Mat x, y;
	int n = src.rows;
	int m = src.cols;
	src = BGR2Gray(src);
	x = Mat::zeros(n, m, CV_8UC1);
	y = Mat::zeros(n, m, CV_8UC1);
	dst = Mat::zeros(n,m,CV_8UC1);
	for (int i = 0;i < n;++i) {
		for (int j = 0;j < m;++j) {
			int tmpx = 0;
			int tmpy = 0;
			for (int k = 0;k < 9;++k) {
				int vx = i + hx[k];
				int vy = j + hy[k];
				int value = 0;
				if (vx >= 0 && vx < n && vy >= 0 && vy < m) value = src.at<uchar>(vx, vy);
				tmpx += value * xkernel[k];
				tmpy += value * ykernel[k];
			}
			x.at<uchar>(i, j) = processPixel(tmpx);
			y.at<uchar>(i, j) = processPixel(tmpy);
			int tmp = round(sqrt(pow(x.at<uchar>(i, j), 2) + pow(y.at<uchar>(i, j), 2)));
			dst.at<uchar>(i, j) = processPixel(tmp);
		}
	}
	if (!dst.data) return 0;
	return 1;
}
int detectByPrewitt(Mat src, Mat &dst) {
	int xkernel[9] = { 1,0,-1,1,0,-1,1,0,-1 };
	int ykernel[9] = { 1,1,1,0,0,0,-1,-1,-1 };
	int hx[9] = { -1,-1,-1,0,0,0,1,1,1 };
	int hy[9] = { -1,0,1,-1,0,1,-1,0,1 };
	Mat x, y;
	int n = src.rows;
	int m = src.cols;
	src = BGR2Gray(src);
	x = Mat::zeros(n, m, CV_8UC1);
	y = Mat::zeros(n, m, CV_8UC1);
	dst = Mat::zeros(n, m, CV_8UC1);
	for (int i = 0;i < n;++i) {
		for (int j = 0;j < m;++j) {
			int tmpx = 0;
			int tmpy = 0;
			for (int k = 0;k < 9;++k) {
				int vx = i + hx[k];
				int vy = j + hy[k];
				int value = 0;
				if (vx >= 0 && vx < n && vy >= 0 && vy < m) value = src.at<uchar>(vx, vy);
				tmpx += value * xkernel[k];
				tmpy += value * ykernel[k];
			}
			x.at<uchar>(i, j) = processPixel(tmpx);
			y.at<uchar>(i, j) = processPixel(tmpy);
			int tmp = round(sqrt(pow(x.at<uchar>(i, j), 2) + pow(y.at<uchar>(i, j), 2)));
			dst.at<uchar>(i, j) = processPixel(tmp);
		}
	}
	if (!dst.data) return 0;
	return 1;
}