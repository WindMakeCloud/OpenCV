// ��ˮ���㷨ʾ��
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

#define WINDOW_NAME "���򴰿�1"

Mat g_maskImage, g_srcImage;
Point prevPt(-1, -1);

static void on_Mouse(int event, int x, int y, int flags, void*);

int main()
{
	g_srcImage = imread("1.jpg", 1);
	imshow(WINDOW_NAME, g_srcImage);
	Mat srcImage, grayImage;
	g_srcImage.copyTo(srcImage);
	cvtColor(g_srcImage, g_maskImage, COLOR_BGR2GRAY);
	cvtColor(g_maskImage, grayImage, COLOR_GRAY2BGR);
	g_maskImage = Scalar::all(0);

	setMouseCallback(WINDOW_NAME, on_Mouse, 0);

	// ��ѯ���������д���
	while (1)
	{
		int c = waitKey(0);
		if ((char)c == 27)
			break;

		// ����Ϊ'2'ʱ���ָ�ԭͼ
		if ((char)c == '2')
		{
			g_maskImage = Scalar::all(0);
			srcImage.copyTo(g_srcImage);
			imshow(WINDOW_NAME, g_srcImage);
		}

		// ����Ϊ'1'��ո�ʱ�����д���
		if ((char)c == '1' || (char)c == ' ')
		{
			int i, j, compCount = 0;
			vector<vector<Point> > contours;
			vector<Vec4i> hierarchy;
			findContours(g_maskImage, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
			if (contours.empty())
				continue;

			Mat maskImage(g_maskImage.size(), CV_32S);
			maskImage = Scalar::all(0);
			for (int index = 0; index >= 0; index = hierarchy[index][0], compCount++)
				drawContours(maskImage, contours, index, Scalar::all(compCount + 1), -1, 8, hierarchy, INT_MAX);
			if (compCount == 0)
				continue;
			vector<Vec3b> colorTab;
			for (i = 0; i < compCount; i++)
			{
				int b = theRNG().uniform(0, 255);
				int g = theRNG().uniform(0, 255);
				int r = theRNG().uniform(0, 255);
				colorTab.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
			}

			double dTime = (double)getTickCount();
			watershed(srcImage, maskImage);
			dTime = (double)getTickCount() - dTime;
			cout << "\t ����ʱ�� = " << dTime * 1000. / getTickFrequency();

			// ˫��ѭ��������ˮ��ͼ���������watershedImage��
			Mat watershedImage(maskImage.size(), CV_8UC3);
			for (i = 0; i < maskImage.rows; i++)
				for (j = 0; j < maskImage.cols; j++)
				{
					int index = maskImage.at<int>(i, j);
					if (index == -1)
						watershedImage.at<Vec3b>(i, j) = Vec3b(255, 255, 255);
					else if (index <= 0 || index > compCount)
						watershedImage.at<Vec3b>(i, j) = Vec3b(0, 0, 0);
					else
						watershedImage.at<Vec3b>(i, j) = colorTab[index - 1];
				}
			// ��ϻҶ�ͼ�ͷ�ˮ��Ч��ͼ����ʾ���յĴ���
			watershedImage = watershedImage * 0.5 + grayImage * 0.5;
			imshow("watershed", watershedImage);
		}
	}
	return 0;
}

static void on_Mouse(int event, int x, int y, int flags, void*)
{
	// ��겻�ڴ���
	if (x < 0 || x >= g_srcImage.cols || y < 0 || y >= g_srcImage.rows)
		return;
	// ���������������Ϣ
	if (event == EVENT_LBUTTONUP || !(flags & EVENT_FLAG_LBUTTON))
		prevPt = Point(-1, -1);
	else if (event == EVENT_LBUTTONDOWN)
		prevPt == Point(x, y);
	// ���������²��ƶ������Ƴ���ɫ����
	else if (event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON))
	{
		Point pt(x, y);
		if (prevPt.x < 0)
			prevPt = pt;
		line(g_maskImage, prevPt, pt, Scalar::all(255), 5, 8, 0);
		line(g_srcImage, prevPt, pt, Scalar::all(255), 5, 8, 0);
		prevPt = pt;
		imshow(WINDOW_NAME, g_srcImage);
	}
}