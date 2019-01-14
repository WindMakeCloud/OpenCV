// 多种重映射：
// 用按键控制四种不同的重映射模式
#include <iostream>
#include <highgui.hpp>
#include <imgproc.hpp>

using namespace cv;
using namespace std;

#define WINDOW_NAME "重映射效果"

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
		cout << "读取图片错误，请确认目录下是否存在指定图片!\n";
		return -1;
	}
	imshow("原图", srcImage);

	dstImage.create(srcImage.size(), srcImage.type());
	map_x.create(srcImage.size(), CV_32FC1);
	map_y.create(srcImage.size(), CV_32FC1);

	namedWindow(WINDOW_NAME);
	imshow(WINDOW_NAME, srcImage);

	// 轮询按键，更新map_x和map_y的值，进行重映射操作并显示效果
	while (1)
	{
		int key = waitKey(0);
		if (key == 27)
		{
			cout << "程序退出…………\n";
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
	// 遍历每一个像素点
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
	cout << "\n\t\t按键操作说明:\n\n"
		<< "\t\t\t按键【Esc】- 退出程序\n"
		<< "\t\t\t按键 【1】 - 第一种映射\n"
		<< "\t\t\t按键 【2】 - 第二种映射\n"
		<< "\t\t\t按键 【3】 - 第三种映射\n"
		<< "\t\t\t按键 【4】 - 第四种映射\n";
}