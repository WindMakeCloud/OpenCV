// ʹ��dft()������ͼ�����DFT������Ƶ��ͼ
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;

int main()
{
	// 1.�ԻҶ�ģʽ��ȡԭʼͼ����ʾ
	Mat srcImage = imread("1.jpg", 0);
	if (!srcImage.data)
	{
		printf("��ȡͼƬ������ȷ��Ŀ¼���Ƿ��ж�ȡָ��ͼƬ��\n");
		return -1;
	}
	imshow("ԭʼͼ��", srcImage);

	// 2.������ͼ��������ѳߴ磬�߽���0����
	int m = getOptimalDFTSize(srcImage.rows);
	int n = getOptimalDFTSize(srcImage.cols);
	// ����ӵ����س�ʼ��Ϊ0
	Mat padded;
	copyMakeBorder(srcImage, padded, 0, m - srcImage.rows, 0, n - srcImage.cols, BORDER_CONSTANT, Scalar::all(0));

	// 3.ΪDFT�Ľ����ʵ�����鲿������ռ�
	// ��planes������Ϻϲ���һ����ͨ������complexI
	Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
	Mat complexI;
	merge(planes, 2, complexI);

	// 4.���о͵�DFT
	dft(complexI, complexI);

	// 5.������ת��Ϊ��ֵ����=>log(1+sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
	split(complexI, planes);   // ����ͨ������ֽ�ɼ�����ͨ������ planes[0] = Re(DFT(I)), planes[1] = Im(DFT(I))
	magnitude(planes[0], planes[1], planes[0]);  // plane[0] = magnitude
	Mat magnitudeImage = planes[0];

	// 6.���ж����߶�����
	magnitudeImage += Scalar::all(1);
	log(magnitudeImage, magnitudeImage);  // ����Ȼ����

	// 7.���к��طֲ�����ͼ����
	// ���������л��У�����Ƶ�ײü�
	magnitudeImage = magnitudeImage(Rect(0, 0, magnitudeImage.cols & -2, magnitudeImage.rows & -2));
	// ��������DFTͼ���е����ޣ�ʹ��ԭ��λ��ͼ������
	int cx = magnitudeImage.cols / 2;
	int cy = magnitudeImage.rows / 2;
	Mat q0(magnitudeImage, Rect(0, 0, cx, cy));   // ROI���������
	Mat q1(magnitudeImage, Rect(cx, 0, cx, cy));  // ROI���������
	Mat q2(magnitudeImage, Rect(0, cy, cx, cy));  // ROI���������
	Mat q3(magnitudeImage, Rect(cx, cy, cx, cy)); // ROI���������
	// �������ޣ����ϻ����£�
	Mat temp;
	q0.copyTo(temp);
	q3.copyTo(q0);
	temp.copyTo(q3);
	// �������ޣ����ϻ����£�
	q1.copyTo(temp);
	q2.copyTo(q1);
	temp.copyTo(q2);

	// 8.��һ������0��1֮��ĸ���ֵ������任Ϊ���ӵ�ͼ���ʽ
	normalize(magnitudeImage, magnitudeImage, 0, 1, NORM_MINMAX);

	// 9.��ʾЧ��ͼ
	imshow("Ƶ�׷�ֵ", magnitudeImage);

	waitKey(0);
	return 0;
}