// HoughLinesP函数的基础上，
// 添加控制threshold的滚动条，
// 动态地控制霍夫线变换检测的线条多少
#include <opencv.hpp>
#include <highgui.hpp>
#include <imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat srcImage, grayImage, midImage, dstImage;
vector<Vec4i> lines;

// 变量接收的Trackbar位置参数
int g_nthreshold = 100;

static void on_HoughLinesP(int, void*);

int main()
{
	srcImage = imread("1.jpg");
	if (!srcImage.data)
	{
		cout << "读取图片错误，请确认目录下是否存在指定图片!\n";
		return -1;
	}

	namedWindow("原图");
	imshow("原图", srcImage);

	namedWindow("霍夫线变换效果图");
	createTrackbar("参数值：", "霍夫线变换效果图", &g_nthreshold, 200, on_HoughLinesP);
	
	// 进行Canny边缘检测
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
	blur(grayImage, midImage, Size(3, 3));
	Canny(midImage, midImage, 30, 90, 3);
	
	dstImage.create(midImage.size(), midImage.type());
	// 调用一次回调函数，调用一次HoughLinesP函数
	on_HoughLinesP(g_nthreshold, 0);
	HoughLinesP(midImage, lines, 1, CV_PI / 180, 80, 50, 10);
	// 显示效果图
	imshow("霍夫线变换效果图", dstImage);

	waitKey(0);
	return 0;
}

static void on_HoughLinesP(int, void*)
{
	// 定义局部变量存储全局变量
	Mat mid = midImage.clone();
	Mat dst = dstImage.clone();
	// 调用HoughLinesP()
	vector<Vec4i> mylines;
	HoughLinesP(mid, mylines, 1, CV_PI / 180, g_nthreshold + 1, 50, 10);
	// 绘制每一条线段
	for (size_t i = 0; i < mylines.size(); i++)
	{
		Vec4i l = mylines[i];
		line(dst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(23, 190, 55), 1, LINE_AA);
	}
	// 显示图像
	imshow("霍夫线变换效果图", dst);
}