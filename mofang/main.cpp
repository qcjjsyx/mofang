#include <iostream>
#include <vector>
#include "magicglobal.h"
#include "magicCube.h"
using namespace std;
/*
* white 1
* yellow 2
* blue 3
* red 4
* green 5
* orange 6
*/

extern vector<int> white;
extern vector<int> yellow;
extern vector<int> blue;
extern vector<int> red;
extern vector<int> green;
extern vector<int> orange;

int main() {

	magicCube cube;
	cube.initCube();
	cube.showCube();
	if (cube.judge())
		cout << "OK" << endl;
	cube.rotaR();
	cube.showCube();
	if (!cube.judge())
		cout << "NO" << endl;

	//cout << "hello world!" << endl;
	return 0;
}