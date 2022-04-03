#include "CannyEdgeDetection.h"
#include "process.h"

CannyEdgeDetection::CannyEdgeDetection(Mat source) {

	source.copyTo(image);
	// khởi tạo kernel để thực hiện gaussian blur
	gaussian_blur_kernelSize = 5;
	gaussian_kernel = new double[gaussian_blur_kernelSize * gaussian_blur_kernelSize]{
								2,4,5,4,2,
								4,9,12,9,4,
								5,12,15,12,5,
								4,9,12,9,4,
								2,4,5,4,2 };
	for (int i = 0; i < gaussian_blur_kernelSize * gaussian_blur_kernelSize; ++i)
		gaussian_kernel[i] = gaussian_kernel[i] * 1.0 / 159;

	//khởi tạo mask thực hiện sobel
	sobel_size = 3;
	sobel_x = new int[sobel_size * sobel_size]{ 
							-1,0,1,
							-2,0,2,
							-1,0,1 };
	sobel_y = new int[sobel_size * sobel_size]{
							-1,-2,-1,
							0,0,0,
							1,2,1 };
	// high threshold
	upper = 70;

	// low threshold
	lower = 35;

}

CannyEdgeDetection::CannyEdgeDetection(Mat source, int low_threshold, int high_threshold) {
	source.copyTo(image);
	// khởi tạo kernel để thực hiện gaussian blur
	gaussian_blur_kernelSize = 5;
	gaussian_kernel = new double[gaussian_blur_kernelSize * gaussian_blur_kernelSize]{
								2,4,5,4,2,
								4,9,12,9,4,
								5,12,15,12,5,
								4,9,12,9,4,
								2,4,5,4,2 };
	for (int i = 0; i < gaussian_blur_kernelSize * gaussian_blur_kernelSize; ++i)
		gaussian_kernel[i] = gaussian_kernel[i] * 1.0 / 159;

	//khởi tạo mask thực hiện sobel
	sobel_size = 3;
	sobel_x = new int[sobel_size * sobel_size]{
							-1,0,1,
							-2,0,2,
							-1,0,1 };
	sobel_y = new int[sobel_size * sobel_size]{
							-1,-2,-1,
							0,0,0,
							1,2,1 };
	upper = high_threshold;
	lower = low_threshold;

}
void CannyEdgeDetection::grayscale() {
	//chuyển thành ảnh xám
	gray_scale = BGR2Gray(image);
	

}
void CannyEdgeDetection::gaussianBlur() {
	gray_scale.copyTo(gaussian_blur);
	
	int rows = gray_scale.rows;
	int cols = gray_scale.cols;
	//padding cho mỗi chiều
	int padding_size = gaussian_blur_kernelSize / 2;
	for (int i = padding_size; i < rows - padding_size; ++i)
		for (int j = padding_size; j < cols - padding_size; ++j)
		{
			double s = 0;
			// thực hiện phép convolution
			for (int k = 0; k < gaussian_blur_kernelSize * gaussian_blur_kernelSize; ++k) {
				int padx = k / gaussian_blur_kernelSize;
				int pady = k % gaussian_blur_kernelSize;
				s += gaussian_kernel[k] * (double)(gray_scale.at<uchar>(i - padding_size + padx, j - padding_size + pady));
			}
			//ghi kết quả vào 
			gaussian_blur.at<uchar>(i, j) = processPixel((int)(s));
		}
}
void CannyEdgeDetection::sobel() {
	//kích thước ảnh
	int rows = gaussian_blur.rows;
	int cols = gaussian_blur.cols;

	gaussian_blur.copyTo(grad);
	gaussian_blur.copyTo(grad_x);
	gaussian_blur.copyTo(grad_y);

	//ma trận lưu hướng của biên cạnh
	direction = Mat::zeros(rows,cols, CV_32FC1);

	//padding cho mỗi cạnh để thực hiện sobel
	int padding_size = sobel_size / 2;
	for (int i = padding_size; i < rows - padding_size; ++i)
		for (int j = padding_size; j < cols - padding_size; ++j)
		{
			double sx = 0;
			double sy = 0;
			// thực hiện phép tính chập ở mask_x và mask_y
			for (int k = 0; k < sobel_size* sobel_size; ++k) {
				int padx = k / sobel_size;
				int pady = k % sobel_size;
				sx += sobel_x[k] * (double)(gaussian_blur.at<uchar>(i - padding_size + padx, j - padding_size + pady));
				sy += sobel_y[k] * (double)(gaussian_blur.at<uchar>(i - padding_size + padx, j - padding_size + pady));
			}
			grad_x.at<uchar>(i, j) = processPixel((int)(sx));
			grad_y.at<uchar>(i, j) = processPixel((int)(sy));

			//gradient tại mỗi pixel của ảnh tổng hợp theo gradient x và gradient y
			int tmp = sqrt(sx * sx + sy * sy);
			grad.at<uchar>(i, j) = processPixel(tmp);

			//tính góc tại mỗi pixel
			if (sx == 0) //dùng tan^-1, mẫu số bằng 0 thì gán mẫu số rất nhỏ
				sx = 1e-7;
			double angle = atan(sy / sx) * 180 / PI; //atan trả kết quả theo radian -> đổi về độ
			direction.at<double>(i, j) = angle;
		}
}
void CannyEdgeDetection::non_max_suppression() {
	int rows = image.rows;
	int cols = image.cols;
	grad.copyTo(non_max);


	for (int i = 1; i < rows - 1; ++i)
		for (int j = 1; j < cols - 1; ++j)
		{
			//lấy góc tại mỗi pixel
			double angle = direction.at<double>(i, j);
			uchar q, r;
			//chia trường hợp góc để tìm các pixel gần kề theo biên cạnh 
			//chiều dọc
			if ((angle > -90 && angle <= -67.5) || (angle >= 67.5 && angle < 90))
			{
				q = grad.at<uchar>(i + 1, j);
				r = grad.at<uchar>(i - 1, j);

			}
			//chiều ngang
			else if (angle > -22.5 && angle < 22.5) {
				//else if ((angle >= 0 && angle < 22.5) || (angle >= 67.5 && angle < 90)){
				q = grad.at<uchar>(i, j + 1);
				r = grad.at<uchar>(i, j - 1);

			}
			//-45
			else if (angle > -67.5 && angle <= -22.5) {
				q = grad.at<uchar>(i + 1, j + 1);
				r = grad.at<uchar>(i - 1, j - 1);

			}
			//45
			else //if (angle >= 22.5 && angle < 67.5)
			{
				q = grad.at<uchar>(i + 1, j - 1);
				r = grad.at<uchar>(i - 1, j + 1);
			}

			//so sánh với giá trị pixel gần kề
			if (!(grad.at<uchar>(i, j) >= q && grad.at<uchar>(i, j) >= r))
				non_max.at<uchar>(i, j) = 0;
			else
				non_max.at<uchar>(i, j) = grad.at<uchar>(i, j);
		}

}
void CannyEdgeDetection::threshold() {
	non_max.copyTo(final_image);
	for (int i = 0; i < non_max.rows; ++i)
		for (int j = 0; j < non_max.cols; ++j) {
			//nếu lơn hơn high threshold -> nó là cạnh -> đặt về 255
			if ((non_max.at<uchar>(i, j)) >= upper)
				final_image.at<uchar>(i, j) = 255;
			//nếu nhỏ hơn low threshold, không là cạnh -> đặt về 0
			else if ((non_max.at<uchar>(i, j)) < lower)
				final_image.at<uchar>(i, j) = 0;

			//nằm giữa 2 threshold -> cạnh yếu
			else {
				//kiểm tra xem có gần một pixel là biên cạnh không
				int check_near_edge = 0;

				//lặp qua các ô gần kề ô đang xét
				for (int padx = -1; padx <= 1; ++padx)
					for (int pady = -1; pady <= 1; ++pady)
					{
						//tọa độ ô gần kề
						int x = i + padx;
						int y = j + pady;
						//nếu vượt quá phạm vi lưu trữ của mảng thì bỏ qua
						if (!(x < 0 || y < 0 || x >= non_max.rows || y >= non_max.cols))
						{
							//nếu pixel gần kề là biên cạnh thì bật biến check lên 
							if (non_max.at<uchar>(x, y) >= upper)
								check_near_edge = 1;
						}
					}

				if (check_near_edge)
					final_image.at<uchar>(i, j) = 255;
				else
					final_image.at<uchar>(i, j) = 0;
			}

		}
	showImage(final_image, "Final image - MyCanny");
}

void CannyEdgeDetection::detect() {
	grayscale();
	gaussianBlur();
	sobel();
	non_max_suppression();
	threshold();

	Mat dst;
	Canny(image, dst, lower, upper);
	showImage(dst, "OPENCV Canny");
}

void CannyEdgeDetection::setFinalImage(Mat src) {
	final_image.copyTo(src);
}

CannyEdgeDetection::~CannyEdgeDetection() {
	if (gaussian_kernel)
	{
		delete[] gaussian_kernel;
		gaussian_kernel = nullptr;
	}
	if (sobel_x)
	{
		delete[] sobel_x;
		sobel_x = nullptr;
	}
	if (sobel_y)
	{
		delete[] sobel_y;
		sobel_y = nullptr;
	}

}
