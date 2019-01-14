// HoughLinesP�����Ļ����ϣ�
// ��ӿ���threshold�Ĺ�������
// ��̬�ؿ��ƻ����߱任������������
#include <opencv.hpp>
#include <highgui.hpp>
#include <imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat srcImage, grayImage, midImage, dstImage;
vector<Vec4i> lines;

// �������յ�Trackbarλ�ò���
int g_nthreshold = 100;

static void on_HoughLinesP(int, void*);

int main()
{
	srcImage = imread("1.jpg");
	if (!srcImage.data)
	{
		cout << "��ȡͼƬ������ȷ��Ŀ¼���Ƿ����ָ��ͼƬ!\n";
		return -1;
	}

	namedWindow("ԭͼ");
	imshow("ԭͼ", srcImage);

	namedWindow("�����߱任Ч��ͼ");
	createTrackbar("����ֵ��", "�����߱任Ч��ͼ", &g_nthreshold, 200, on_HoughLinesP);
	
	// ����Canny��Ե���
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
	blur(grayImage, midImage, Size(3, 3));
	Canny(midImage, midImage, 30, 90, 3);
	
	dstImage.create(midImage.size(), midImage.type());
	// ����һ�λص�����������һ��HoughLinesP����
	on_HoughLinesP(g_nthreshold, 0);
	HoughLinesP(midImage, lines, 1, CV_PI / 180, 80, 50, 10);
	// ��ʾЧ��ͼ
	imshow("�����߱任Ч��ͼ", dstImage);

	waitKey(0);
	return 0;
}

static void on_HoughLinesP(int, void*)
{
	// ����ֲ������洢ȫ�ֱ���
	Mat mid = midImage.clone();
	Mat dst = dstImage.clone();
	// ����HoughLinesP()
	vector<Vec4i> mylines;
	HoughLinesP(mid, mylines, 1, CV_PI / 180, g_nthreshold + 1, 50, 10);
	// ����ÿһ���߶�
	for (size_t i = 0; i < mylines.size(); i++)
	{
		Vec4i l = mylines[i];
		line(dst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(23, 190, 55), 1, LINE_AA);
	}
	// ��ʾͼ��
	imshow("�����߱任Ч��ͼ", dst);
}