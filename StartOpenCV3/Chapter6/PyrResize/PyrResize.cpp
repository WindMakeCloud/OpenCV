// ͼ��������������ۺϲ���
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

#define WINDOW_NAME "����չʾ"

void ShowHelpText();

Mat srcImage, dstImage, tmpImage;

int main()
{
	ShowHelpText();

	srcImage = imread("1.jpg");
	if (!srcImage.data)
	{
		cout << "��ȡͼƬ������ȷ��Ŀ¼���Ƿ����ָ��ͼƬ��\n";
		return -1;
	}

	namedWindow(WINDOW_NAME);
	imshow(WINDOW_NAME, srcImage);

	tmpImage = srcImage;
	dstImage = tmpImage;

	int key = 0;

	while (1)
	{
		key = waitKey(0);

		switch (key)
		{
		case 27 :  // ����Esc
			return 0;
		case 'a' : // ����A������pyrUp
			pyrUp(tmpImage, dstImage, Size(tmpImage.cols * 2, tmpImage.rows * 2));
			cout << ">A�����£�����pyrUp��������ͼƬ�Ŵ�ͼƬ�ߴ� * 2 \n";
			break;
		case 'd' :
			pyrDown(tmpImage, dstImage, Size(tmpImage.cols / 2, tmpImage.rows / 2));
			cout << ">D�����£�����pyrDown��������ͼƬ��С��ͼƬ�ߴ� / 2 \n";
			break;
		case 'w' :
			resize(tmpImage, dstImage, Size(tmpImage.cols * 2, tmpImage.rows * 2));
			cout << ">W�����£�����resize��������ͼƬ�Ŵ�ͼƬ�ߴ� * 2 \n";
			break;
		case 's' :
			resize(tmpImage, dstImage, Size(tmpImage.cols / 2, tmpImage.rows / 2));
			cout << ">S�����£�����resize��������ͼƬ��С��ͼƬ�ߴ� / 2 \n";
			break;
		}
		imshow(WINDOW_NAME, dstImage);

		// ��dst����tmp������һ��ѭ��
		tmpImage = dstImage;
	}
	return 0;
}

void ShowHelpText()
{
	cout << "\tͼ�������Pyr�����Ų���Resizeʾ������\n\n";
	cout << "\t��������˵��:\n"
		<< "\t\t��Esc��- �����˳�\n"
		<< "\t\t ��W�� - resize�Ŵ�2��\n"
		<< "\t\t ��S�� - resize��С2��\n"
		<< "\t\t ��A�� - pyrUp�Ŵ�2��\n"
		<< "\t\t ��D�� - pyrDown��С2��\n";
}