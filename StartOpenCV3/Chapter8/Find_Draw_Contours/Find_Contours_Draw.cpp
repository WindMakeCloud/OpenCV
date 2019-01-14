// ���Ҳ���������ͼ
// ʹ��blur()��Canny()��������Ϲ켣��
// ��̬�ؼ���ͼ������
#include <opencv.hpp>
#include <highgui.hpp>
#include <imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

#define WINDOW_NAME1 "ԭͼ����"
#define WINDOW_NAME2 "����ͼ����"

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
		cout << "��ȡͼƬ������ȷ��Ŀ¼���Ƿ����ָ��ͼƬ��\n";
		return -1;
	}

	// ת���ɻҶ�ͼ������
	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
	blur(g_grayImage, g_grayImage, Size(3, 3));

	// ��������
	namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME1, g_srcImage);

	namedWindow(WINDOW_NAME2);
	// ��������������ʼ��
	createTrackbar("Canny��ֵ", WINDOW_NAME2, &g_Thresh, g_Thresh_max, on_ThreshChange);
	on_ThreshChange(0, 0);

	waitKey(0);
	return 0;
}


void on_ThreshChange(int, void*)
{
	// Canny���Ӽ���Ե
	Canny(g_grayImage, g_cannyMat_output, g_Thresh, g_Thresh * 2, 3);
	// Ѱ������
	findContours(g_cannyMat_output, g_Contours, g_Hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
	// �������
	Mat drawing = Mat::zeros(g_cannyMat_output.size(), CV_8UC3);
	for (int i = 0; i < g_Contours.size(); i++)
	{
		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));  // ����ֵ
		drawContours(drawing, g_Contours, i, color, 2, 8, g_Hierarchy, 0, Point());
	}
	// ��ʾЧ��ͼ
	imshow(WINDOW_NAME2, drawing);
}