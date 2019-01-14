// ��Ϲ켣��������������ֵ���õ���ͬ��͹�����Ч��ͼ
#include <highgui.hpp>
#include <imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

#define WINDOW_NAME1 "ԭʼͼ����"
#define WINDOW_NAME2 "͹�����Ч��ͼ����"

Mat g_srcImage, g_grayImage;
int g_Thresh = 50;
int g_maxThresh = 255;
RNG g_rng(12345);
Mat srcImage_copy = g_srcImage.clone();
Mat g_thresholdImage_output;
vector<vector<Point> > g_Contours;
vector<Vec4i> g_Hierarchy;

void on_ThreshChange(int, void*);

int main()
{
	g_srcImage = imread("1.jpg", 1);

	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
	blur(g_grayImage, g_grayImage, Size(3, 3));

	namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME1, g_srcImage);

	cvNamedWindow(WINDOW_NAME2, WINDOW_AUTOSIZE);
	createTrackbar("��ֵ", WINDOW_NAME2, &g_Thresh, g_maxThresh, on_ThreshChange);
	on_ThreshChange(0, 0);

	waitKey(0);
	return 0;
}

void on_ThreshChange(int, void*)
{
	// ��ͼ����ж�ֵ����������ֵ
	threshold(g_grayImage, g_thresholdImage_output, g_Thresh, 255, THRESH_BINARY);
	// Ѱ������
	findContours(g_thresholdImage_output, g_Contours, g_Hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
	// ����ÿ��������Ѱ����͹��
	vector<vector<Point> > hull(g_Contours.size());
	for (unsigned int i = 0; i < g_Contours.size(); i++)
		convexHull(Mat(g_Contours[i]), hull[i], false);
	// ����������͹��
	Mat drawing = Mat::zeros(g_thresholdImage_output.size(), CV_8UC3);
	for (unsigned int i = 0; i < g_Contours.size(); i++)
	{
		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
		drawContours(drawing, g_Contours, i, color, 1, 8, vector<Vec4i>(), 0, Point());
		drawContours(drawing, hull, i, color, 1, 8, vector<Vec4i>(), 0, Point());
	}
	// ��ʾЧ��ͼ
	imshow(WINDOW_NAME2, drawing);
}