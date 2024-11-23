#ifndef _UTILITY
#define _UTILITY
/*
该文件主要是用于opencv读取魔方图像。
*/

//wiatKey() 用来暂停的功能

#include<opencv2/opencv.hpp>
#include<string>
using namespace cv;
using namespace std;

class Utility
{



public:

	/*从图像中获取魔方状态*/
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