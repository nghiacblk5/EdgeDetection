#include "process.h"

void showImage(Mat image, string s) {
	if (!image.data)
	{
		cout << "Khong the mo anh" << endl;
		return;
	}
	namedWindow(s, WINDOW_AUTOSIZE);
	imshow(s, image);
	waitKey(0);
	return;
}

Mat BGR2Gray(Mat image) {
	Mat image_gray;
	//lấy kích thước của ảnh ban đầu
	int rows = image.rows;
	int cols = image.cols;
	// tạo ma trận chứa dữ liệu của ảnh xám, với 1 kênh màu và các pixel có giá trị từ 0 ->255
	image_gray = Mat(rows, cols, CV_8UC1);
	for (int i = 0; i < rows; ++i)
		for (int j = 0; j < cols; ++j)
		{
			Vec3b pixel_bgr = image.at<Vec3b>(i, j);

			uchar blue = pixel_bgr[0];
			uchar green = pixel_bgr[1];
			uchar red = pixel_bgr[2];
			//công thức tính pixel ảnh xám dựa trên pixel ảnh màu tại 1 vị trí
			image_gray.at<uchar>(i, j) = uchar(0.114 * blue + 0.587 * green + 0.299 * red);
		}
	//hiển thị hình ảnh lên
	return image_gray;
}


uchar processPixel(int k) {
	if (k < 0)
		k = -k;
	if (k > 255)
		return uchar(255);
	return uchar(k);
}





