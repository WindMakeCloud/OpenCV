// canny边缘检测
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main()
{
	Mat image = imread("mao3.jpg");
	imshow("【原始图】canny边缘检测", image);

	Mat dstImage, edge, grayImage;
	
	// 创建与image同类型大小的矩阵
	dstImage.create(image.size(), image.type());

	// 将图像转换为灰度图像
	cvtColor(image, grayImage, COLOR_BGR2GRAY);

	// 使用3*3内核来降噪
	blur(grayImage, edge, Size(3, 3));

	// 运行Canny算子
	Canny(edge, edge, 3, 9, 3);

	// 显示效果图
	imshow("【效果图】canny边缘检测", edge);

	waitKey(0);
    return 0;
}

