// �ۺ�ʵ������̬ѧ�˲�
// �������㡢��ʴ/���͡���ñ/��ñ

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <imgproc.hpp>

using namespace std;
using namespace cv;

Mat srcImage, dstImage;           // ԭʼͼ��Ч��ͼ
int ElementShape = MORPH_RECT;    // Ԫ�ؽṹ����״

// �������յ�Trackbarλ�ò���
int MaxIterationNum = 10;
int OpenCloseNum = 0;
int ErodeDilateNum = 0;
int TopBlackHatNum = 0;

// �ص���������
static void on_OpenClose(int, void*);
static void on_ErodeDilate(int, void*);
static void on_TopBlackHat(int, void*);
static void ShowHelpText();   // ������Ϣ

int main()
{
	// ��ʾ������Ϣ
	ShowHelpText();

	// ����ԭͼ
	srcImage = imread("1.jpg");
	if (!srcImage.data)
	{
		cout << "��ȡͼƬ������ȷ��Ŀ¼����ָ��ͼƬ��\n";
		return -1;
	}

	// ��ʾԭʼͼ
	namedWindow("ԭͼ");
	imshow("ԭͼ", srcImage);

	// ������������
	namedWindow("������/������");
	namedWindow("��ʴ/����");
	namedWindow("��ñ/��ñ");

	// ������ֵ
	OpenCloseNum = 9;
	ErodeDilateNum = 9;
	TopBlackHatNum = 2;

	// �������ڴ����켣��
	createTrackbar("����ֵ", "������/������", &OpenCloseNum, MaxIterationNum * 2 + 1, on_OpenClose);
	createTrackbar("����ֵ", "��ʴ/����", &ErodeDilateNum, MaxIterationNum * 2 + 1, on_ErodeDilate);
	createTrackbar("����ֵ", "��ñ/��ñ", &TopBlackHatNum, MaxIterationNum * 2 + 1, on_TopBlackHat);

	// ��ѯ��ȡ������Ϣ
	while (1)
	{
		int c;

		// ִ�лص�����
		on_OpenClose(OpenCloseNum, 0);
		on_ErodeDilate(ErodeDilateNum, 0);
		on_TopBlackHat(TopBlackHatNum, 0);

		// ��ȡ����
		c = waitKey(0);

		// ����Q����Esc�����˳�
		if ((char)c == 'q' || (char)c == 27)
			break;
		// ���¼��̰���1��ʹ����Բ(Elliptic)�ṹԪ��MORPH_ELLIPSE
		if ((char)c == 49)  // ���̰���1��ASII��Ϊ49
			ElementShape = MORPH_ELLIPSE;
		// ���¼��̰���2��ʹ�þ��νṹԪ��MORPH_RECT
		else if ((char)c == 50)  // ���̰���2��ASII��Ϊ50
			ElementShape = MORPH_RECT;
		// ���¼��̰���3��ʹ��ʮ���νṹԪ��MORPH_CROSS
		else if ((char)c == 51)  // ���̰���3��ASII��Ϊ51
			ElementShape = MORPH_CROSS;
		// ���¼��̰���space���ھ��Ρ���Բ��ʮ���νṹԪ����ѭ��
		else if ((char)c == ' ')
			ElementShape = (ElementShape + 1) % 3;
	}
	return 0;
}

static void on_OpenClose(int, void*)
{
	// ƫ�����Ķ���
	int offset = OpenCloseNum - MaxIterationNum;           // ƫ����
	int Absolute_offset = offset > 0 ? offset : -offset;   // ƫ��������ֵ
	// �Զ����
	Mat element = getStructuringElement(
		ElementShape,
		Size(Absolute_offset * 2 + 1, Absolute_offset * 2 + 1),
		Point(Absolute_offset, Absolute_offset));
	// ���в���
	if (offset < 0)
		morphologyEx(srcImage, dstImage, MORPH_OPEN, element);
	else
		morphologyEx(srcImage, dstImage, MORPH_CLOSE, element);
	// ��ʾͼ��
	imshow("������/������", dstImage);
}

static void on_ErodeDilate(int, void*)
{
	// ƫ�������趨
	int offset = ErodeDilateNum - MaxIterationNum;   // ƫ����
	int Absolute_offset = offset > 0 ? offset : -offset;  // ����ƫ����
	// �Զ����
	Mat element = getStructuringElement(
		ElementShape,
		Size(Absolute_offset * 2 + 1, Absolute_offset * 2 + 1),
		Point(Absolute_offset, Absolute_offset)
	);
	// ���в���
	if (offset < 0)
		erode(srcImage, dstImage, element);
	else
		dilate(srcImage, dstImage, element);
	// ��ʾͼ��
	imshow("��ʴ/����", dstImage);
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
	imshow("��ñ/��ñ", dstImage);
}

void ShowHelpText()
{
	cout << "\n    �����켣���۲�ͼƬ����Ч��\n\n"
		<< "    ��������˵����\n"
		<< "              ���̰�����Esc����Q��- �˳�����\n"
		<< "              ���̰�����1��- ʹ����Բ�ṹԪ��\n"
		<< "              ���̰�����2��- ʹ�þ��νṹԪ��\n"
		<< "              ���̰�����3��- ʹ��ʮ���νṹԪ��\n"
		<< "              ���̰������ո�- �ھ��Ρ���Բ��ʮ���νṹԪ����ѭ��\n";
}