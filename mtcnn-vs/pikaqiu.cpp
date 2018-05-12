#include "network.h"
#include "mtcnn.h"
#include <time.h>
#pragma comment(lib, "libopenblas.dll.a")

int main()
{
	//因为执行目录被设置到openblas/x64下了，保证dll能正常载入，这时候图片路径就相对要提上去2级
	Mat image = imread("11.jpg");
	mtcnn find(image.cols, image.rows);
	find.findFace(image);
	clock_t start;
	start = clock();
	int ret = find.findFace(image);
	imshow("result", image);
	imwrite("result.jpg", image);
	start = clock() - start;
	cout << ret;
	cout << "time is  " << start / 10e3 << endl;

	waitKey(0);
	image.release();
	return 0;
}