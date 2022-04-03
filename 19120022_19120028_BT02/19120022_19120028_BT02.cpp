
#include "process.h"
#include "CannyEdgeDetection.h"

int detectByCany(Mat sourceImage, Mat &destinationImage) {
	CannyEdgeDetection* c = new CannyEdgeDetection(sourceImage);
	c->detect();
	c->setFinalImage(destinationImage);
	if (!destinationImage.data) return 0;
	return 1;

}

int detectByCany(Mat sourceImage, Mat& destinationImage, int low_threshold, int high_threshold) {
	CannyEdgeDetection* c = new CannyEdgeDetection(sourceImage, low_threshold,high_threshold);
	c->detect();
	c->setFinalImage(destinationImage);
	if (!destinationImage.data) return 0;
	return 1;
}

int main(/*int argc, char** argv*/)
{

	//if (argc == 2) {
	//	if (!(strcmp(argv[1], "help"))) {

	//	}
	//	else {
	//		cout << "Cu phap khong hop le";

	//	}
	//}
	//else if (argc == 3) 
	//{
	//	Mat image = imread(argv[1], IMREAD_COLOR);
	//	if (!image.data) {
	//		cout << "Khong the mo anh";
	//		return -1;
	//	}
	//	if (!(strcmp(argv[2], "sob"))) {
	//		//do sobel
	//	}
	//	else if (!(strcmp(argv[2], "pre"))) {
	//		//do prewitt
	//	}
	//	else if (!(strcmp(argv[2], "lap"))) {
	//		Mat dst;
	//		int rst = detectByLaplace(image, dst);
	//		if (rst)
	//			showImage(dst, "Laplace");

	//	}
	//	else if (!(strcmp(argv[2], "canny"))){
	//		Mat dst;
	//		int rst = detectByCany(image, dst);
	//		if (rst)
	//			showImage(dst, "Canny");
	//	}
	//	else {
	//		cout << "Cu phap khong hop le";

	//	}
	//}

	//else if (argc == 5)
	//{
	//	int l = stoi(argv[3]);
	//	int h = stoi(argv[4]);
	//	Mat image = imread(argv[1], IMREAD_COLOR);
	//	if(!(strcmp(argv[2], "canny"))) {
	//		Mat dst;
	//		int rst = detectByCany(image, dst,l,h);
	//		if (rst)
	//			showImage(dst, "Canny");
	//}
	//else {
	//	cout << "Cu phap khong hop le";

	//}
	string image[3] = { "github.png", "lena.png", "tf.jpg" };
	for (int i = 0; i < 3; ++i)
	{
		Mat src = imread(image[i], IMREAD_COLOR);
		Mat dst; 
		int rst = detectByCany(src, dst);
		if (rst)
			showImage(dst, image[i]);
		Mat canny_dst;
		Canny(src, canny_dst, 35, 70);
		showImage(canny_dst, "Nothing");
		
	}
	
	return 0;
}


