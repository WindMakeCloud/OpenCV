// Mat类显示格式
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
	Mat r = Mat(10, 3, CV_8UC3);                  // 创建r矩阵
	randu(r, Scalar::all(0), Scalar::all(255));   // 用随机数初始化r矩阵(范围0-255)
	
	// OpenCV默认风格
	cout << "r (OpenCV默认风格) = " << endl << r << ";" << endl << endl;
	
	// Python风格
	cout << "r (Python风格) = " << endl << format(r, Formatter::FMT_PYTHON) << ";" << endl << endl;

	// 逗号分隔风格
	cout << "r (逗号分隔风格) = " << endl << format(r, Formatter::FMT_CSV) << ";" << endl << endl;

	// Numpy风格
	cout << "r (Nympy风格) = " << endl << format(r, Formatter::FMT_NUMPY) << ";" << endl << endl;

	// C语言风格
	cout << "r (C语言风格) = " << endl << format(r, Formatter::FMT_C) << ";" << endl << endl;

    return 0;
}

