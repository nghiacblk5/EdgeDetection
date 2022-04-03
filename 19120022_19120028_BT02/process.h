#pragma once
#include "opencv2\core\core.hpp"
#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"
//#include "opencv2/opencv.hpp"
#include <iostream>
//#include <cmath>

#define PI 3.14159265
using namespace std;
using namespace cv;

void showImage(Mat image, string s);
Mat BGR2Gray(Mat image);
uchar processPixel(int k);
int detectByLaplace(Mat src, Mat &des);
