// ROI选定区域
// 使用addWeighted()函数进行混合操作

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using std::cout;

bool ROI_AddImage();
bool LinearBlending();
bool ROI_LinearBlending();

int main()
{
	system("color 5E");

	if (ROI_AddImage() && LinearBlending() && ROI_LinearBlending())
		cout << "成功运行，得到想要的图像！\n";

	waitKey(0);
	return 0;
}

bool ROI_AddImage()
{
	// 1.读入图像
	Mat srcImage = imread("dota_pa.jpg");
	if (!srcImage.data)
	{
		cout << "读取srcimage错误!\n";
		return false;
	}
	Mat logoImage = imread("dota_logo.jpg");
	if (!logoImage.data)
	{
		cout << "读取logoImage错误!\n";
		return false;
	}

	// 2.定义一个Mat类并给其设定ROI区域
	Mat imageROI = srcImage(Rect(200, 250, logoImage.cols, logoImage.rows));

	// 3.加盖掩模（必须是灰度图）
	Mat mask = imread("dota_logo.jpg", 0);

	// 4.将掩模复制到ROI
	logoImage.copyTo(imageROI, mask);

	// 5.显示结果
	namedWindow("1.利用ROI实现图像叠加示例窗口");
	imshow("1.利用ROI实现图像叠加示例窗口", srcImage);

	return true;
}

bool LinearBlending()
{
	double alphaValue = 0.5;
	double betaValue;
	Mat srcImage1, srcImage2, dstImage;

	// 1.读取图像（两幅图像需为同类型尺寸）
	srcImage1 = imread("mogu.jpg");
	srcImage2 = imread("rain.jpg");
	if (!srcImage1.data)
	{
		cout << "读取srcImage1错误！\n";
		return false;
	}
	if (!srcImage2.data)
	{
		cout << "读取srcImage2错误！\n";
		return false;
	}

	// 2.图像混合加权操作
	betaValue = (1.0 - alphaValue);
	addWeighted(srcImage1, alphaValue, srcImage2, betaValue, 0.0, dstImage);

	// 3.创建窗口并输出原图和混合图
	namedWindow("2.线性混合示例窗口【原图】", 1);
	imshow("2.线性混合示例窗口【原图】", srcImage1);

	namedWindow("2.线性混合示例窗口【效果图】", 1);
	imshow("2.线性混合示例窗口【效果图】", dstImage);

	return true;
}

bool ROI_LinearBlending()
{
	// 1.读取图像
	Mat srcImage3 = imread("dota_pa.jpg", 1);
	Mat logoImage = imread("dota_logo.jpg");
	if (!srcImage3.data)
	{
		cout << "读取srcImage3错误！\n";
		return false;
	}
	if (!logoImage.data)
	{
		cout << "读取logoImage1错误！\n";
		return false;
	}

	// 2.定义一个Mat类并给其设定ROI区域
	Mat imageROI;
	//imageROI = srcImage3(Rect(200, 250, logoImage.cols, logoImage.rows));  // 方法一
	imageROI = srcImage3(Range(250, 250 + logoImage.rows), Range(200, 200 + logoImage.cols));  // 方法二

	// 3.将logo加到原图上
	addWeighted(imageROI, 0.5, logoImage, 0.3, 0., imageROI);

	// 4.显示结果
	namedWindow("3.区域线性图像混合示例窗口");
	imshow("3.区域线性图像混合示例窗口", srcImage3);

	return true;
}