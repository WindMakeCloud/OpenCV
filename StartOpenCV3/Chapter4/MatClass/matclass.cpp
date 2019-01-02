// Mat容器的简单应用
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat C = (Mat_<double>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	cout << "C = " << endl << C << endl;
	Mat RowClone = C.row(1).clone();
	cout << "Rowclone = " << endl << RowClone << endl;
    return 0;
}

