// 边缘检测综合示例
// 包括Canny，Sobel，Scharr三种函数
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// 定义全局变量，原图，原图的灰度版，目标图
Mat srcImage, grayImage, dstImage;
// Canny边缘检测相关变量
Mat cannyDetectEdge;
int cannyLowThreshold = 1;
// Sobel边缘检测相关变量
Mat sobelGradient_x, sobelGradient_y;
Mat sobelAbsGradient_x, sobelAbsGradient_y;
int sobelKernelSize = 1;
// Scharr滤波器变量
Mat scharrGradient_x, scharrGradient_y;
Mat scharrAbsGradient_x, scharrAbsGradient_y;

// 全局函数声明
static void on_Canny(int, void*);
static void on_Sobel(int, void*);
void Scharr();

int main()
{
	srcImage = imread("1.jpg");
	if (!srcImage.data)
	{
		cout << "图片读取失败，请确认目录下是否存在指定图片！\n";
		return -1;
	}
	namedWindow("原图");
	imshow("原图", srcImage);

	dstImage.create(srcImage.size(), srcImage.type());
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);

	namedWindow("Canny边缘检测");
	namedWindow("Sobel边缘检测");

	createTrackbar("参数值:", "Canny边缘检测", &cannyLowThreshold, 120, on_Canny);
	createTrackbar("参数值:", "Sobel边缘检测", &sobelKernelSize, 3, on_Sobel);
	// 调用回调函数
	on_Canny(0, 0);
	on_Sobel(0, 0);

	Scharr();

	while ((char(waitKey(1)) != 'q')) { }
	return 0;
}

static void on_Canny(int, void*)
{
	// 先使用3*3内核来降噪
	blur(grayImage, cannyDetectEdge, Size(3, 3));
	// 运行Canny算子
	Canny(cannyDetectEdge, cannyDetectEdge, cannyLowThreshold, cannyLowThreshold * 3, 3);
	// 先将dstImage内所有元素设置为0
	dstImage = Scalar::all(0);
	// 使用canny算子输出的边缘图cannyDetectEdge作为掩码，来将原图srcImage拷到目标图dstImage
	srcImage.copyTo(dstImage, cannyDetectEdge);
	// 显示效果图
	imshow("Canny边缘检测", dstImage);
}

static void on_Sobel(int, void*)
{
	// 求x方向梯度
	Sobel(srcImage, sobelGradient_x, CV_16S, 1, 0, (2 * sobelKernelSize + 1), 1, 1, BORDER_DEFAULT);
	// 求y方向梯度
	Sobel(srcImage, sobelGradient_y, CV_16S, 0, 1, (2 * sobelKernelSize + 1), 1, 1, BORDER_DEFAULT);
	// 计算绝对值，并将结果转换成8位
	convertScaleAbs(sobelGradient_x, sobelAbsGradient_x);
	convertScaleAbs(sobelGradient_y, sobelAbsGradient_y);
	// 合并梯度
	addWeighted(sobelAbsGradient_x, 0.5, sobelAbsGradient_y, 0.5, 0, dstImage);
	// 显示效果图
	imshow("Sobel边缘检测", dstImage);
}

void Scharr()
{
	// x,y方向梯度
	Scharr(srcImage, scharrGradient_x, CV_16S, 1, 0, 1, 0, BORDER_DEFAULT);
	Scharr(srcImage, scharrGradient_y, CV_16S, 0, 1, 1, 0, BORDER_DEFAULT);
	// 计算绝对值，将结果转换成8位
	convertScaleAbs(scharrGradient_x, scharrAbsGradient_x);
	convertScaleAbs(scharrGradient_y, scharrAbsGradient_y);
	// 合并梯度
	addWeighted(scharrAbsGradient_x, 0.5, scharrAbsGradient_y, 0.5, 0, dstImage);
	// 显示效果图
	imshow("Scharr滤波器", dstImage);
}