// ͼ��Աȶȡ����ȵĵ���
// �������켣���ֱ���ƶԱȶȺ�����ֵ

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

static void on_ContrastAndBright(int, void*);

int g_nContrastValue;  // �Աȶ�ֵ
int g_nBrightValue;    // ����ֵ
Mat g_srcImage, g_dstImage;

int main()
{
	// ��ȡͼ��
	g_srcImage = imread("1.jpg");
	if (!g_srcImage.data)
	{
		cout << "��ȡͼ��ʧ�ܣ�ȷ�ϵ�ǰĿ¼�Ƿ���ָ��ͼƬ��\n";
		return -1;
	}
	g_dstImage = Mat::zeros(g_srcImage.size(), g_srcImage.type());

	// �趨�ԱȶȺ����ȵĳ�ֵ
	g_nContrastValue = 80;
	g_nBrightValue = 80;

	// ����Ч��ͼ����
	namedWindow("��Ч��ͼ��", 1);

	// �����켣��
	createTrackbar("�Աȶ�", "��Ч��ͼ��", &g_nContrastValue, 300, on_ContrastAndBright);
	createTrackbar("�� ��", "��Ч��ͼ��", &g_nBrightValue, 200, on_ContrastAndBright);

	// ���лص�������ʼ��
	on_ContrastAndBright(g_nContrastValue, 0);
	on_ContrastAndBright(g_nBrightValue, 0);

	// ����q��ʱ�������˳�
	while (char(waitKey(1)) != 'q') { }
	return 0;
}

// on_ContrastAndBright()������
// �ñ�ͼ��ԱȶȺ����ȵĻص�����
static void on_ContrastAndBright(int, void*)
{
	// ��������
	namedWindow("��ԭʼͼ��", 1);

	// ����forѭ����ִ������g_dstImage(i,j) = a*g_srcImage(i,j) + b
	for (int y = 0; y < g_srcImage.rows; y++)
		for (int x = 0; x < g_srcImage.cols; x++)
			for (int c = 0; c < 3; c++)
				g_dstImage.at<Vec3b>(y, x)[c] =
				saturate_cast<uchar>((g_nContrastValue*0.01)*(g_srcImage.at<Vec3b>(y, x)[c]) + g_nBrightValue);

	// ��ʾͼ��
	imshow("��ԭʼͼ��", g_srcImage);
	imshow("��Ч��ͼ��", g_dstImage);
}