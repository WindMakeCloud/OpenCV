// ������ɫͨ��&��ͨ��ͼ����
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

bool MulChanImagBlend();

int main()
{
	system("color 9F");

	if (MulChanImagBlend())
		cout << "���гɹ����õ���Ҫ��ͼ��\n";

	waitKey(0);
	return 0;
}

bool MulChanImagBlend()
{
	// ������ر���
	Mat srcImage;
	Mat logoImage;
	vector<Mat> channels;
	Mat imageBlueChannel;

	// ��ɫͨ������
	// ��ͨ�����-��ɫ��������
	// 1. ����ͼƬ
	logoImage = imread("dota_logo.jpg", 0);
	srcImage = imread("dota_jugg.jpg");

	if (!logoImage.data)
	{
		cout << "��ȡlogoImage����\n";
		return false;
	}
	if (!srcImage.data)
	{
		cout << "��ȡsrcImage����\n";
		return false;
	}

	// 2.����ͨ��ͼ��ת����3����ͨ��ͼ��
	split(srcImage, channels);

	// 3. ��ԭͼ����ɫͨ�����÷��ظ�imageBlueChannel�������ã����ߵȼۣ��ı�һ����һ��Ҳ�ı�
	imageBlueChannel = channels.at(0);

	// 4. ��ԭͼ����ɫͨ��(500,250)�������·���һ�������logoͼ���м�Ȩ������
	// ���õ��Ļ�Ͻ���浽imageBlueChannel��
	addWeighted(imageBlueChannel(Rect(500, 250, logoImage.cols, logoImage.rows)), 1.0,
		logoImage, 0.5, 0, imageBlueChannel(Rect(500, 250, logoImage.cols, logoImage.rows)));

	// 5.��������ͨ�����ºϲ���һ����ͨ��
	merge(channels, srcImage);

	// 6.��ʾЧ��ͼ
	namedWindow("<1>ԭ��+logo��ɫͨ��");
	imshow("<1>ԭ��+logo��ɫͨ��", srcImage);

	// ��ɫͨ������
	// ��ͨ�����-��ɫ��������
	// 0.������ر���
	Mat imageGreenChannel;

	// 1.���¶���ͼƬ
	logoImage = imread("dota_logo.jpg", 0);
	srcImage = imread("dota_jugg.jpg");
	if (!logoImage.data)
	{
		cout << "��ȡlogoImage����\n";
		return false;
	}
	if (!srcImage.data)
	{
		cout << "��ȡsrcImage����\n";
		return false;
	}

	// 2.��һ����ͨ��ͼ��׼����������ͨ��ͼ��
	split(srcImage, channels);

	// 3.��ԭͼ��ɫͨ�������÷��ظ�imageGreenChannel�������ã����ߵȼۣ��ı�һ����һ��Ҳ�ı�
	imageGreenChannel = channels.at(1);
	// 4.��ԭͼ��ɫͨ����(500,250)�������·��������logoͼ����м�Ȩ������
	// ���õ��Ļ�Ͻ������imageGreenChannel
	addWeighted(imageGreenChannel(Rect(500, 250, logoImage.cols, logoImage.rows)), 1.0,
		logoImage, 0.5, 0., imageGreenChannel(Rect(500, 250, logoImage.cols, logoImage.rows)));

	// 5.�����������ĵ�ͨ�����ºϲ���һ����ͨ��
	merge(channels, srcImage);

	// 6.��ʾЧ��ͼ
	namedWindow("<2>ԭ��+logo��ɫͨ��");
	imshow("<2>ԭ��+logo��ɫͨ��", srcImage);

	// ��ɫͨ������
	// ��ͨ�����-��ɫ��������
	// 0.������ر���
	Mat imageRedChannel;

	// 1.���¶���ͼƬ
	logoImage = imread("dota_logo.jpg", 0);
	srcImage = imread("dota_jugg.jpg");
	if (!logoImage.data)
	{
		cout << "��ȡlogoImage����\n";
		return false;
	}
	if (!srcImage.data)
	{
		cout << "��ȡsrcImage����\n";
		return false;
	}

	// 2.��һ����ͨ��ͼ��׼����������ͨ��ͼ��
	split(srcImage, channels);

	// 3.��ԭͼ��ɫͨ�������÷��ظ�imageGreenChannel�������ã����ߵȼۣ��ı�һ����һ��Ҳ�ı�
	imageRedChannel = channels.at(2);
	// 4.��ԭͼ��ɫͨ����(500,250)�������·��������logoͼ����м�Ȩ������
	// ���õ��Ļ�Ͻ������imageRedChannel
	addWeighted(imageRedChannel(Rect(500, 250, logoImage.cols, logoImage.rows)), 1.0,
		logoImage, 0.5, 0., imageRedChannel(Rect(500, 250, logoImage.cols, logoImage.rows)));

	// 5.�����������ĵ�ͨ�����ºϲ���һ����ͨ��
	merge(channels, srcImage);

	// 6.��ʾЧ��ͼ
	namedWindow("<2>ԭ��+logo��ɫͨ��");
	imshow("<2>ԭ��+logo��ɫͨ��", srcImage);

	return true;
}