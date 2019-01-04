// 5种图像滤波方法结合轨迹条演示滤波效果
// 线性滤波：方框滤波，均值滤波，高斯滤波
// 非线性滤波：中值滤波，双边滤波

#include <core.hpp>
#include <highgui.hpp>
#include <imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// 全局变量的声明
Mat srcImage, dstImage1, dstImage2, dstImage3, dstImage4, dstImage5;
int BoxFilterValue = 6;         // 方框滤波内核值
int MeanBlurValue = 10;         // 均值滤波内核值
int GaussianBlurValue = 6;      // 高斯滤波内核值
int MedianBlueValue = 10;       // 中值滤波参数值
int BilateralFilterValue = 10;  // 双边滤波参数值

// 各滤波方法轨迹条回调函数
static void on_BoxFilter(int, void*);
static void on_MeanBlur(int, void*);
static void on_GaussianBlur(int, void*);
static void on_MedianBlur(int, void*);
static void on_BilateralFilter(int, void*);

int main()
{
	// 载入原图
	srcImage = imread("1.jpg");
	if (!srcImage.data)
	{
		cout << "读取图片错误，请确认目录下有指定图片！\n";
		return -1;
	}

	// 复制原图到5个Mat中
	dstImage1 = srcImage.clone();
	dstImage2 = srcImage.clone();
	dstImage3 = srcImage.clone();
	dstImage4 = srcImage.clone();
	dstImage5 = srcImage.clone();

	// 显示原图
	namedWindow("原图");
	imshow("原图", srcImage);

	// 方框滤波
	namedWindow("方框滤波");
	createTrackbar("内核值：", "方框滤波", &BoxFilterValue, 50, on_BoxFilter);
	on_BoxFilter(BoxFilterValue, 0);

	// 均值滤波
	namedWindow("均值滤波");
	createTrackbar("内核值：", "均值滤波", &MeanBlurValue, 50, on_MeanBlur);
	on_MeanBlur(MeanBlurValue, 0);

	// 高斯滤波
	namedWindow("高斯滤波");
	createTrackbar("内核值：", "高斯滤波", &GaussianBlurValue, 50, on_GaussianBlur);
	on_GaussianBlur(GaussianBlurValue, 0);

	// 中值滤波
	namedWindow("中值滤波");
	createTrackbar("参数值：", "中值滤波", &MedianBlueValue, 50, on_MedianBlur);
	on_MedianBlur(MedianBlueValue, 0);

	// 双边滤波
	namedWindow("双边滤波");
	createTrackbar("参数值：", "双边滤波", &BilateralFilterValue, 50, on_BilateralFilter);
	on_BilateralFilter(BilateralFilterValue, 0);

	// 按q键程序结束
	cout << "按q键程序结束!\n";
	while (char(waitKey(1)) != 'q') { }
	return 0;
}

static void on_BoxFilter(int, void*)
{
	boxFilter(srcImage, dstImage1, -1, Size(BoxFilterValue + 1, BoxFilterValue + 1));
	imshow("方框滤波", dstImage1);
}

static void on_MeanBlur(int, void*)
{
	blur(srcImage, dstImage2, Size(MeanBlurValue + 1, MeanBlurValue + 1), Point(-1, -1));
	imshow("均值滤波", dstImage2);
}

static void on_GaussianBlur(int, void*)
{
	GaussianBlur(srcImage, dstImage3, Size(GaussianBlurValue * 2 + 1, GaussianBlurValue * 2 + 1), 0, 0);
	imshow("高斯滤波", dstImage3);
}

static void on_MedianBlur(int, void*)
{
	medianBlur(srcImage, dstImage4, MedianBlueValue * 2 + 1);
	imshow("中值滤波", dstImage4);
}

static void on_BilateralFilter(int, void*)
{
	bilateralFilter(srcImage, dstImage5, BilateralFilterValue, BilateralFilterValue * 2, BilateralFilterValue / 2);
	imshow("双边滤波", dstImage5);
}