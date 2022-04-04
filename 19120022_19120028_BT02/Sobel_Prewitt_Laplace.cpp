#include "Sobel_Prewitt_Laplace.h"
int detectBySobel(Mat src, Mat &dst) {
	showImage(src, "Anh ban dau");
	//kernel thực hiện phép tích chập
	int xkernel[9] = { -1,0,1,-2,0,2,-1,0,1 };
	int ykernel[9] = { 1,2,1,0,0,0,-1,-2,-1 };
	// chứa các vị trí quanh pixel đang xét
	int hx[9] = { -1,-1,-1,0,0,0,1,1,1 };
	int hy[9] = { -1,0,1,-1,0,1,-1,0,1 };
	Mat x, y;
	int n = src.rows;
	int m = src.cols;
	src = BGR2Gray(src);
	// ma trận chứa gradient theo x với y
	x = Mat::zeros(n, m, CV_8UC1);
	y = Mat::zeros(n, m, CV_8UC1);
	dst = Mat::zeros(n,m,CV_8UC1);
	for (int i = 0;i < n;++i) {
		for (int j = 0;j < m;++j) {
			int tmpx = 0;
			int tmpy = 0;
			//lặp qua các pixel xung quanh pixel (i,j) để tính tích chập
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
			// tổng hợp hai ảnh gradient
			int tmp = round(sqrt(pow(x.at<uchar>(i, j), 2) + pow(y.at<uchar>(i, j), 2)));
			dst.at<uchar>(i, j) = processPixel(tmp);
		}
	}
	if (!dst.data) return 0;
	//hiển thị 2 ảnh x,y
	showImage(x, "Sobel_x");
	showImage(y, "Sobel_y");
	return 1;
}
int detectByPrewitt(Mat src, Mat &dst) {
	showImage(src, "Anh ban dau");
	//kernel thực hiện phép tích chập
	int xkernel[9] = { 1,0,-1,1,0,-1,1,0,-1 };
	int ykernel[9] = { 1,1,1,0,0,0,-1,-1,-1 };
	// chứa các vị trí quanh pixel đang xét
	int hx[9] = { -1,-1,-1,0,0,0,1,1,1 };
	int hy[9] = { -1,0,1,-1,0,1,-1,0,1 };
	Mat x, y;
	int n = src.rows;
	int m = src.cols;
	src = BGR2Gray(src);
	// ma trận chứa gradient theo x với y
	x = Mat::zeros(n, m, CV_8UC1);
	y = Mat::zeros(n, m, CV_8UC1);
	dst = Mat::zeros(n, m, CV_8UC1);
	for (int i = 0;i < n;++i) {
		for (int j = 0;j < m;++j) {
			int tmpx = 0;
			int tmpy = 0;
			//lặp qua các pixel xung quanh pixel (i,j) để tính tích chập
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
			// tổng hợp hai ảnh gradient
			int tmp = round(sqrt(pow(x.at<uchar>(i, j), 2) + pow(y.at<uchar>(i, j), 2)));
			dst.at<uchar>(i, j) = processPixel(tmp);
		}
	}
	//hiển thị hai ảnh x,y
	if (!dst.data) return 0;
	showImage(x, "Prewitt_x");
	showImage(y, "Prewitt_y");
	return 1;
}

int detectByLaplace(Mat src, Mat& des) {
	Mat gray_scale = BGR2Gray(src);
	gray_scale.copyTo(des);

	int mask[] = { 0,-1,0,
			  -1, 4,-1,
			   0,-1,0 };
	int rows = src.rows;
	int cols = src.cols;
	for (int j = 1; j < rows - 1; ++j)
		for (int i = 1; i < cols - 1; ++i)
		{
			int n = int(gray_scale.at<uchar>(j - 1, i)) * mask[1];
			int s = int(gray_scale.at<uchar>(j + 1, i)) * mask[3];
			int e = int(gray_scale.at<uchar>(j, i - 1)) * mask[5];
			int w = int(gray_scale.at<uchar>(j, i + 1)) * mask[7];
			int c = int(gray_scale.at<uchar>(j, i)) * mask[4];
			int tmp = c + n + s + e + w;
			if (tmp < 0) tmp *= -1;
			if (tmp > 255)
				tmp = 255;
			des.at<uchar>(j, i) = uchar(tmp);
		}
	if (!des.data)
		return 0;
	return 1;
}