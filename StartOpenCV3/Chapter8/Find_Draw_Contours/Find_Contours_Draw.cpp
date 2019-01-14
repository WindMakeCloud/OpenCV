// 查找并绘制轮廓图
// 使用blur()和Canny()函数，结合轨迹条
// 动态地检测出图像轮廓
#include <opencv.hpp>
#include <highgui.hpp>
#include <imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

#define WINDOW_NAME1 "原图窗口"
#define WINDOW_NAME2 "轮廓图窗口"

Mat g_srcImage, g_grayImage;
int g_Thresh = 80;
int g_Thresh_max = 255;
RNG g_rng(12345);
Mat g_cannyMat_output;
vector<vector<Point> > g_Contours;
vector<Vec4i> g_Hierarchy;

void on_ThreshChange(int, void*);

int main()
{
	g_srcImage = imread("1.jpg", 1);
	if (!g_srcImage.data)
	{
		cout << "读取图片错误，请确认目录下是否存在指定图片！\n";
		return -1;
	}

	// 转换成灰度图并降噪
	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
	blur(g_grayImage, g_grayImage, Size(3, 3));

	// 创建窗口
	namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME1, g_srcImage);

	namedWindow(WINDOW_NAME2);
	// 创建滚动条并初始化
	createTrackbar("Canny阈值", WINDOW_NAME2, &g_Thresh, g_Thresh_max, on_ThreshChange);
	on_ThreshChange(0, 0);

	waitKey(0);
	return 0;
}


void on_ThreshChange(int, void*)
{
	// Canny算子检测边缘
	Canny(g_grayImage, g_cannyMat_output, g_Thresh, g_Thresh * 2, 3);
	// 寻找轮廓
	findContours(g_cannyMat_output, g_Contours, g_Hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
	// 绘出轮廓
	Mat drawing = Mat::zeros(g_cannyMat_output.size(), CV_8UC3);
	for (int i = 0; i < g_Contours.size(); i++)
	{
		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));  // 任意值
		drawContours(drawing, g_Contours, i, color, 2, 8, g_Hierarchy, 0, Point());
	}
	// 显示效果图
	imshow(WINDOW_NAME2, drawing);
}