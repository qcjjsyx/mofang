#ifndef SOLUTION_H
#define SOLUTION_H
#include "RubikCube.hpp"
#include <vector>
#include <string>
using namespace std;
class Solution {
private: vector<string> moves = { "L", "R", "U", "D", "F", "B" };

public: 
	RubikCube cube;
	Solution(int moves=20) {
		cube = RubikCube();
		cube.scramble(moves);

	}

	bool DFS() {

	}




};


#endif