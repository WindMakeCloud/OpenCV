// 减少图像中颜色数量，256变为8种
// 整除32后乘32

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void colorReduce(Mat& inputImage, Mat& outputImage, int div);

int main()
{
	// 1.创建原始图并显示
	Mat srcImage = imread("1.jpg");
	imshow("原始图", srcImage);

	// 2.按原图的参数规格创建效果图
	Mat dstImage;
	dstImage.create(srcImage.rows, srcImage.cols, srcImage.type());

	// 3.记录起始时间
	double time0 = static_cast<double>(getTickCount());

	// 4.调用颜色空间缩减函数
	colorReduce(srcImage, dstImage, 32);

	// 5.计算运行时间并输出
	time0 = ((double)getTickCount() - time0) / getTickFrequency();
	cout << "此方法运行时间为：" << time0 << "s" << endl;

	// 6.显示效果图
	imshow("效果图", dstImage);
	waitKey(0);
	return 0;
}

/*// colorReduce()函数：
// 使用【指针访问：C操作符[]】方法的颜色空间缩减函数
void colorReduce(Mat& inputImage, Mat& outputImage, int div)
{
	// 参数准备
	outputImage = inputImage.clone();     // 复制实参到临时变量
	int rowNumber = outputImage.rows;     // 行数
	int colNumber = outputImage.cols * outputImage.channels();  // 列数*通道数=每一行元素个数

	// 双重循环，遍历所有像素值
	for (int i = 0; i < rowNumber; i++)   // 行循环
	{
		uchar* data = outputImage.ptr<uchar>(i);  // 获取第i行的首地址
		for (int j = 0; j < colNumber; j++)  // 列循环
			data[j] = data[j] / div * div + div / 2;  // 处理每个像素
	}
}*/

/*// colorReduce()函数：
// 使用【迭代器】方法的颜色空间缩减函数
void colorReduce(Mat& inputImage, Mat& outputImage, int div)
{
	// 参数准备
	outputImage = inputImage.clone();
	// 获取迭代器
	Mat_<Vec3b>::iterator it = outputImage.begin<Vec3b>();  // 初始位置迭代器
	Mat_<Vec3b>::iterator itend = outputImage.end<Vec3b>(); // 终止位置迭代器

	// 存取彩色图像像素
	for (; it != itend; ++it)
	{
		(*it)[0] = (*it)[0] / div * div + div / 2;
		(*it)[1] = (*it)[1] / div * div + div / 2;
		(*it)[2] = (*it)[2] / div * div + div / 2;
	}
}*/

// colorReduce()函数：
// 使用【动态地址运算配合at】方法的颜色空间缩减函数
void colorReduce(Mat& inputImage, Mat& outputImage, int div)
{
	// 参数准备
	outputImage = inputImage.clone();
	int rowNumber = outputImage.rows;  // 行数
	int colNumber = outputImage.cols;  // 列数

	// 存取彩色图像像素
	for (int i = 0 ; i < rowNumber; i++)
		for (int j = 0; j < colNumber; j++)
		{
			outputImage.at<Vec3b>(i, j)[0] = 
				outputImage.at<Vec3b>(i, j)[0] / div * div + div / 2;  // 蓝色通道
			outputImage.at<Vec3b>(i, j)[1] =
				outputImage.at<Vec3b>(i, j)[1] / div * div + div / 2;  // 绿色通道
			outputImage.at<Vec3b>(i, j)[2] =
				outputImage.at<Vec3b>(i, j)[2] / div * div + div / 2;  // 红色通道
		}
}