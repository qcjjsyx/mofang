#ifndef _NEWSOLUTION
#define NEWSOLUTION
#include "Search.hpp"
#include "CubeState.hpp"
#include "string"
#include "vector"
#include "iostream"
#include "queue"


using namespace std;

#define MOVE_COUNT 18
#define MOVELIMIT  74943//010 010 010 010 111 111

#define CORNORS_ORIENTATION_SIZE  2187 //3^7
#define EDGES_ORIENTATION_SIZE  2048 //2^11

#define CORNOR_POSITION_SIZE 40320 //8!
#define UD_EDGES_POSITION_SIZE 40320 //8!
#define MIDDLE_EDGE_POSITION_SIZE 24//4!

#define MIDDLE_EDGE_COMBINATION 495//C(4,12)

#define MIDDLE_EDGES_POSITION_ORIENTATION_SIZE 11880  // A(4,12); 




//phase1:只考虑角块方向，棱块方向，以及中间四个棱块的标号
int8_t cornorOrientation[CORNORS_ORIENTATION_SIZE];
int8_t edgeOrientation[EDGES_ORIENTATION_SIZE];
int8_t middleEdgeArrangement[MIDDLE_EDGES_POSITION_ORIENTATION_SIZE];

int cornorOrientationMove[CORNORS_ORIENTATION_SIZE][MOVE_COUNT];
int edgeOrientationMove[EDGES_ORIENTATION_SIZE][MOVE_COUNT];
int middleEdgeArrangementMove[MIDDLE_EDGES_POSITION_ORIENTATION_SIZE][MOVE_COUNT];

int8_t cornorOrientationAndMiddleEdgeCom[CORNORS_ORIENTATION_SIZE * MIDDLE_EDGE_COMBINATION];
int8_t edgeOrientationAndMiddleEdgeCom[EDGES_ORIENTATION_SIZE * MIDDLE_EDGE_COMBINATION];


//phase2:完全复原
//对各个魔方状态到目标状态的步数
int8_t cornorPosition[CORNOR_POSITION_SIZE];
int8_t udEdgePosition[UD_EDGES_POSITION_SIZE];
int8_t middleEdgePosition[MIDDLE_EDGE_POSITION_SIZE];

//cornorPositionMove[father][move] = next:father状态进行了move以后，变成了next状态。
int cornorPositionMove[CORNOR_POSITION_SIZE][MOVE_COUNT];
int udEdgePositionMove[UD_EDGES_POSITION_SIZE][MOVE_COUNT];
int middleEdgePositionMove[MIDDLE_EDGE_POSITION_SIZE][MOVE_COUNT];

int8_t cornorPositionAndMiddleEdgePos[CORNOR_POSITION_SIZE * MIDDLE_EDGE_POSITION_SIZE];
int8_t udEdgePositionAndMiddleEdgePos[UD_EDGES_POSITION_SIZE * MIDDLE_EDGE_POSITION_SIZE];


class NewSolution
{
public:
	NewSolution() {
		cout << "开始初始化" << endl;
		init();
		cout << "初始化完成" << endl;
	};
	~NewSolution() {};


	void solve() {
		cout << "hello";
		cout << (int)cornorPosition[0];
	}

private:

	int factorial_8[8] = { 1,2,6,24,120,720,5040,40320 };
	int factorial_4[4] = { 1,2,6,24 };

	////phase1:只考虑角块方向，棱块方向，以及中间四个棱块的标号
	//int8_t* cornorOrientation = new int8_t[CORNORS_ORIENTATION_SIZE];
	//int8_t* edgeOrientation = new int8_t[EDGES_ORIENTATION_SIZE];
	//int8_t* middleEdgeArrangement = new int8_t[MIDDLE_EDGES_POSITION_ORIENTATION_SIZE];

	//int cornorOrientationMove[CORNORS_ORIENTATION_SIZE][MOVE_COUNT];
	//int edgeOrientationMove[EDGES_ORIENTATION_SIZE][MOVE_COUNT];
	//int middleEdgeArrangementMove[MIDDLE_EDGES_POSITION_ORIENTATION_SIZE][MOVE_COUNT];

	//int8_t* cornorOrientationAndMiddleEdgeCom = new int8_t[CORNORS_ORIENTATION_SIZE * MIDDLE_EDGE_COMBINATION];
	//int8_t* edgeOrientationAndMiddleEdgeCom = new int8_t[EDGES_ORIENTATION_SIZE * MIDDLE_EDGE_COMBINATION];


