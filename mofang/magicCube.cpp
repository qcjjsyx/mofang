#include "magicCube.h"
#include<iostream>
#include <vector>
#include "magicglobal.h"
#include<string>
using namespace std;

const char color[7] = {'N','W','Y','B','R','G','O'};
extern vector<int> white;
extern vector<int> yellow;
extern vector<int> blue;
extern vector<int> red;
extern vector<int> green;
extern vector<int> orange;


void traversal(vector<vector<int>> matrix) {
	for (vector<vector<int>>::iterator iter = matrix.begin(); iter != matrix.end(); iter++) {
		vector<int> row = *iter;
		for (vector<int>::iterator it = row.begin(); it != row.end(); it++) {
			cout << color[*it] << " ";
		}
		cout << endl;
	}
}

bool judgeSingle(vector<vector<int>> matrix, int num) {
	for (vector<vector<int>>::iterator iter = matrix.begin(); iter != matrix.end(); iter++) {
		vector<int> row = *iter;
		for (vector<int>::iterator it = row.begin(); it != row.end(); it++) {
			if (*it != num)
				return false;
		}
	}
	return true;
}

void magicCube::initCube() {
	this->front = vector<vector<int>>(3, blue);
	this->back = vector<vector<int>>(3, green);
	this->right = vector<vector<int>>(3, red);
	this->left = vector<vector<int>>(3, orange);
	this->up = vector<vector<int>>(3, yellow);
	this->down = vector<vector<int>>(3, white);
}


void magicCube::showCube() {
	vector<vector<int>>::iterator iter;
	vector<int>::iterator it;
	vector<int> row;

	cout << "F:" << endl;
	traversal(this->front);
	cout << "B:" << endl;
	traversal(this->back);
	cout << "R:" << endl;
	traversal(this->right);
	cout << "L:" << endl;
	traversal(this->left);
	cout << "D:" << endl;
	traversal(this->down);
	cout << "U:" << endl;
	traversal(this->up);
}


void magicCube::rotaR() {
	//先计算右面的变换
	swap(this->right[0][1], this->right[1][2]);
	swap(this->right[0][1], this->right[1][0]);
	swap(this->right[2][1], this->right[1][0]);
	swap(this->right[0][0], this->right[0][2]);
	swap(this->right[2][0], this->right[2][2]);
	swap(this->right[0][0], this->right[2][2]);

	//前后交换
	swap(this->front[0][2], this->back[0][2]);
	swap(this->front[1][2], this->back[1][2]);
	swap(this->front[2][2], this->back[2][2]);
	//后上交换
	swap(this->back[0][2], this->up[0][2]);
	swap(this->back[1][2], this->up[1][2]);
	swap(this->back[2][2], this->up[2][2]);
	swap(this->back[0][2], this->back[2][2]);
	//前下交换
	swap(this->front[0][2],this->down[2][2]);
	swap(this->front[1][2], this->down[1][2]);
	swap(this->front[2][2], this->down[0][2]);
	swap(this->front[0][2], this->front[2][2]);


}

void magicCube::rotaL() {

}

void magicCube::rotaU() {

}

void magicCube::rotaD() {

}

void magicCube::rotaF() {

}

void magicCube::rotaB() {

}

bool magicCube::judge() {
	if (judgeSingle(this->down, 1) && judgeSingle(this->up, 2) && judgeSingle(this->right, 4) && judgeSingle(this->left, 6) && judgeSingle(this->front, 3) && judgeSingle(this->back, 5))
		return true;

	return false;

}