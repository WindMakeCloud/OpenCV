// ������ˮ���floodFill����ʵ����ɫ���
// ����PhotoShopħ��������

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

Mat srcImage, dstImage, grayImage, maskImage; // ����ԭʼͼ��Ŀ��ͼ���Ҷ�ͼ����ģ
int FillMode = 1;   // ��ˮ���ģʽ
int MaxLowDifference = 20, MaxUpDifference = 20;    // �������ֵ���������ֵ
int Connectivity = 4;    // ��ʾfloodFill������ʶ���ڰ�λ����ֵͨ
bool IsColor = true;     // �Ƿ�Ϊ��ɫͼ��bool��ʶ
bool UseMask = false;    // �Ƿ���ʾ��ģ���ڵ�bool��ʶ
int NewMaskVal = 255;    // �µ����»��Ƶ�����ֵ

static void onMouse(int event, int x, int y, int, void*);

int main()
{
	// ����ԭͼ
	srcImage = imread("1.jpg");
	if (!srcImage.data)
	{
		cout << "��ȡͼƬ������ȷ��Ŀ¼���Ƿ���ָ����ͼƬ!\n";
		return -1;
	}
	// ��ʾԭͼ
	namedWindow("ԭͼ");
	imshow("ԭͼ", srcImage);

	srcImage.copyTo(dstImage);
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);   // ��ͨ����ɫͼת��Ϊ�Ҷ�ͼ
	maskImage.create(srcImage.rows + 2, srcImage.cols + 2, CV_8UC1);  // ��ʼ����ģmask

	namedWindow("Ч��ͼ");

	// �����켣��
	createTrackbar("�������ֵ", "Ч��ͼ", &MaxLowDifference, 255, 0);
	createTrackbar("�������ֵ", "Ч��ͼ", &MaxUpDifference, 255, 0);

	// ���ص�����
	setMouseCallback("Ч��ͼ", onMouse, 0);

	// ѭ����ѯ����
	while (1)
	{
		// ����ʾЧ��ͼ
		imshow("Ч��ͼ", IsColor ? dstImage : grayImage);

		// ��ȥ���̰���
		int c = waitKey(0);
		// Esc���£������˳�
		if ((c & 255) == 27)
		{
			cout << "�����˳�......\n";
			break;
		}

		// ���ݰ�����ͬ�����и��ֲ���
		switch ((char)c)
		{
		// ����1���£�Ч��ͼ�ڻҶ�ͼ��ɫͼ֮���л�
		case '1' :
			if (IsColor)  // ��ԭ��Ϊ��ɫ��תΪ�Ҷ�ͼ�����ҽ���ģmask����Ԫ������Ϊ0
			{
				cout << "���̡�1�����£��л���ɫ/�Ҷ�ģʽ����ǰ����Ϊ����ɫ���л������Ҷȡ�\n";
				cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
				maskImage = Scalar::all(0);
				IsColor = false;
			}
			else  // ��ԭ��Ϊ�Ҷ�ͼ��תΪ��ɫ�����ҽ�mask����ԭɫ����Ϊ0
			{
				cout << "���̡�1�����£��л���ɫ/�Ҷ�ģʽ����ǰ����Ϊ���Ҷȡ��л�������ɫ��\n";
				srcImage.copySize(dstImage);
				maskImage = Scalar::all(0);
				IsColor = true;
			}
			break;
		// ����2���£���ʾ/������ģ����
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
		// ����3���£��ָ�ԭʼͼ��
		case '3' :
			cout << "���̡�3�����£��ָ�ԭʼͼ��\n";
			srcImage.copyTo(dstImage);
			cvtColor(dstImage, grayImage, COLOR_BGR2GRAY);
			maskImage = Scalar::all(0);
			break;
		// ����4����,ʹ�ÿշ�Χ����ˮ���
		case '4' :
			cout << "���̡�4�����£�ʹ�ÿշ�Χ����ˮ���\n";
			FillMode = 0;
			break;
		// ����5���£�ʹ�ý��䡢�̶���Χ����ˮ���
		case '5' :
			cout << "������5�����£�ʹ�ý��䡢�̶���Χ����ˮ���\n";
			FillMode = 1;
			break;
		// ����6���£�ʹ�ý��䡢������Χ���������
		case '6' :
			cout << "������6�����£�ʹ�ý��䡢������Χ����ˮ���\n";
			FillMode = 2;
			break;
		// ����7���£�������ʶ���ĵͰ�λʹ��4λ������ģʽ
		case '7' :
			cout << "������7�����£�������ʶ���ĵͰ�λʹ��4λ������ģʽ\n";
			Connectivity = 4;
			break;
		// ����8���£�������ʶ���ĵͰ�λʹ��8λ������ģʽ
		case '8' :
			cout << "������8�����£�������ʶ���ĵͰ�λʹ��8λ������ģʽ\n";
			Connectivity = 8;
			break;
		}
	}

	return 0;
}

// �����Ϣ�ص�����
static void onMouse(int event, int x, int y, int, void*)
{
	// ��������û�а��£��򷵻�
	if (event != EVENT_LBUTTONDOWN)
		return;

	// 1.����floodFill����֮ǰ�Ĳ���׼��
	Point seed = Point(x, y);   // ��������
	int LowDifference = FillMode == 0 ? 0 : MaxLowDifference;  // �շ�Χ����ˮ��䣬��ֵ��Ϊ0��������Ϊȫ����󸴲�
	int UpDifference = FillMode == 0 ? 0 : MaxUpDifference;    // �շ�Χ����ˮ��䣬��ֵ��Ϊ0��������Ϊȫ����󸴲�
	// ��ʶ����0~7λΪConnectivity��8~15λΪNewMaskVal����8λ��ֵ��16~23λΪFLOODFILL_FIXED_RANGE��0
	int flags = Connectivity + (NewMaskVal << 8) + (FillMode == 1 ? FLOODFILL_FIXED_RANGE : 0);
	// �������BGRֵ���������һ��0~255֮���ֵ
	int b = (unsigned)theRNG() & 255;
	int g = (unsigned)theRNG() & 255;
	int r = (unsigned)theRNG() & 255;
	Rect ccomp;   // �����ػ��������С�߽��������
	// ���ػ��������ص���ֵ
	Scalar newVal = IsColor ? Scalar(b, g, r) : Scalar(r*0.299 + g * 0.587 + b * 0.114);
	// Ŀ��ͼ�ĸ�ֵ
	Mat dst = IsColor ? dstImage : grayImage;
	int area;

	// 2.��ʽ����flooFill����
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
	imshow("Ч��ͼ", dst);
	cout << area << " �����ر��ػ�\n";
}