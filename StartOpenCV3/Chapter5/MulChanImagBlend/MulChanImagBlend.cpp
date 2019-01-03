// 分离颜色通道&多通道图像混合
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

bool MulChanImagBlend();

int main()
{
	system("color 9F");

	if (MulChanImagBlend())
		cout << "运行成功，得到需要的图像！\n";

	waitKey(0);
	return 0;
}

bool MulChanImagBlend()
{
	// 定义相关变量
	Mat srcImage;
	Mat logoImage;
	vector<Mat> channels;
	Mat imageBlueChannel;

	// 蓝色通道部分
	// 多通道混合-蓝色分量部分
	// 1. 读入图片
	logoImage = imread("dota_logo.jpg", 0);
	srcImage = imread("dota_jugg.jpg");

	if (!logoImage.data)
	{
		cout << "读取logoImage错误！\n";
		return false;
	}
	if (!srcImage.data)
	{
		cout << "读取srcImage错误！\n";
		return false;
	}

	// 2.把三通道图像转换成3个单通道图像
	split(srcImage, channels);

	// 3. 将原图的蓝色通道引用返回给imageBlueChannel，是引用，两者等价，改变一个另一个也改变
	imageBlueChannel = channels.at(0);

	// 4. 将原图的蓝色通道(500,250)坐标右下方的一块区域和logo图进行加权操作，
	// 将得到的混合结果存到imageBlueChannel中
	addWeighted(imageBlueChannel(Rect(500, 250, logoImage.cols, logoImage.rows)), 1.0,
		logoImage, 0.5, 0, imageBlueChannel(Rect(500, 250, logoImage.cols, logoImage.rows)));

	// 5.将三个单通道重新合并成一个三通道
	merge(channels, srcImage);

	// 6.显示效果图
	namedWindow("<1>原画+logo蓝色通道");
	imshow("<1>原画+logo蓝色通道", srcImage);

	// 绿色通道部分
	// 多通道混合-绿色分量部分
	// 0.定义相关变量
	Mat imageGreenChannel;

	// 1.重新读入图片
	logoImage = imread("dota_logo.jpg", 0);
	srcImage = imread("dota_jugg.jpg");
	if (!logoImage.data)
	{
		cout << "读取logoImage错误！\n";
		return false;
	}
	if (!srcImage.data)
	{
		cout << "读取srcImage错误！\n";
		return false;
	}

	// 2.将一个三通道图像准换成三个单通道图像
	split(srcImage, channels);

	// 3.将原图绿色通道的引用返回给imageGreenChannel，是引用，两者等价，改变一个另一个也改变
	imageGreenChannel = channels.at(1);
	// 4.将原图绿色通道的(500,250)坐标右下方的区域和logo图像进行加权操作，
	// 将得到的混合结果存入imageGreenChannel
	addWeighted(imageGreenChannel(Rect(500, 250, logoImage.cols, logoImage.rows)), 1.0,
		logoImage, 0.5, 0., imageGreenChannel(Rect(500, 250, logoImage.cols, logoImage.rows)));

	// 5.将三个独立的单通道重新合并成一个三通道
	merge(channels, srcImage);

	// 6.显示效果图
	namedWindow("<2>原画+logo绿色通道");
	imshow("<2>原画+logo绿色通道", srcImage);

	// 红色通道部分
	// 多通道混合-红色分量部分
	// 0.定义相关变量
	Mat imageRedChannel;

	// 1.重新读入图片
	logoImage = imread("dota_logo.jpg", 0);
	srcImage = imread("dota_jugg.jpg");
	if (!logoImage.data)
	{
		cout << "读取logoImage错误！\n";
		return false;
	}
	if (!srcImage.data)
	{
		cout << "读取srcImage错误！\n";
		return false;
	}

	// 2.将一个三通道图像准换成三个单通道图像
	split(srcImage, channels);

	// 3.将原图红色通道的引用返回给imageGreenChannel，是引用，两者等价，改变一个另一个也改变
	imageRedChannel = channels.at(2);
	// 4.将原图红色通道的(500,250)坐标右下方的区域和logo图像进行加权操作，
	// 将得到的混合结果存入imageRedChannel
	addWeighted(imageRedChannel(Rect(500, 250, logoImage.cols, logoImage.rows)), 1.0,
		logoImage, 0.5, 0., imageRedChannel(Rect(500, 250, logoImage.cols, logoImage.rows)));

	// 5.将三个独立的单通道重新合并成一个三通道
	merge(channels, srcImage);

	// 6.显示效果图
	namedWindow("<2>原画+logo红色通道");
	imshow("<2>原画+logo红色通道", srcImage);

	return true;
}