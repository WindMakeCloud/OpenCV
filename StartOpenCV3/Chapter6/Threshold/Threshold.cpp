// ��ֵ����
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

#define WINDOW_NAME "���򴰿�"

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
		cout << "��ȡͼƬ������ȷ��Ŀ¼���Ƿ����ָ��ͼƬ��\n";
		return -1;
	}

	// ����һ��ԭͼ�ĻҶ�ͼ
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);

	namedWindow("ԭͼ");
	imshow("ԭͼ", srcImage);

	namedWindow(WINDOW_NAME);
	// �����켣��
	createTrackbar("ģʽ", WINDOW_NAME, &ThresholdType, 4, on_Threshold);
	createTrackbar("����", WINDOW_NAME, &ThresholdValue, 255, on_Threshold);

	// ��ʼ���Զ������ֵ�ص�����
	on_Threshold(0, 0);

	// ����Esc�������˳�
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
	cout << "\t\t��ֵ����ʾ������\n\n"
		<< "\t\tģʽ�켣��˵����\n"
		<< "\t\t\t��Esc��- �˳�����\n"
		<< "\t\t\t ��0�� - ��������ֵ\n"
		<< "\t\t\t ��1�� - ����������ֵ\n"
		<< "\t\t\t ��2�� - �ض���ֵ\n"
		<< "\t\t\t ��3�� - ����ֵ��Ϊ0\n"
		<< "\t\t\t ��4�� - ��ֵ��Ϊ0\n";
}