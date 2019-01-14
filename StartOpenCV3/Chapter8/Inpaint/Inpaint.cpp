// 图像修补，inpaint()函数的应用
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/photo.hpp>
#include <iostream>

using namespace std;
using namespace cv;

#define WINDOW_NAME1 "原图"
#define WINDOW_NAME2 "修补图"

Mat srcImage1, inpaintMask;
Point prevPt(-1, -1);

static void on_Mouse(int event, int x, int y, int flags, void*);

int main()
{
	Mat srcImage = imread("1.jpg", 1);
	srcImage1 = srcImage.clone();
	inpaintMask = Mat::zeros(srcImage1.size(), CV_8U);

	imshow(WINDOW_NAME1, srcImage1);
	
	setMouseCallback(WINDOW_NAME1, on_Mouse, 0);

	while (1)
	{
		char c = (char)waitKey();

		if (c == 27)
			break;

		if (c == '2')
		{
			inpaintMask = Scalar::all(0);
			srcImage.copyTo(srcImage1);
			imshow(WINDOW_NAME1, srcImage1);
		}

		if (c == '1' || c == ' ')
		{
			Mat inpaintedImage;
			inpaint(srcImage1, inpaintMask, inpaintedImage, 3, INPAINT_TELEA);
			imshow(WINDOW_NAME2, inpaintedImage);
		}
	}
	return 0;
}

static void on_Mouse(int event, int x, int y, int flags, void*)
{
	// 鼠标不在窗口
	if (x < 0 || x >= srcImage1.cols || y < 0 || y >= srcImage1.rows)
		return;
	if (event == EVENT_LBUTTONUP || !(flags & EVENT_FLAG_LBUTTON))
		prevPt = Point(-1, -1);
	else if (event == EVENT_LBUTTONDOWN)
		prevPt = Point(x, y);
	else if (event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON))
	{
		Point pt(x, y);
		if (prevPt.x < 0)
			prevPt = pt;
		line(inpaintMask, prevPt, pt, Scalar::all(255), 5, 8, 0);
		line(srcImage1, prevPt, pt, Scalar::all(255), 5, 8, 0);
		prevPt = pt;
		imshow(WINDOW_NAME1, srcImage1);
	}
}