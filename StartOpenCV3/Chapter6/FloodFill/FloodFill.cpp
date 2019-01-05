// 利用漫水填充floodFill函数实现颜色填充
// 类似PhotoShop魔法棒功能

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

Mat srcImage, dstImage, grayImage, maskImage; // 定义原始图、目标图、灰度图、掩模
int FillMode = 1;   // 漫水填充模式
int MaxLowDifference = 20, MaxUpDifference = 20;    // 负差最大值、正差最大值
int Connectivity = 4;    // 表示floodFill函数标识符第八位的连通值
bool IsColor = true;     // 是否为彩色图的bool标识
bool UseMask = false;    // 是否显示掩模窗口的bool标识
int NewMaskVal = 255;    // 新的重新绘制的像素值

static void onMouse(int event, int x, int y, int, void*);

int main()
{
	// 载入原图
	srcImage = imread("1.jpg");
	if (!srcImage.data)
	{
		cout << "读取图片错误，请确认目录下是否有指定的图片!\n";
		return -1;
	}
	// 显示原图
	namedWindow("原图");
	imshow("原图", srcImage);

	srcImage.copyTo(dstImage);
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);   // 三通道彩色图转换为灰度图
	maskImage.create(srcImage.rows + 2, srcImage.cols + 2, CV_8UC1);  // 初始化掩模mask

	namedWindow("效果图");

	// 创建轨迹条
	createTrackbar("复差最大值", "效果图", &MaxLowDifference, 255, 0);
	createTrackbar("正差最大值", "效果图", &MaxUpDifference, 255, 0);

	// 鼠标回调函数
	setMouseCallback("效果图", onMouse, 0);

	// 循环轮询按键
	while (1)
	{
		// 先显示效果图
		imshow("效果图", IsColor ? dstImage : grayImage);

		// 回去键盘按键
		int c = waitKey(0);
		// Esc按下，程序退出
		if ((c & 255) == 27)
		{
			cout << "程序退出......\n";
			break;
		}

		// 根据按键不同，进行各种操作
		switch ((char)c)
		{
		// 键盘1按下，效果图在灰度图彩色图之间切换
		case '1' :
			if (IsColor)  // 若原来为彩色，转为灰度图，并且将掩模mask所有元素设置为0
			{
				cout << "键盘【1】按下，切换彩色/灰度模式，当前操作为【彩色】切换到【灰度】\n";
				cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
				maskImage = Scalar::all(0);
				IsColor = false;
			}
			else  // 若原来为灰度图，转为彩色，并且将mask所有原色设置为0
			{
				cout << "键盘【1】按下，切换彩色/灰度模式，当前操作为【灰度】切换到【彩色】\n";
				srcImage.copySize(dstImage);
				maskImage = Scalar::all(0);
				IsColor = true;
			}
			break;
		// 键盘2按下，显示/隐藏掩模窗口
		case '2' :
			if (UseMask)
			{
				destroyWindow("mask");
				UseMask = false;
			}
			else
			{
				namedWindow("mask", 0);
				maskImage = Scalar::all(0);
				imshow("mask", maskImage);
				UseMask = true;
			}
			break;
		// 键盘3按下，恢复原始图像
		case '3' :
			cout << "键盘【3】按下，恢复原始图像\n";
			srcImage.copyTo(dstImage);
			cvtColor(dstImage, grayImage, COLOR_BGR2GRAY);
			maskImage = Scalar::all(0);
			break;
		// 键盘4按下,使用空范围的漫水填充
		case '4' :
			cout << "键盘【4】按下，使用空范围的漫水填充\n";
			FillMode = 0;
			break;
		// 键盘5按下，使用渐变、固定范围的漫水填充
		case '5' :
			cout << "按键【5】按下，使用渐变、固定范围的漫水填充\n";
			FillMode = 1;
			break;
		// 按键6按下，使用渐变、浮动范围的满树填充
		case '6' :
			cout << "按键【6】按下，使用渐变、浮动范围的漫水填充\n";
			FillMode = 2;
			break;
		// 按键7按下，操作标识符的低八位使用4位的连接模式
		case '7' :
			cout << "按键【7】按下，操作标识符的低八位使用4位的连接模式\n";
			Connectivity = 4;
			break;
		// 按键8按下，操作标识符的低八位使用8位的连接模式
		case '8' :
			cout << "按键【8】按下，操作标识符的低八位使用8位的连接模式\n";
			Connectivity = 8;
			break;
		}
	}

	return 0;
}

// 鼠标消息回调函数
static void onMouse(int event, int x, int y, int, void*)
{
	// 若鼠标左键没有按下，则返回
	if (event != EVENT_LBUTTONDOWN)
		return;

	// 1.调用floodFill函数之前的参数准备
	Point seed = Point(x, y);   // 种子坐标
	int LowDifference = FillMode == 0 ? 0 : MaxLowDifference;  // 空范围的漫水填充，此值设为0，否则设为全局最大复差
	int UpDifference = FillMode == 0 ? 0 : MaxUpDifference;    // 空范围的漫水填充，此值设为0，否则设为全局最大复差
	// 标识符的0~7位为Connectivity，8~15位为NewMaskVal左移8位的值，16~23位为FLOODFILL_FIXED_RANGE或0
	int flags = Connectivity + (NewMaskVal << 8) + (FillMode == 1 ? FLOODFILL_FIXED_RANGE : 0);
	// 随机生成BGR值，随机返回一个0~255之间的值
	int b = (unsigned)theRNG() & 255;
	int g = (unsigned)theRNG() & 255;
	int r = (unsigned)theRNG() & 255;
	Rect ccomp;   // 定义重绘区域的最小边界矩形区域
	// 在重绘区域像素的新值
	Scalar newVal = IsColor ? Scalar(b, g, r) : Scalar(r*0.299 + g * 0.587 + b * 0.114);
	// 目标图的赋值
	Mat dst = IsColor ? dstImage : grayImage;
	int area;

	// 2.正式调用flooFill函数
	if (UseMask)
	{
		threshold(maskImage, maskImage, 1, 128, THRESH_BINARY);
		area = floodFill(dst, maskImage, seed, newVal, &ccomp,
			Scalar(LowDifference, LowDifference, LowDifference),
			Scalar(UpDifference, UpDifference, UpDifference),
			flags);
		imshow("mask", maskImage);
	}
	else
	{
		area = floodFill(dst, seed, newVal, &ccomp,
			Scalar(LowDifference, LowDifference, LowDifference),
			Scalar(UpDifference, UpDifference, UpDifference),
			flags);
	}
	imshow("效果图", dst);
	cout << area << " 个像素被重绘\n";
}