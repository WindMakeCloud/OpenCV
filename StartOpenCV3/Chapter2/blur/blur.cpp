// blur模糊效果
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main()
{
	Mat image = imread("mao2.jpg");

	imshow("均值滤波【原图】", image);

	//进行均值滤波操作
	Mat dstimage;
	blur(image, dstimage, Size(20, 20));

	// 显示效果图
	imshow("均值滤波【效果图】", dstimage);

	waitKey(0);
    return 0;
}

