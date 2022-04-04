#pragma once
//#include "opencv2\core\core.hpp"
//#include "opencv2\highgui\highgui.hpp"
//#include "opencv2\imgproc\imgproc.hpp"
//#include <iostream>
#include <cmath>
#include "process.h"

#define PI 3.14159265
//using namespace std;
//using namespace cv;
class CannyEdgeDetection
{
private:
	
	Mat image;   //ảnh ban đầu 
	Mat gray_scale;  //ảnh grayscale 
	Mat gaussian_blur; //ảnh sau khi blur   
	Mat grad_x;    //đạo hàm hướng x
	Mat grad_y;    //đạo hàm hướng y
	Mat grad;      //đạo hàm tổng
	Mat direction; // hướng của mỗi pixel
	Mat non_max;   // ảnh sau khi áp dụng non_max_suppression
	Mat final_image;// ảnh sau khi áp dụng double threshold -> ảnh cuối cùng
	int gaussian_blur_kernelSize;  //kích thước kernel Gaussian
	double* gaussian_kernel;
	int sobel_size; //kích thước sobel
	int* sobel_x;
	int* sobel_y;
	int upper;  //hifgh threshold
	int lower;  //low threshold

public: 
	CannyEdgeDetection(Mat source);
	CannyEdgeDetection(Mat source, int low_threshold, int high_threshold);
	void setFinalImage(Mat&);
	void grayscale();
	void gaussianBlur();
	void sobel();
	void non_max_suppression();
	void threshold();
	void detect();
	~CannyEdgeDetection();

};

