// ROIѡ������
// ʹ��addWeighted()�������л�ϲ���

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
		cout << "�ɹ����У��õ���Ҫ��ͼ��\n";

	waitKey(0);
	return 0;
}

bool ROI_AddImage()
{
	// 1.����ͼ��
	Mat srcImage = imread("dota_pa.jpg");
	if (!srcImage.data)
	{
		cout << "��ȡsrcimage����!\n";
		return false;
	}
	Mat logoImage = imread("dota_logo.jpg");
	if (!logoImage.data)
	{
		cout << "��ȡlogoImage����!\n";
		return false;
	}

	// 2.����һ��Mat�ಢ�����趨ROI����
	Mat imageROI = srcImage(Rect(200, 250, logoImage.cols, logoImage.rows));

	// 3.�Ӹ���ģ�������ǻҶ�ͼ��
	Mat mask = imread("dota_logo.jpg", 0);

	// 4.����ģ���Ƶ�ROI
	logoImage.copyTo(imageROI, mask);

	// 5.��ʾ���
	namedWindow("1.����ROIʵ��ͼ�����ʾ������");
	imshow("1.����ROIʵ��ͼ�����ʾ������", srcImage);

	return true;
}

bool LinearBlending()
{
	double alphaValue = 0.5;
	double betaValue;
	Mat srcImage1, srcImage2, dstImage;

	// 1.��ȡͼ������ͼ����Ϊͬ���ͳߴ磩
	srcImage1 = imread("mogu.jpg");
	srcImage2 = imread("rain.jpg");
	if (!srcImage1.data)
	{
		cout << "��ȡsrcImage1����\n";
		return false;
	}
	if (!srcImage2.data)
	{
		cout << "��ȡsrcImage2����\n";
		return false;
	}

	// 2.ͼ���ϼ�Ȩ����
	betaValue = (1.0 - alphaValue);
	addWeighted(srcImage1, alphaValue, srcImage2, betaValue, 0.0, dstImage);

	// 3.�������ڲ����ԭͼ�ͻ��ͼ
	namedWindow("2.���Ի��ʾ�����ڡ�ԭͼ��", 1);
	imshow("2.���Ի��ʾ�����ڡ�ԭͼ��", srcImage1);

	namedWindow("2.���Ի��ʾ�����ڡ�Ч��ͼ��", 1);
	imshow("2.���Ի��ʾ�����ڡ�Ч��ͼ��", dstImage);

	return true;
}

bool ROI_LinearBlending()
{
	// 1.��ȡͼ��
	Mat srcImage3 = imread("dota_pa.jpg", 1);
	Mat logoImage = imread("dota_logo.jpg");
	if (!srcImage3.data)
	{
		cout << "��ȡsrcImage3����\n";
		return false;
	}
	if (!logoImage.data)
	{
		cout << "��ȡlogoImage1����\n";
		return false;
	}

	// 2.����һ��Mat�ಢ�����趨ROI����
	Mat imageROI;
	//imageROI = srcImage3(Rect(200, 250, logoImage.cols, logoImage.rows));  // ����һ
	imageROI = srcImage3(Range(250, 250 + logoImage.rows), Range(200, 200 + logoImage.cols));  // ������

	// 3.��logo�ӵ�ԭͼ��
	addWeighted(imageROI, 0.5, logoImage, 0.3, 0., imageROI);

	// 4.��ʾ���
	namedWindow("3.��������ͼ����ʾ������");
	imshow("3.��������ͼ����ʾ������", srcImage3);

	return true;
}