#ifndef _UTILITY
#define _UTILITY
/*
���ļ���Ҫ������opencv��ȡħ��ͼ��
*/

//wiatKey() ������ͣ�Ĺ���

#include<opencv2/opencv.hpp>
#include<string>
using namespace cv;
using namespace std;

class Utility
{



public:

	/*��ͼ���л�ȡħ��״̬*/
	string readFromImage(string pathB, string pathL, string pathU, string pathR, string pathF, string pathD) {
		Mat B = imread(pathB);
		Mat L = imread(pathL);
		Mat U = imread(pathU);
		Mat R = imread(pathR);
		Mat F = imread(pathF);
		Mat D = imread(pathD);

		string ret = "";
		ret += image2Str(B);
		ret += image2Str(L);
		ret += image2Str(U);
		ret += image2Str(R);
		ret += image2Str(F);
		ret += image2Str(D);

		return ret;
	}

private:
	string image2Str(Mat img) {

	}

};

#endif