#ifndef SOLUTION_H
#define SOLUTION_H
#include "RubikCube.hpp"
#include <vector>
#include <string>
using namespace std;
class Solution {
private: 
	vector<string> moves = { "L", "R", "U", "D", "F", "B","_L","_R","_U","_D","_F","_B"};
		
public: 
	RubikCube block;
	vector < vector<vector<char>>> initialCube;
	Solution(int moves) {
		block = RubikCube();
		block.scramble(moves);
		initialCube = block.cube;

	}
	vector<string> order;
	//因为想不出好的剪枝方法，我觉得DFS是在这方面是垃圾
	bool DFS(int depth, int maxdepth) {
		if (depth > maxdepth) {
			return false;
		}

		for (int i = 0; i < 12; ++i) {
			block.applyRotate(moves[i]);
			order.push_back(moves[i]);
			if (block.isSolved()) {
				for (string it : order) {
					cout << it << " ";
				}
				cout << endl;
				return true;
			}else if (DFS(depth + 1, maxdepth)) {
				return true;
			}
			block.applyRotateInverse(moves[i]);
			order.pop_back();
		}
		return false;
	}



};


#endif