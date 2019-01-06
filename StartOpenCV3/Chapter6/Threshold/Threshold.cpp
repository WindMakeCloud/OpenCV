// 阈值操作
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

#define WINDOW_NAME "程序窗口"

int ThresholdValue = 100;
int ThresholdType = 3;
Mat srcImage, grayImage, dstImage;

void ShowHelpText();
void on_Threshold(int, void*);

int main()
{
	ShowHelpText();

	srcImage = imread("1.jpg");
	if (!srcImage.data)
	{
		cout << "读取图片错误，请确认目录下是否存在指定图片！\n";
		return -1;
	}

	// 存留一份原图的灰度图
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);

	namedWindow("原图");
	imshow("原图", srcImage);

	namedWindow(WINDOW_NAME);
	// 创建轨迹条
	createTrackbar("模式", WINDOW_NAME, &ThresholdType, 4, on_Threshold);
	createTrackbar("参数", WINDOW_NAME, &ThresholdValue, 255, on_Threshold);

	// 初始化自定义的阈值回调函数
	on_Threshold(0, 0);

	// 按下Esc，程序退出
	while (1)
	{
		int key;
		key = waitKey(0);
		if ((char)key == 27)
			break;
	}
	return 0;
}

void on_Threshold(int, void*)
{
	threshold(grayImage, dstImage, ThresholdValue, 255, ThresholdType);

	imshow(WINDOW_NAME, dstImage);
}

void ShowHelpText()
{
	cout << "\t\t阈值操作示例程序\n\n"
		<< "\t\t模式轨迹条说明：\n"
		<< "\t\t\t【Esc】- 退出程序\n"
		<< "\t\t\t 【0】 - 二进制阈值\n"
		<< "\t\t\t 【1】 - 反二进制阈值\n"
		<< "\t\t\t 【2】 - 截断阈值\n"
		<< "\t\t\t 【3】 - 反阈值化为0\n"
		<< "\t\t\t 【4】 - 阈值化为0\n";
}