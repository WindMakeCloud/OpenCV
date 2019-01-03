// 图像对比度、亮度的调整
// 用两个轨迹条分别控制对比度和亮度值

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

static void on_ContrastAndBright(int, void*);

int g_nContrastValue;  // 对比度值
int g_nBrightValue;    // 亮度值
Mat g_srcImage, g_dstImage;

int main()
{
	// 读取图像
	g_srcImage = imread("1.jpg");
	if (!g_srcImage.data)
	{
		cout << "读取图像失败，确认当前目录是否有指定图片！\n";
		return -1;
	}
	g_dstImage = Mat::zeros(g_srcImage.size(), g_srcImage.type());

	// 设定对比度和亮度的初值
	g_nContrastValue = 80;
	g_nBrightValue = 80;

	// 创建效果图窗口
	namedWindow("【效果图】", 1);

	// 创建轨迹条
	createTrackbar("对比度", "【效果图】", &g_nContrastValue, 300, on_ContrastAndBright);
	createTrackbar("亮 度", "【效果图】", &g_nBrightValue, 200, on_ContrastAndBright);

	// 进行回调函数初始化
	on_ContrastAndBright(g_nContrastValue, 0);
	on_ContrastAndBright(g_nBrightValue, 0);

	// 按下q健时，程序退出
	while (char(waitKey(1)) != 'q') { }
	return 0;
}

// on_ContrastAndBright()函数：
// 该表图像对比度和亮度的回调函数
static void on_ContrastAndBright(int, void*)
{
	// 创建窗口
	namedWindow("【原始图】", 1);

	// 三个for循环，执行运算g_dstImage(i,j) = a*g_srcImage(i,j) + b
	for (int y = 0; y < g_srcImage.rows; y++)
		for (int x = 0; x < g_srcImage.cols; x++)
			for (int c = 0; c < 3; c++)
				g_dstImage.at<Vec3b>(y, x)[c] =
				saturate_cast<uchar>((g_nContrastValue*0.01)*(g_srcImage.at<Vec3b>(y, x)[c]) + g_nBrightValue);

	// 显示图像
	imshow("【原始图】", g_srcImage);
	imshow("【效果图】", g_dstImage);
}