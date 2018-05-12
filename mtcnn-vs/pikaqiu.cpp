#include "network.h"
#include "mtcnn.h"
#include <time.h>
#pragma comment(lib, "libopenblas.dll.a")

int main()
{
	//��Ϊִ��Ŀ¼�����õ�openblas/x64���ˣ���֤dll���������룬��ʱ��ͼƬ·�������Ҫ����ȥ2��
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