// ������ӳ�䣺
// �ð����������ֲ�ͬ����ӳ��ģʽ
#include <iostream>
#include <highgui.hpp>
#include <imgproc.hpp>

using namespace cv;
using namespace std;

#define WINDOW_NAME "��ӳ��Ч��"

Mat srcImage, dstImage;
Mat map_x, map_y;

int update_map(int key);
static void ShowHelpText();

int main()
{
	ShowHelpText();
	srcImage = imread("1.jpg");
	if (!srcImage.data)
	{
		cout << "��ȡͼƬ������ȷ��Ŀ¼���Ƿ����ָ��ͼƬ!\n";
		return -1;
	}
	imshow("ԭͼ", srcImage);

	dstImage.create(srcImage.size(), srcImage.type());
	map_x.create(srcImage.size(), CV_32FC1);
	map_y.create(srcImage.size(), CV_32FC1);

	namedWindow(WINDOW_NAME);
	imshow(WINDOW_NAME, srcImage);

	// ��ѯ����������map_x��map_y��ֵ��������ӳ���������ʾЧ��
	while (1)
	{
		int key = waitKey(0);
		if (key == 27)
		{
			cout << "�����˳���������\n";
			break;
		}

		update_map(key);
		remap(srcImage, dstImage, map_x, map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0));
		imshow(WINDOW_NAME, dstImage);
	}
	return 0;
}

int update_map(int key)
{
	// ����ÿһ�����ص�
	for (int j = 0; j < srcImage.rows; j++)
		for(int i = 0; i < srcImage.cols; i++)
			switch (key)
			{
			case '1' :
				if (i > srcImage.cols*0.25 && i < srcImage.cols*0.75 &&
					j > srcImage.rows*0.25 && j < srcImage.rows*0.75)
				{
					map_x.at<float>(j, i) = static_cast<float>(2 * (i - srcImage.cols*0.25) + 0.5);
					map_y.at<float>(j, i) = static_cast<float>(2 * (j - srcImage.rows*0.25) + 0.5);
				}
				else
				{
					map_x.at<float>(j, i) = 0;
					map_y.at<float>(j, i) = 0;
				}
				break;
			case '2' :
				map_x.at<float>(j, i) = static_cast<float>(i);
				map_y.at<float>(j, i) = static_cast<float>(srcImage.rows - j);
				break;
			case '3' :
				map_x.at<float>(j, i) = static_cast<float>(srcImage.cols - i);
				map_y.at<float>(j, i) = static_cast<float>(j);
				break;
			case '4' :
				map_x.at<float>(j, i) = static_cast<float>(srcImage.cols - i);
				map_y.at<float>(j, i) = static_cast<float>(srcImage.rows - j);
				break;
			}

	return 1;
}

static void ShowHelpText()
{
	cout << "\n\t\t��������˵��:\n\n"
		<< "\t\t\t������Esc��- �˳�����\n"
		<< "\t\t\t���� ��1�� - ��һ��ӳ��\n"
		<< "\t\t\t���� ��2�� - �ڶ���ӳ��\n"
		<< "\t\t\t���� ��3�� - ������ӳ��\n"
		<< "\t\t\t���� ��4�� - ������ӳ��\n";
}