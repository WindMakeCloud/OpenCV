// 图像金字塔和缩放综合操作
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

#define WINDOW_NAME "程序展示"

void ShowHelpText();

Mat srcImage, dstImage, tmpImage;

int main()
{
	ShowHelpText();

	srcImage = imread("1.jpg");
	if (!srcImage.data)
	{
		cout << "读取图片错误，请确认目录下是否存在指定图片！\n";
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
		case 27 :  // 按键Esc
			return 0;
		case 'a' : // 按键A，调用pyrUp
			pyrUp(tmpImage, dstImage, Size(tmpImage.cols * 2, tmpImage.rows * 2));
			cout << ">A键按下，基于pyrUp函数进行图片放大：图片尺寸 * 2 \n";
			break;
		case 'd' :
			pyrDown(tmpImage, dstImage, Size(tmpImage.cols / 2, tmpImage.rows / 2));
			cout << ">D键按下，基于pyrDown函数进行图片缩小：图片尺寸 / 2 \n";
			break;
		case 'w' :
			resize(tmpImage, dstImage, Size(tmpImage.cols * 2, tmpImage.rows * 2));
			cout << ">W键按下，基于resize函数进行图片放大：图片尺寸 * 2 \n";
			break;
		case 's' :
			resize(tmpImage, dstImage, Size(tmpImage.cols / 2, tmpImage.rows / 2));
			cout << ">S键按下，基于resize函数进行图片缩小：图片尺寸 / 2 \n";
			break;
		}
		imshow(WINDOW_NAME, dstImage);

		// 将dst赋给tmp方便下一次循环
		tmpImage = dstImage;
	}
	return 0;
}

void ShowHelpText()
{
	cout << "\t图像金字塔Pyr和缩放操作Resize示例程序\n\n";
	cout << "\t按键操作说明:\n"
		<< "\t\t【Esc】- 程序退出\n"
		<< "\t\t 【W】 - resize放大2倍\n"
		<< "\t\t 【S】 - resize缩小2倍\n"
		<< "\t\t 【A】 - pyrUp放大2倍\n"
		<< "\t\t 【D】 - pyrDown缩小2倍\n";
}