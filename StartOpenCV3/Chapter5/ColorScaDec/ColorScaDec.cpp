// ����ͼ������ɫ������256��Ϊ8��
// ����32���32

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void colorReduce(Mat& inputImage, Mat& outputImage, int div);

int main()
{
	// 1.����ԭʼͼ����ʾ
	Mat srcImage = imread("1.jpg");
	imshow("ԭʼͼ", srcImage);

	// 2.��ԭͼ�Ĳ�����񴴽�Ч��ͼ
	Mat dstImage;
	dstImage.create(srcImage.rows, srcImage.cols, srcImage.type());

	// 3.��¼��ʼʱ��
	double time0 = static_cast<double>(getTickCount());

	// 4.������ɫ�ռ���������
	colorReduce(srcImage, dstImage, 32);

	// 5.��������ʱ�䲢���
	time0 = ((double)getTickCount() - time0) / getTickFrequency();
	cout << "�˷�������ʱ��Ϊ��" << time0 << "s" << endl;

	// 6.��ʾЧ��ͼ
	imshow("Ч��ͼ", dstImage);
	waitKey(0);
	return 0;
}

/*// colorReduce()������
// ʹ�á�ָ����ʣ�C������[]����������ɫ�ռ���������
void colorReduce(Mat& inputImage, Mat& outputImage, int div)
{
	// ����׼��
	outputImage = inputImage.clone();     // ����ʵ�ε���ʱ����
	int rowNumber = outputImage.rows;     // ����
	int colNumber = outputImage.cols * outputImage.channels();  // ����*ͨ����=ÿһ��Ԫ�ظ���

	// ˫��ѭ����������������ֵ
	for (int i = 0; i < rowNumber; i++)   // ��ѭ��
	{
		uchar* data = outputImage.ptr<uchar>(i);  // ��ȡ��i�е��׵�ַ
		for (int j = 0; j < colNumber; j++)  // ��ѭ��
			data[j] = data[j] / div * div + div / 2;  // ����ÿ������
	}
}*/

/*// colorReduce()������
// ʹ�á�����������������ɫ�ռ���������
void colorReduce(Mat& inputImage, Mat& outputImage, int div)
{
	// ����׼��
	outputImage = inputImage.clone();
	// ��ȡ������
	Mat_<Vec3b>::iterator it = outputImage.begin<Vec3b>();  // ��ʼλ�õ�����
	Mat_<Vec3b>::iterator itend = outputImage.end<Vec3b>(); // ��ֹλ�õ�����

	// ��ȡ��ɫͼ������
	for (; it != itend; ++it)
	{
		(*it)[0] = (*it)[0] / div * div + div / 2;
		(*it)[1] = (*it)[1] / div * div + div / 2;
		(*it)[2] = (*it)[2] / div * div + div / 2;
	}
}*/

// colorReduce()������
// ʹ�á���̬��ַ�������at����������ɫ�ռ���������
void colorReduce(Mat& inputImage, Mat& outputImage, int div)
{
	// ����׼��
	outputImage = inputImage.clone();
	int rowNumber = outputImage.rows;  // ����
	int colNumber = outputImage.cols;  // ����

	// ��ȡ��ɫͼ������
	for (int i = 0 ; i < rowNumber; i++)
		for (int j = 0; j < colNumber; j++)
		{
			outputImage.at<Vec3b>(i, j)[0] = 
				outputImage.at<Vec3b>(i, j)[0] / div * div + div / 2;  // ��ɫͨ��
			outputImage.at<Vec3b>(i, j)[1] =
				outputImage.at<Vec3b>(i, j)[1] / div * div + div / 2;  // ��ɫͨ��
			outputImage.at<Vec3b>(i, j)[2] =
				outputImage.at<Vec3b>(i, j)[2] / div * div + div / 2;  // ��ɫͨ��
		}
}