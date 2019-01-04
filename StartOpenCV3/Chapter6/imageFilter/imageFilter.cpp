// 5��ͼ���˲�������Ϲ켣����ʾ�˲�Ч��
// �����˲��������˲�����ֵ�˲�����˹�˲�
// �������˲�����ֵ�˲���˫���˲�

#include <core.hpp>
#include <highgui.hpp>
#include <imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// ȫ�ֱ���������
Mat srcImage, dstImage1, dstImage2, dstImage3, dstImage4, dstImage5;
int BoxFilterValue = 6;         // �����˲��ں�ֵ
int MeanBlurValue = 10;         // ��ֵ�˲��ں�ֵ
int GaussianBlurValue = 6;      // ��˹�˲��ں�ֵ
int MedianBlueValue = 10;       // ��ֵ�˲�����ֵ
int BilateralFilterValue = 10;  // ˫���˲�����ֵ

// ���˲������켣���ص�����
static void on_BoxFilter(int, void*);
static void on_MeanBlur(int, void*);
static void on_GaussianBlur(int, void*);
static void on_MedianBlur(int, void*);
static void on_BilateralFilter(int, void*);

int main()
{
	// ����ԭͼ
	srcImage = imread("1.jpg");
	if (!srcImage.data)
	{
		cout << "��ȡͼƬ������ȷ��Ŀ¼����ָ��ͼƬ��\n";
		return -1;
	}

	// ����ԭͼ��5��Mat��
	dstImage1 = srcImage.clone();
	dstImage2 = srcImage.clone();
	dstImage3 = srcImage.clone();
	dstImage4 = srcImage.clone();
	dstImage5 = srcImage.clone();

	// ��ʾԭͼ
	namedWindow("ԭͼ");
	imshow("ԭͼ", srcImage);

	// �����˲�
	namedWindow("�����˲�");
	createTrackbar("�ں�ֵ��", "�����˲�", &BoxFilterValue, 50, on_BoxFilter);
	on_BoxFilter(BoxFilterValue, 0);

	// ��ֵ�˲�
	namedWindow("��ֵ�˲�");
	createTrackbar("�ں�ֵ��", "��ֵ�˲�", &MeanBlurValue, 50, on_MeanBlur);
	on_MeanBlur(MeanBlurValue, 0);

	// ��˹�˲�
	namedWindow("��˹�˲�");
	createTrackbar("�ں�ֵ��", "��˹�˲�", &GaussianBlurValue, 50, on_GaussianBlur);
	on_GaussianBlur(GaussianBlurValue, 0);

	// ��ֵ�˲�
	namedWindow("��ֵ�˲�");
	createTrackbar("����ֵ��", "��ֵ�˲�", &MedianBlueValue, 50, on_MedianBlur);
	on_MedianBlur(MedianBlueValue, 0);

	// ˫���˲�
	namedWindow("˫���˲�");
	createTrackbar("����ֵ��", "˫���˲�", &BilateralFilterValue, 50, on_BilateralFilter);
	on_BilateralFilter(BilateralFilterValue, 0);

	// ��q���������
	cout << "��q���������!\n";
	while (char(waitKey(1)) != 'q') { }
	return 0;
}

static void on_BoxFilter(int, void*)
{
	boxFilter(srcImage, dstImage1, -1, Size(BoxFilterValue + 1, BoxFilterValue + 1));
	imshow("�����˲�", dstImage1);
}

static void on_MeanBlur(int, void*)
{
	blur(srcImage, dstImage2, Size(MeanBlurValue + 1, MeanBlurValue + 1), Point(-1, -1));
	imshow("��ֵ�˲�", dstImage2);
}

static void on_GaussianBlur(int, void*)
{
	GaussianBlur(srcImage, dstImage3, Size(GaussianBlurValue * 2 + 1, GaussianBlurValue * 2 + 1), 0, 0);
	imshow("��˹�˲�", dstImage3);
}

static void on_MedianBlur(int, void*)
{
	medianBlur(srcImage, dstImage4, MedianBlueValue * 2 + 1);
	imshow("��ֵ�˲�", dstImage4);
}

static void on_BilateralFilter(int, void*)
{
	bilateralFilter(srcImage, dstImage5, BilateralFilterValue, BilateralFilterValue * 2, BilateralFilterValue / 2);
	imshow("˫���˲�", dstImage5);
}