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

	/*从图像中获取魔方状态
	  图像需要精准，后续考虑预处理等操作
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


	string readFromCamera() {
		VideoCapture capture(0);
		//string writePath = "../temp/";
		int i = 0;
		Mat B, L, U, R, F, D;
		while (true)
		{
			if (i == 6) break;
			
			Mat frame;
			capture >> frame;
			rectangle(frame, Point(170, 90), Point(470, 390), Scalar(0, 0, 255), 3, 1, 0);
			//cout << frame.size() << endl;
			if (32 == waitKey(20)&&i==0) {			//空格拍照
				/*string name = writePath + to_string(i) + ".jpg";
				imwrite(name, frame);
				cout << name << endl;*/
				cout << 'B' << endl;
				B = frame;
				i++;
			}

			if (32 == waitKey(20) && i == 1) {			//空格拍照
				cout << 'L' << endl;
				L = frame;
				i++;
			}

			if (32 == waitKey(20) && i == 2) {			//空格拍照
				cout << 'U' << endl;
				U = frame;
				i++;
			}

			if (32 == waitKey(20) && i == 3) {			//空格拍照
				cout << 'R' << endl;
				R = frame;
				i++;
			}
			if (32 == waitKey(20) && i == 4) {			//空格拍照
				cout << 'F' << endl;
				F = frame;
				i++;
			}

			if (32 == waitKey(20) && i == 5) {			//空格拍照
				cout << 'D' << endl;
				D = frame;
				i++;
			}

			imshow("读取视频", frame);//640*480
			waitKey(20);	//延时30
		}
		cout << "采集完成" << endl;
		B = B(Rect(170, 90, 470, 390));
		L = L(Rect(170, 90, 470, 390));
		U = U(Rect(170, 90, 470, 390));
		R = R(Rect(170, 90, 470, 390));
		F = F(Rect(170, 90, 470, 390));
		D = D(Rect(170, 90, 470, 390));


		string ret = "";
		ret += image2Str(B);
		ret += image2Str(L);
		ret += image2Str(U);
		ret += image2Str(R);
		ret += image2Str(F);
		ret += image2Str(D);
		return ret;
	}

	/*从颜色到面的转换，记录原始状态
	白色：D, 黄色：U, 蓝色：F, 红色：R, 绿色：B, 橙色：L*/
	string trans(string from) {
		string to = from;
		for (int i = 0; i < from.length(); ++i) {
			if (from[i] == 'W') to[i] = 'D';
			if (from[i] == 'Y') to[i] = 'U';
			if (from[i] == 'B') to[i] = 'F';
			if (from[i] == 'R') to[i] = 'R';
			if (from[i] == 'G') to[i] = 'B';
			if (from[i] == 'O') to[i] = 'L';
		}
		//to[54] = '\0';
		return to;
	}
private:
	string image2Str(Mat img) {
		if (img.empty()) {
			cout << "error:can't load image" << endl;
			return " ";
		}
		string ret = "";
		int rows = 3, cols = 3;
		int blockWidth = img.cols / cols;
		int blockHeight = img.rows / rows;

		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				// 计算小块的区域
				Rect roi(j * blockWidth, i * blockHeight, blockWidth, blockHeight);
				Mat block = img(roi);

				// 计算区域的平均颜色
				Scalar avgColor = cv::mean(block);

				// 检测颜色
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

		// 定义基本颜色范围（需要根据实际情况调整）
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