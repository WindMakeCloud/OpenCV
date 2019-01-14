// 查找和绘制图像轮廓矩
// moments()矩的计算
// contourArea()轮廓面积计算
// arcLength()轮廓长度计算
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

#define WINDOW_NAME1 "原始图"
#define WINDOW_NAME2 "轮廓图"

Mat g_srcImage, g_grayImage;
int g_Thresh = 100;
int g_MaxThresh = 255;
RNG g_rng(12345);
Mat g_cannyMat_output;
vector<vector<Point>> g_Contours;
vector<Vec4i> g_Hierarchy;

void on_ThreshChange(int, void*);

int main()
{
	g_srcImage = imread("1.jpg", 1);
	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
	blur(g_grayImage, g_grayImage, Size(3, 3));

	namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME1, g_srcImage);

	createTrackbar("阈值", WINDOW_NAME1, &g_Thresh, g_MaxThresh, on_ThreshChange);
	on_ThreshChange(0, 0);

	waitKey(0);
	return 0;
}

void on_ThreshChange(int, void*)
{
	// canny边缘检测
	Canny(g_grayImage, g_cannyMat_output, g_Thresh, g_Thresh * 2, 3);
	// 找到轮廓
	findContours(g_cannyMat_output, g_Contours, g_Hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
	// 计算矩
	vector<Moments> mu(g_Contours.size());
	for (unsigned int i = 0; i < g_Contours.size(); i++)
		mu[i] = moments(g_Contours[i], false);
	// 计算中心矩
	vector<Point2f> mc(g_Contours.size());
	for (unsigned int i = 0; i < g_Contours.size(); i++)
		mc[i] = Point2f(static_cast<float>(mu[i].m10 / mu[i].m00), static_cast<float>(mu[i].m01 / mu[i].m00));
	// 绘制轮廓
	Mat drawing = Mat::zeros(g_cannyMat_output.size(), CV_8UC3);
	for (unsigned int i = 0; i < g_Contours.size(); i++)
	{
		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
		drawContours(drawing, g_Contours, i, color, 2, 8, g_Hierarchy, 0, Point());
		circle(drawing, mc[i], 4, color, -1, 8, 0);
	}
	namedWindow(WINDOW_NAME2, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME2, drawing);

	// 通过m00计算轮廓面积并和opencv函数比较
	cout << "\t 输出内容：面积和轮廓长度\n";
	for (unsigned int i = 0; i < g_Contours.size(); i++)
	{
		cout << " >通过m00计算出轮廓" << i << "的面积：" << "(M_00) = " << mu[i].m00 << endl;
		cout << "  OpenCV函数计算出的面积：" << contourArea(g_Contours[i]) << ", "
			<< "长度：" << arcLength(g_Contours[i], true) << endl << endl;
	}
}