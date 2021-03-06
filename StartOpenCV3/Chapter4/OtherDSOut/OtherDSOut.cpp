// 其他数据结构的显示
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

int main()
{
	// 定义和输出二维点
	Point2f p(6, 2);
	cout << "【二维点】p = " << p << ";\n\n";

	// 定义和输出三维点
	Point3f p3f(8, 2, 0);
	cout << "【三维点】p3f = " << p3f << ";\n\n";

	// 定义和输出基于Mat类的std::vector
	vector<float> v;
	v.push_back(3);
	v.push_back(5);
	v.push_back(7);
	cout << "【基于Mat的vector】shortvec = " << Mat(v) << ";\n\n";

	// 定义和输出std::vector点
	vector<Point2f> points(20);
	for (size_t i = 0; i < points.size(); ++i)
		points[i] = Point2f((float)(i * 5), (float)(i % 7));
	cout << "【二维点向量】points = " << points << ";\n";

    return 0;
}