	////phase2:完全复原
	////对各个魔方状态到目标状态的步数
	//int8_t* cornorPosition = new int8_t[CORNOR_POSITION_SIZE];
	//int8_t* udEdgePosition = new int8_t[UD_EDGES_POSITION_SIZE];
	//int8_t* middleEdgePosition = new int8_t[MIDDLE_EDGE_POSITION_SIZE];

	////cornorPositionMove[father][move] = next:father状态进行了move以后，变成了next状态。
	//int cornorPositionMove[CORNOR_POSITION_SIZE][MOVE_COUNT];
	//int udEdgePositionMove[UD_EDGES_POSITION_SIZE][MOVE_COUNT];
	//int middleEdgePositionMove[MIDDLE_EDGE_POSITION_SIZE][MOVE_COUNT];

	//int8_t* cornorPositionAndMiddleEdgePos = new int8_t[CORNOR_POSITION_SIZE * MIDDLE_EDGE_POSITION_SIZE];
	//int8_t* udEdgePositionAndMiddleEdgePos = new int8_t[UD_EDGES_POSITION_SIZE * MIDDLE_EDGE_POSITION_SIZE];




	vector<cube_t> middleEdgePos;


	int cantor(int* nums, int size, int* factorial_n) {
		int ret = 0, sum = 0;
		for (int i = 0; i < size; i++) {
			for (int j = i + 1; j < size; j++)
				if (nums[j] < nums[i])
					sum++;

			ret += sum * factorial_n[size - i - 2];
			sum = 0;
		}
		return ret;
	}



	int combine(int m, int n) {
		if (m < n) return 0;
		int distribution = 1;
		int Arrangement = 1;
		for (int i = 0; i < n; i++) {
			Arrangement *= m - i;
			distribution *= n - i;
		}
		return Arrangement / distribution;
	}

	int combineIndex(int* nums, int m) {

		int tarIndex = 1;
		int ret = 0;
		for (int i = m - 1; i >= 0; i--) {
			if (nums[i] > 0) {
				ret += combine(m - 1 - i, tarIndex);
				tarIndex++;
			}
		}
		return ret;
	}

	void init() {
		cube_t cube;
		memset(cornorPositionMove, 0xff, sizeof(int) * CORNORS_ORIENTATION_SIZE * MOVE_COUNT);
		phase2FillBuffer(cube, cornorPosition, CORNOR_POSITION_SIZE, cornors_perm_index);
		memset(udEdgePositionMove, 0xff, sizeof(int) * UD_EDGES_POSITION_SIZE * MOVE_COUNT);
		phase2FillBuffer(cube, udEdgePosition, UD_EDGES_POSITION_SIZE, ud_edges_perm_index);
		memset(middleEdgePositionMove, 0xff, sizeof(int) * MIDDLE_EDGE_POSITION_SIZE * MOVE_COUNT);
		phase2FillBuffer(cube, middleEdgePosition, MIDDLE_EDGE_POSITION_SIZE, middle_edges_perm_index);



		memset(middleEdgeArrangementMove, 0xff, sizeof(int) * MIDDLE_EDGES_POSITION_ORIENTATION_SIZE * MOVE_COUNT);
		phase1FillBuffer(cube, middleEdgeArrangement, MIDDLE_EDGES_POSITION_ORIENTATION_SIZE, me_combine_index);
		memset(cornorOrientationMove, 0xff, sizeof(int) * CORNORS_ORIENTATION_SIZE * MOVE_COUNT);
		phase1FillBuffer(cube, cornorOrientation, CORNORS_ORIENTATION_SIZE, co_index);
		memset(edgeOrientationMove, 0xff, sizeof(int) * EDGES_ORIENTATION_SIZE * MOVE_COUNT);
		phase1FillBuffer(cube, edgeOrientation, EDGES_ORIENTATION_SIZE, eo_index);


		phase2Pre();
		phase1Pre();


	}

	


