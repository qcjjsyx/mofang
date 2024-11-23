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

	/*��ͼ���л�ȡħ��״̬
	  ͼ����Ҫ��׼����������Ԥ����Ȳ���
	*/
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
		if (img.empty()) {
			cout << "error:can't load image" << endl;
			return;
		}
		string ret = "";
		int rows = 3, cols = 3;
		int blockWidth = img.cols / cols;
		int blockHeight = img.rows / rows;

		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				// ����С�������
				Rect roi(j * blockWidth, i * blockHeight, blockWidth, blockHeight);
				Mat block = img(roi);

				// ���������ƽ����ɫ
				Scalar avgColor = cv::mean(block);

				// �����ɫ
				string colorName = detectColor(avgColor);
				if (colorName != "Unknown") {
					ret += colorName;
				}
			}
			
		}
		if (ret.length() < 9) {
			cout << "detect error" << endl;
			return " ";
		}
		return ret;
	}

	string detectColor(const Scalar& color) {
		int blue = color[0], green = color[1], red = color[2];

		// ���������ɫ��Χ����Ҫ����ʵ�����������
		if (red > 200 && green < 80 && blue < 80) return "R";
		if (green > 200 && red < 80 && blue < 80) return "G";
		if (blue > 200 && red < 80 && green < 80) return "B";
		if (red > 200 && green > 200 && blue < 80) return "Y";
		if (red > 200 && green > 200 && blue > 200) return "W";
		if (red > 100 && green < 100 && blue < 100) return "O";

		return "Unknown";
	}
};

#endif