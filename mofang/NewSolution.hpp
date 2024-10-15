#ifndef _NEWSOLUTION
#define NEWSOLUTION
#include "Search.hpp"
#include "CubeState.hpp"
#include "string"
#include "vector"
#include "iostream"

using namespace std;

#define MOVE_COUNT 18

#define CORNORS_ORIENTATION_SIZE  2187 //3^7
#define EDGES_ORIENTATION_SIZE  2048 //2^11

#define CORNOR_POSITION_SIZE 40320 //8!
#define UD_EDGES_POSITION_SIZE 40320 //8!
#define MIDDLE_EDGE_POSITION_SIZE 24//4!

#define MIDDLE_EDGE_COMBINATION 495//C(4,12)

#define MIDDLE_EDGES_POSITION_ORIENTATION_SIZE 11880  // A(4,12); 




class NewSolution
{
public:
	NewSolution();
	~NewSolution();


	void solve(cube_t cube) {

	}

private:

	int factorial_8[8] = { 1,2,6,24,120,720,5040,40320 };
	int factorial_4[4] = { 1,2,6,24 };

	//phase1:只考虑角块方向，棱块方向，以及中间四个棱块的标号
	int8_t cornorOrientation[CORNORS_ORIENTATION_SIZE];
	int8_t edgeOrientation[EDGES_ORIENTATION_SIZE];
	int8_t middleEdgePositionOrientation[MIDDLE_EDGES_POSITION_ORIENTATION_SIZE];

	int cornorOrientationMove[CORNORS_ORIENTATION_SIZE][MOVE_COUNT];
	int edgeOrientationMove[EDGES_ORIENTATION_SIZE][MOVE_COUNT];
	int middleEdgePositionOrientationMove[MIDDLE_EDGES_POSITION_ORIENTATION_SIZE][MOVE_COUNT];

	int8_t cornorOrientationAndMiddleEdgeCom[CORNORS_ORIENTATION_SIZE * MIDDLE_EDGE_COMBINATION];
	int8_t edgeOrientationAndMiddleEdgeCom[EDGES_ORIENTATION_SIZE * MIDDLE_EDGE_COMBINATION];


	//phase2:完全复原
	int8_t cornorPosition[CORNOR_POSITION_SIZE];
	int8_t udEdgePosition[UD_EDGES_POSITION_SIZE];
	int8_t middleEdgePosition[MIDDLE_EDGE_POSITION_SIZE];

	int cornorPositionMove[CORNOR_POSITION_SIZE][MOVE_COUNT];
	int udEdgePositionMove[UD_EDGES_POSITION_SIZE][MOVE_COUNT];
	int middleEdgePositionMove[MIDDLE_EDGE_POSITION_SIZE][MOVE_COUNT];

	int8_t cornorPositionAndMiddleEdgePos[CORNOR_POSITION_SIZE * MIDDLE_EDGE_POSITION_SIZE];
	int8_t udEdgePositionAndMiddleEdgePos[UD_EDGES_POSITION_SIZE * MIDDLE_EDGE_POSITION_SIZE];

	vector<cube_t> middleEdgePos;

	void init() {
		cube_t cube;
		memset(cornorPositionMove, 0xff, sizeof(int) * CORNORS_ORIENTATION_SIZE * MOVE_COUNT);

	}

	int calculateIndex(cube_t cube, int type) {
		int ret = 0;
		switch (type){
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

			}

		}

		return ret;
	}



};







#endif