	void phase2FillBuffer(cube_t cube, int8_t* dest, int destSize, enum phase_type type) {
		queue<pair<cube_t, int>> q;
		q.push(make_pair(cube, 0));
		memset(dest, 0xff, destSize);
		if (type == middle_edges_perm_index) {
			middleEdgePos.push_back(cube);
		}
		dest[0] = 0;
		while (!q.empty()) {
			pair<cube_t, int> front = q.front();
			int fatherIndex = calculateIndex(front.first, type);
			for (int move = 0; move < 18; ++move) {
				if (MOVELIMIT & (1 << move)) {//规定可以用的操作，具体看cubeState
					cube_t current = CubeState::moveRotate(move, front.first);
					int nextIndex = calculateIndex(current, type);

					if (type == cornors_perm_index) {
						cornorPositionMove[fatherIndex][move] = nextIndex;
					}
					else if (type == ud_edges_perm_index) {
						udEdgePositionMove[fatherIndex][move] = nextIndex;
					}
					else if (type == middle_edges_perm_index) {
						middleEdgePositionMove[fatherIndex][move] = nextIndex;
					}

					if (dest[nextIndex] == -1) {
						int step = front.second;
						dest[nextIndex] = step + 1;
						q.push(make_pair(current, step + 1));
						if (type == middle_edges_perm_index) {
							middleEdgePos.push_back(current);
						}
					}

				}
			}
			q.pop();
		}
		
	}



	void phase1FillBuffer(cube_t cube, int8_t* dest, int destSize, enum phase_type type) {
		queue<pair<cube_t, int>>q;
		memset(dest, 0xff, destSize);
		q.push(make_pair(cube, 0));
		dest[0] = 0;
		if (type == me_combine_index) {
			for (int i = 0; i < MIDDLE_EDGE_POSITION_SIZE; ++i) {
				q.push(make_pair(middleEdgePos[i], 0));
				int index = calculateIndex(middleEdgePos[i], me_combine_index);
				dest[index] = 0;
			}
		}
		while (!q.empty()) {
			pair<cube_t, int> front = q.front();
			int fatherIndex = calculateIndex(front.first, type);
			for (int move = 0; move < 18; ++move) {
				cube_t current = CubeState::moveRotate(move, front.first);
				int nextIndex = calculateIndex(current, type);
				if (type == co_index) {
					cornorOrientationMove[fatherIndex][move] = nextIndex;
				}
				else if (type == eo_index) {
					edgeOrientationMove[fatherIndex][move] = nextIndex;
				}
				else if (type == me_combine_index) {
					middleEdgeArrangementMove[fatherIndex][move] = nextIndex;
				}

				if (dest[nextIndex] == -1) {
					int step = front.second;
					dest[nextIndex] = step + 1;
					q.push(make_pair(current, step + 1));
				}
			}
			q.pop();
		}

	}


	void phase2Pre() {
		memset(cornorPositionAndMiddleEdgePos, 0xff, CORNOR_POSITION_SIZE * MIDDLE_EDGE_POSITION_SIZE);
		phase2_t start1;
		start1.cornor = 0;
		start1.edge2 = 0;
		queue<pair<phase2_t, int>>q;
		q.push(make_pair(start1, 0));
		cornorPositionAndMiddleEdgePos[0] = 0;


		while (!q.empty()) {
			pair<phase2_t, int> front = q.front();
			int depth = front.second;
			for (int move = 0; move < 18; ++move) {
				if (MOVELIMIT & (1 << move)) {
					phase2_t newState;
					newState.cornor = cornorPositionMove[front.first.cornor][move];
					newState.edge2 = middleEdgeArrangementMove[front.first.edge2][move];
					if (cornorPositionAndMiddleEdgePos[newState.cornor * 24 + newState.edge2] == -1) {
						cornorPositionAndMiddleEdgePos[newState.cornor * 24 + newState.edge2] = depth + 1;
						q.push(make_pair(newState, depth + 1));
					}
				}
			}

			q.pop();
		}


		memset(udEdgePositionAndMiddleEdgePos, 0xff, UD_EDGES_POSITION_SIZE * MIDDLE_EDGE_POSITION_SIZE);
		phase2_t start2;
		queue<pair<phase2_t, int>> q2;
		start2.edge1 = 0;
		start2.edge2 = 0;
		q2.push(make_pair(start2, 0));
		udEdgePositionAndMiddleEdgePos[0] = 0;
		while (!q2.empty()) {
			pair<phase2_t, int> front = q2.front();
			int depth = front.second;
			for (int move = 0; move < 18; ++move) {
				if (MOVELIMIT & (1 << move)) {
					phase2_t newState;
					newState.edge1 = udEdgePositionMove[front.first.edge1][move];
					newState.edge2 = middleEdgeArrangementMove[front.first.edge2][move];
					if (udEdgePositionAndMiddleEdgePos[newState.edge1 * 24 + newState.edge2] == -1) {
						udEdgePositionAndMiddleEdgePos[newState.edge1 * 24 + newState.edge2] = depth + 1;
						q2.push(make_pair(newState, depth + 1));
					}
				}
			}
			q2.pop();
		}

	}




