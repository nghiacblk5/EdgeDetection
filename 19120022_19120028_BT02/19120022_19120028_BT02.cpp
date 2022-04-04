#include "process.h"
#include "Sobel_Prewitt_Laplace.h"
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

int main(int argc, char** argv)
{
	if (argc == 2) {
		if (!(strcmp(argv[1], "help"))) {
			cout << "Edge detection" << endl << endl;
			cout << "1. Sobel: <tenchuongtrinh>  <duongdantaptinanh>  sob" << endl;
			cout << "2. Prewitt: <tenchuongtrinh> <duongdantaptinanh> pre" << endl;
			cout << "3. Laplace: <tenchuongtrinh> <duongdantaptinanh> lap" << endl;
			cout << "4: Canny: Thuc hien 1 trong 2 cach:\n";
			cout << "\tCach 1: <tenchuongtrinh> <duongdantaptinanh> canny " << endl;
			cout << "\tCach 2: <tenchuongtrinh> <duongdantaptinanh> canny <low threshold>  <high threshold>" << endl;
		}
		else {
			cout << "Cu phap khong hop le";

		}
	}
	else if (argc == 3)
	{
		Mat image = imread(argv[1], IMREAD_COLOR);
		if (!image.data) {
			cout << "Khong the mo anh";
			return -1;
		}
		if (!(strcmp(argv[2], "sob"))) {
			Mat dst;
			int rst = detectBySobel(image, dst);
			if (rst) {
				cout << "Hien thi thanh cong";
			}
		}
		else if (!(strcmp(argv[2], "pre"))) {
			Mat dst;
			int rst = detectByPrewitt(image, dst);
			if (rst) {
				cout << "Hien thi thanh cong";
			}
		}
		else if (!(strcmp(argv[2], "lap"))) {
			Mat dst;
			int rst = detectByLaplace(image, dst);
			if (rst)
			{
				showImage(image, "Anh ban dau");
				showImage(dst, "Laplace");
			}
				

		}
		else if (!(strcmp(argv[2], "canny"))) {
			Mat dst;
			int rst = detectByCany(image, dst);
			if (rst) {
				showImage(image, "Anh ban dau");
				showImage(dst, "Canny");
			}
		}
		else {
			cout << "Cu phap khong hop le";
		}
	}
	else if (argc == 5)
	{
		int l = stoi(argv[3]);
		int h = stoi(argv[4]);
		Mat image = imread(argv[1], IMREAD_COLOR);
		if (!(strcmp(argv[2], "canny"))) {
			Mat dst;
			int rst = detectByCany(image, dst, l, h);
			if (rst) {
				showImage(image, "Anh ban dau");
				showImage(dst, "Canny");
			}
		}
	}
	else {
		cout << "Cu phap khong hop le";
	}


	return 0;
}
	
