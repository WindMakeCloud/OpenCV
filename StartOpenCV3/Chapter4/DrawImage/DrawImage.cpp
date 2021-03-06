
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

#define WINDOW_NAME1 "【绘制图1】"     // 窗口1标题
#define WINDOW_NAME2 "【绘制图2】"     // 窗口2标题
#define WINDOW_WIDTH 600              // 窗口大小

void DrawEllipse(Mat img, double angle);         // 椭圆绘制函数
void DrawFilledCircle(Mat img, Point center);    // 实心原绘制函数
void DrawPolygon(Mat img);                       // 凹多边形绘制函数
void DrawLine(Mat img, Point start, Point end);  // 线绘制函数

int main()
{
	// 创建空白的Mat图像
	Mat atomImage = Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);
	Mat rookImage = Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);

	// 一、绘制化学中的原子示意图
	// 1.1 绘制椭圆
	DrawEllipse(atomImage, 90);
	DrawEllipse(atomImage, 0);
	DrawEllipse(atomImage, 45);
	DrawEllipse(atomImage, -45);
	// 1.2 绘制实心圆
	DrawFilledCircle(atomImage, Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2));

	// 二、绘制组合图
	// 2.1 绘制凹多边形
	DrawPolygon(rookImage);
	// 2.2 绘制矩形
	rectangle(rookImage,
		Point(0, 7 * WINDOW_WIDTH / 8),
		Point(WINDOW_WIDTH, WINDOW_WIDTH),
		Scalar(0, 255, 255),
		-1,
		8);
	// 2.3 绘制一些线段
	DrawLine(rookImage, Point(0, 15 * WINDOW_WIDTH / 16), Point(WINDOW_WIDTH, 15 * WINDOW_WIDTH / 16));
	DrawLine(rookImage, Point(WINDOW_WIDTH / 4, 7 * WINDOW_WIDTH / 8), Point(WINDOW_WIDTH / 4, WINDOW_WIDTH));
	DrawLine(rookImage, Point(WINDOW_WIDTH / 2, 7 * WINDOW_WIDTH / 8), Point(WINDOW_WIDTH / 2, WINDOW_WIDTH));
	DrawLine(rookImage, Point(3 * WINDOW_WIDTH / 4, 7 * WINDOW_WIDTH / 8), Point(3 * WINDOW_WIDTH / 4, WINDOW_WIDTH));

	// 三、显示绘制出的图像
	imshow(WINDOW_NAME1, atomImage);
	moveWindow(WINDOW_NAME1, 0, 200);
	imshow(WINDOW_NAME2, rookImage);
	moveWindow(WINDOW_NAME2, WINDOW_WIDTH, 200);

	waitKey(0);
    return 0;
}

// 椭圆绘制函数：
// 自定义的绘制函数，实现了绘制不同角度、相同尺寸的椭圆
void DrawEllipse(Mat img, double angle)
{
	int thickness = 2;
	int lineType = 8;

	ellipse(img,
		Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2),  // 中心点
		Size(WINDOW_WIDTH / 4, WINDOW_WIDTH / 16),  // 大小
		angle,                                      // 旋转角度
		0,                                          // 扩展弧度0到
		360,                                        // 360度
		Scalar(255, 129, 0),                        // 颜色
		thickness,                                  // 线宽
		lineType);                                  // 线型
}

// 实心圆绘制函数：
// 自定义的绘制函数，实现了实心圆的绘制
void DrawFilledCircle(Mat img, Point center)
{
	int thickness = -1;
	int lineType = 8;

	circle(img,
		center,               // 圆心
		WINDOW_WIDTH / 32,    // 半径
		Scalar(0, 0, 255),    // 颜色
		thickness,            // 线宽定义为-1，则为实心
		lineType);            // 线型
}


// 凹多边形绘制函数：
// 自定义绘制函数，实现了凹多边形的绘制
void DrawPolygon(Mat img)
{
	int lineType = 8;

	// 创建一些点
	Point rookPoints[1][20];
	rookPoints[0][0]  = Point(     WINDOW_WIDTH / 4,   7 * WINDOW_WIDTH /  8);
	rookPoints[0][1]  = Point( 3 * WINDOW_WIDTH / 4,   7 * WINDOW_WIDTH /  8);
	rookPoints[0][2]  = Point( 3 * WINDOW_WIDTH / 4,  13 * WINDOW_WIDTH / 16);
	rookPoints[0][3]  = Point(11 * WINDOW_WIDTH / 16, 13 * WINDOW_WIDTH / 16);
	rookPoints[0][4]  = Point(19 * WINDOW_WIDTH / 32,  3 * WINDOW_WIDTH /  8);
	rookPoints[0][5]  = Point( 3 * WINDOW_WIDTH / 4,   3 * WINDOW_WIDTH /  8);
	rookPoints[0][6]  = Point( 3 * WINDOW_WIDTH / 4,       WINDOW_WIDTH /  8);
	rookPoints[0][7]  = Point(26 * WINDOW_WIDTH / 40,      WINDOW_WIDTH /  8);
	rookPoints[0][8]  = Point(26 * WINDOW_WIDTH / 40,      WINDOW_WIDTH /  4);
	rookPoints[0][9]  = Point(22 * WINDOW_WIDTH / 40,      WINDOW_WIDTH /  4);
	rookPoints[0][10] = Point(22 * WINDOW_WIDTH / 40,      WINDOW_WIDTH /  8);
	rookPoints[0][11] = Point(18 * WINDOW_WIDTH / 40,      WINDOW_WIDTH /  8);
	rookPoints[0][12] = Point(18 * WINDOW_WIDTH / 40,      WINDOW_WIDTH /  4);
	rookPoints[0][13] = Point(14 * WINDOW_WIDTH / 40,      WINDOW_WIDTH /  4);
	rookPoints[0][14] = Point(14 * WINDOW_WIDTH / 40,      WINDOW_WIDTH /  8);
	rookPoints[0][15] = Point(     WINDOW_WIDTH / 4,       WINDOW_WIDTH /  8);
	rookPoints[0][16] = Point(     WINDOW_WIDTH / 4,   3 * WINDOW_WIDTH /  8);
	rookPoints[0][17] = Point(13 * WINDOW_WIDTH / 32,  3 * WINDOW_WIDTH /  8);
	rookPoints[0][18] = Point( 5 * WINDOW_WIDTH / 16, 13 * WINDOW_WIDTH / 16);
	rookPoints[0][19] = Point(     WINDOW_WIDTH / 4,  13 * WINDOW_WIDTH / 16);

	const Point* ppt[1] = { rookPoints[0] };
	int npt[] = { 20 };

	fillPoly(img,
		ppt,                     // 多边形顶点集
		npt,                     // 多边形顶点数目
		1,                       // 多边形数量
		Scalar(255, 255, 255),   // 颜色
		lineType);               // 线型
}


// 线绘制函数：
// 自定义的绘制函数，实现了线的绘制
void DrawLine(Mat img, Point start, Point end)
{
	int thickness = 2;
	int lineType = 8;

	line(img,
		start,              // 起点
		end,                // 终点
		Scalar(0, 0, 0),    // 颜色
		thickness,          // 线宽
		lineType);          // 线型
}