	void phase1Pre() {
		phase1_t start;
		start.co = 0;
		start.middle_edge_combination = 0;
		queue<pair<phase1_t, int>>q;
		q.push(make_pair(start, 0));
		memset(cornorOrientationAndMiddleEdgeCom, 0xff, CORNORS_ORIENTATION_SIZE * MIDDLE_EDGE_COMBINATION);
		cornorOrientationAndMiddleEdgeCom[0] = 0;
		while (!q.empty()) {
			pair<phase1_t, int> front = q.front();
			int depth = front.second;
			for (int move = 0; move < 18; ++move) {
				phase1_t newState;
				newState.co = cornorOrientationMove[front.first.co][move];
				newState.middle_edge_combination = middleEdgeArrangementMove[front.first.middle_edge_combination][move];
				if (cornorOrientationAndMiddleEdgeCom[newState.co*MIDDLE_EDGE_COMBINATION+newState.middle_edge_combination/24] == -1) {
					q.push(make_pair(newState, depth + 1));
					cornorOrientationAndMiddleEdgeCom[newState.co * MIDDLE_EDGE_COMBINATION + newState.middle_edge_combination / 24] = depth+1;
				}
			}
			q.pop();
		}


		phase1_t start2;
		start2.eo = 0;
		start2.middle_edge_combination = 0;
		queue<pair<phase1_t, int>> q2;
		q2.push(make_pair(start2, 0));
		memset(edgeOrientationAndMiddleEdgeCom, 0xff, EDGES_ORIENTATION_SIZE * MIDDLE_EDGE_COMBINATION);
		edgeOrientationAndMiddleEdgeCom[0] = 0;
		while (!q.empty()) {
			pair<phase1_t, int> front = q2.front();
			int depth = front.second;
			for (int move = 0; move < 18; ++move) {
				phase1_t newState1;
				newState1.eo = edgeOrientationMove[front.first.eo][move];
				newState1.middle_edge_combination = middleEdgeArrangementMove[front.first.middle_edge_combination][move];
				if (edgeOrientationAndMiddleEdgeCom[newState1.eo * MIDDLE_EDGE_COMBINATION + newState1.middle_edge_combination / 24] == -1) {
					q2.push(make_pair(newState1, depth + 1));
					edgeOrientationAndMiddleEdgeCom[newState1.eo * MIDDLE_EDGE_COMBINATION + newState1.middle_edge_combination / 24] = depth + 1;
				}
			}
			q2.pop();
		}
	}

	int calculateIndex(cube_t cube, int type) {
		int ret = 0;
		switch (type) {
		case eo_index: {
			for (int i = 0; i < 11; ++i) {
				ret = ret * 2 + cube.edgeOrientation[i];
			}
		}
					 break;
		case co_index: {
			for (int i = 0; i < 7; ++i) {
				ret = ret * 3 + cube.cornorOrientation[i];
			}
		}
					 break;
		case me_combine_index: {
			int x = 0;
			int combineArr[12] = { 0 };
			int positionArr[4] = { 0 };
			for (int i = 0; i < 12; ++i) {
				if (cube.edgeIndex[i] > 8) {
					combineArr[i] = 1;
					positionArr[x] = cube.edgeIndex[i] - 8;
					x++;
				}
			}
			int comIndex = combineIndex(combineArr, 12);
			int posIndex = cantor(positionArr, 4, factorial_4);
			ret = comIndex * 24 + posIndex;
		}
							 break;

		case ud_edges_perm_index: {
			int positionArr[8] = { 0 };
			for (int i = 0; i < 8; ++i) {
				positionArr[i] = cube.edgeIndex[i];
			}
			ret = cantor(positionArr, 8, factorial_8);
		}
								break;

		case middle_edges_perm_index: {
			int positionArr[4] = { 0 };
			for (int i = 0; i < 4; ++i) {
				positionArr[i] = cube.edgeIndex[i + 8] - 8;
			}
			ret = cantor(positionArr, 4, factorial_4);
		}
									break;

		case cornors_perm_index: {
			int positionArr[8] = { 0 };
			for (int i = 0; i < 8; ++i) {
				positionArr[i] = cube.cornorIndex[i];
			}
			ret = cantor(positionArr, 8, factorial_8);
		}
							   break;
		}

		return ret;
	}


};







#endif