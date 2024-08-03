#ifndef MAGICCUBE_H
#define MAGICCUBE_H
#include <iostream>
#include <vector>
#include "magicglobal.h"

using namespace std;
class magicCube
{
private:
	vector<vector<int>> front;
	vector<vector<int>> back;
	vector<vector<int>> left;
	vector<vector<int>> right;
	vector<vector<int>> down;
	vector<vector<int>> up;

public:
	void setCube();
	void rotaL();
	void rotaR();
	void rotaF();
	void rotaB();
	void rotaD();
	void rotaU();
	void showCube();
	void initCube();
	bool judge();


};

#endif
