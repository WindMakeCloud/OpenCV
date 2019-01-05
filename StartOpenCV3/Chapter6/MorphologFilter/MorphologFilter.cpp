// 综合实例：形态学滤波
// 开闭运算、腐蚀/膨胀、顶帽/黑帽

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <imgproc.hpp>

using namespace std;
using namespace cv;

Mat srcImage, dstImage;           // 原始图和效果图
int ElementShape = MORPH_RECT;    // 元素结构的形状

// 变量接收的Trackbar位置参数
int MaxIterationNum = 10;
int OpenCloseNum = 0;
int ErodeDilateNum = 0;
int TopBlackHatNum = 0;

// 回调函数声明
static void on_OpenClose(int, void*);
static void on_ErodeDilate(int, void*);
static void on_TopBlackHat(int, void*);
static void ShowHelpText();   // 帮助信息

int main()
{
	// 显示帮助信息
	ShowHelpText();

	// 载入原图
	srcImage = imread("1.jpg");
	if (!srcImage.data)
	{
		cout << "读取图片错误，请确认目录下由指定图片！\n";
		return -1;
	}

	// 显示原始图
	namedWindow("原图");
	imshow("原图", srcImage);

	// 创建三个窗口
	namedWindow("开运算/闭运算");
	namedWindow("腐蚀/膨胀");
	namedWindow("顶帽/黑帽");

	// 参数幅值
	OpenCloseNum = 9;
	ErodeDilateNum = 9;
	TopBlackHatNum = 2;

	// 三个窗口创建轨迹条
	createTrackbar("迭代值", "开运算/闭运算", &OpenCloseNum, MaxIterationNum * 2 + 1, on_OpenClose);
	createTrackbar("迭代值", "腐蚀/膨胀", &ErodeDilateNum, MaxIterationNum * 2 + 1, on_ErodeDilate);
	createTrackbar("迭代值", "顶帽/黑帽", &TopBlackHatNum, MaxIterationNum * 2 + 1, on_TopBlackHat);

	// 轮询获取按键信息
	while (1)
	{
		int c;

		// 执行回调函数
		on_OpenClose(OpenCloseNum, 0);
		on_ErodeDilate(ErodeDilateNum, 0);
		on_TopBlackHat(TopBlackHatNum, 0);

		// 获取按键
		c = waitKey(0);

		// 按下Q键或Esc程序退出
		if ((char)c == 'q' || (char)c == 27)
			break;
		// 按下键盘按键1，使用椭圆(Elliptic)结构元素MORPH_ELLIPSE
		if ((char)c == 49)  // 键盘按键1的ASII码为49
			ElementShape = MORPH_ELLIPSE;
		// 按下键盘按键2，使用矩形结构元素MORPH_RECT
		else if ((char)c == 50)  // 键盘按键2的ASII码为50
			ElementShape = MORPH_RECT;
		// 按下键盘按键3，使用十字形结构元素MORPH_CROSS
		else if ((char)c == 51)  // 键盘按键3的ASII码为51
			ElementShape = MORPH_CROSS;
		// 按下键盘按键space，在矩形、椭圆、十字形结构元素中循环
		else if ((char)c == ' ')
			ElementShape = (ElementShape + 1) % 3;
	}
	return 0;
}

static void on_OpenClose(int, void*)
{
	// 偏移量的定义
	int offset = OpenCloseNum - MaxIterationNum;           // 偏移量
	int Absolute_offset = offset > 0 ? offset : -offset;   // 偏移量绝对值
	// 自定义核
	Mat element = getStructuringElement(
		ElementShape,
		Size(Absolute_offset * 2 + 1, Absolute_offset * 2 + 1),
		Point(Absolute_offset, Absolute_offset));
	// 进行操作
	if (offset < 0)
		morphologyEx(srcImage, dstImage, MORPH_OPEN, element);
	else
		morphologyEx(srcImage, dstImage, MORPH_CLOSE, element);
	// 显示图像
	imshow("开运算/闭运算", dstImage);
}

static void on_ErodeDilate(int, void*)
{
	// 偏移量的设定
	int offset = ErodeDilateNum - MaxIterationNum;   // 偏移量
	int Absolute_offset = offset > 0 ? offset : -offset;  // 绝对偏移量
	// 自定义核
	Mat element = getStructuringElement(
		ElementShape,
		Size(Absolute_offset * 2 + 1, Absolute_offset * 2 + 1),
		Point(Absolute_offset, Absolute_offset)
	);
	// 进行操作
	if (offset < 0)
		erode(srcImage, dstImage, element);
	else
		dilate(srcImage, dstImage, element);
	// 显示图像
	imshow("腐蚀/膨胀", dstImage);
}

static void on_TopBlackHat(int, void*)
{
	int offset = TopBlackHatNum - MaxIterationNum;
	int Absolute_offset = offset > 0 ? offset : -offset;
	Mat element = getStructuringElement(
		ElementShape,
		Size(Absolute_offset * 2 + 1, Absolute_offset * 2 + 1),
		Point(Absolute_offset, Absolute_offset)
	);
	if (offset < 0)
		morphologyEx(srcImage, dstImage, MORPH_TOPHAT, element);
	else
		morphologyEx(srcImage, dstImage, MORPH_BLACKHAT, element);
	imshow("顶帽/黑帽", dstImage);
}

void ShowHelpText()
{
	cout << "\n    调整轨迹条观察图片处理效果\n\n"
		<< "    按键操作说明：\n"
		<< "              键盘按键【Esc】或【Q】- 退出程序\n"
		<< "              键盘按键【1】- 使用椭圆结构元素\n"
		<< "              键盘按键【2】- 使用矩形结构元素\n"
		<< "              键盘按键【3】- 使用十字形结构元素\n"
		<< "              键盘按键【空格】- 在矩形、椭圆、十字形结构元素中循环\n";
}