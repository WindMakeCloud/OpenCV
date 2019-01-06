// ��Ե����ۺ�ʾ��
// ����Canny��Sobel��Scharr���ֺ���
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// ����ȫ�ֱ�����ԭͼ��ԭͼ�ĻҶȰ棬Ŀ��ͼ
Mat srcImage, grayImage, dstImage;
// Canny��Ե�����ر���
Mat cannyDetectEdge;
int cannyLowThreshold = 1;
// Sobel��Ե�����ر���
Mat sobelGradient_x, sobelGradient_y;
Mat sobelAbsGradient_x, sobelAbsGradient_y;
int sobelKernelSize = 1;
// Scharr�˲�������
Mat scharrGradient_x, scharrGradient_y;
Mat scharrAbsGradient_x, scharrAbsGradient_y;

// ȫ�ֺ�������
static void on_Canny(int, void*);
static void on_Sobel(int, void*);
void Scharr();

int main()
{
	srcImage = imread("1.jpg");
	if (!srcImage.data)
	{
		cout << "ͼƬ��ȡʧ�ܣ���ȷ��Ŀ¼���Ƿ����ָ��ͼƬ��\n";
		return -1;
	}
	namedWindow("ԭͼ");
	imshow("ԭͼ", srcImage);

	dstImage.create(srcImage.size(), srcImage.type());
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);

	namedWindow("Canny��Ե���");
	namedWindow("Sobel��Ե���");

	createTrackbar("����ֵ:", "Canny��Ե���", &cannyLowThreshold, 120, on_Canny);
	createTrackbar("����ֵ:", "Sobel��Ե���", &sobelKernelSize, 3, on_Sobel);
	// ���ûص�����
	on_Canny(0, 0);
	on_Sobel(0, 0);

	Scharr();

	while ((char(waitKey(1)) != 'q')) { }
	return 0;
}

static void on_Canny(int, void*)
{
	// ��ʹ��3*3�ں�������
	blur(grayImage, cannyDetectEdge, Size(3, 3));
	// ����Canny����
	Canny(cannyDetectEdge, cannyDetectEdge, cannyLowThreshold, cannyLowThreshold * 3, 3);
	// �Ƚ�dstImage������Ԫ������Ϊ0
	dstImage = Scalar::all(0);
	// ʹ��canny��������ı�ԵͼcannyDetectEdge��Ϊ���룬����ԭͼsrcImage����Ŀ��ͼdstImage
	srcImage.copyTo(dstImage, cannyDetectEdge);
	// ��ʾЧ��ͼ
	imshow("Canny��Ե���", dstImage);
}

static void on_Sobel(int, void*)
{
	// ��x�����ݶ�
	Sobel(srcImage, sobelGradient_x, CV_16S, 1, 0, (2 * sobelKernelSize + 1), 1, 1, BORDER_DEFAULT);
	// ��y�����ݶ�
	Sobel(srcImage, sobelGradient_y, CV_16S, 0, 1, (2 * sobelKernelSize + 1), 1, 1, BORDER_DEFAULT);
	// �������ֵ���������ת����8λ
	convertScaleAbs(sobelGradient_x, sobelAbsGradient_x);
	convertScaleAbs(sobelGradient_y, sobelAbsGradient_y);
	// �ϲ��ݶ�
	addWeighted(sobelAbsGradient_x, 0.5, sobelAbsGradient_y, 0.5, 0, dstImage);
	// ��ʾЧ��ͼ
	imshow("Sobel��Ե���", dstImage);
}

void Scharr()
{
	// x,y�����ݶ�
	Scharr(srcImage, scharrGradient_x, CV_16S, 1, 0, 1, 0, BORDER_DEFAULT);
	Scharr(srcImage, scharrGradient_y, CV_16S, 0, 1, 1, 0, BORDER_DEFAULT);
	// �������ֵ�������ת����8λ
	convertScaleAbs(scharrGradient_x, scharrAbsGradient_x);
	convertScaleAbs(scharrGradient_y, scharrAbsGradient_y);
	// �ϲ��ݶ�
	addWeighted(scharrAbsGradient_x, 0.5, scharrAbsGradient_y, 0.5, 0, dstImage);
	// ��ʾЧ��ͼ
	imshow("Scharr�˲���", dstImage);
}