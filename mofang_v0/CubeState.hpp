#ifndef CUBESTATE_H
#define CUBESTATE_H
#include <map>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>
#define MOVECUBE 20

using namespace std;





/*
U/D 高
F/B 中
L/R 低
*/
/************************************************
------------------------------------------------------
               |1   2   3|
               |4   5   6|
               |7   8   9|
------------------------------------------------------
|10  11  12|  |19  20  21| |28  29  30|
|13  14  15|  |22  23  24| |31  32  33|
|16  17  18|  |25  26  27| |34  35  36|
---------------------------------------------------- -
              |37  38  39|
              |40  41  42|
              |43  44  45|
------------------------------------------------------
              |46  47  48|
              |49  50  51|
              |52  53  54|
************************************************/

/*********************************************


          ___2    ___2    ___1
         /__/|   /__/|   /__/|
         |__|/   |__|/   |__|/

      ___3             ___1
     /__/|            /__/|
     |__|/            |__|/

  ___3	  ___0	  ___0
 /__/|	 /__/|	 /__/|
 |__|/	 |__|/	 |__|/



         ___11            ___10
        /__/|            /__/|
        |__|/            |__|/



 ___9              ___8
/__/|             /__/|
|__|/             |__|/



       ___6     ___6     ___7
      /__/|    /__/|    /__/|
      |__|/    |__|/    |__|/

    ___7              ___5
   /__/|             /__/|
   |__|/             |__|/

 ___5	  ___4	   ___4
/__/|	 /__/|    /__/|
|__|/	 |__|/    |__|/








*************************************************/

struct cube_t
{
	int8_t edgeIndex[12];
	int8_t cornorIndex[8];
	int8_t edgeOrientation[12];
	int8_t cornorOrientation[8];

	cube_t() {
		for (int i = 0; i < 12; ++i) {
			if (i < 8) {
				cornorIndex[i] = i;
				cornorOrientation[i] = 0;
			}

            edgeIndex[i] = i;
			edgeOrientation[i] = 0;
			
		}
	}

};


static const int8_t face_edges[6][4] = {
	{0,1,2,3},//U
	{4,7,6,5},//D
	{0,9,4,8},//F
	{2,10,6,11},//B
    {3,11,7,9},//L
    {1,8,5,10}//R
};

static const int8_t face_cornors[6][4] = {
    {0,1,2,3},//U
    {4,5,6,7},//D
    {0,3,5,4},//F
    {2,1,7,6},//B
    {3,2,6,5},//L
    {1,0,4,7}//R
};


static const int8_t map_cornors[8][3] = {
    {27,39,34},
    {21,28,9},
    {19,7,12},
    {25,18,37},
    {48,36,45},
    {46,43,16},
    {52,10,1},
    {54,3,30},


};

static const int8_t map_edges[12][2] = {
    {   26,38},
    {   24,31},
    {   20,8},
    {   22,15},
    {   47,44},
    {   51,33},
    {   53,2},
    {   49,13},
    {	42,35},
    {	40,17},
    {	6,29},
    {	4,11}
};

static const char* colorCornor[8]{
    "YBR",
    "YRG",
    "YGO",
    "YOB",
    "WRB",
    "WBO",
    "WOG",
    "WGR",
};

static const char* colorEdge[12]{

};

static const char* cornors[8]{
    "UFR",
    "URB",
    "UBL",
    "ULF",
    "DRF",
    "DFL",
    "DLB",
    "DBR"
};
static const char* edges[12]{
    "UF",
    "UR",
    "UB",
    "UL",
    "DF",
    "DR",
    "DB",
    "DL",
    "FR",
    "FL",
    "BR",
    "BL"
};

map<string, int> str2move{
    {"U",0},{"U2",1},{"U'",2},
    {"D",3},{"D2",4},{"D'",5},
    {"F",6},{"F2",7},{"U'",8},
    {"B",9},{"B2",10},{"B'",11},
    {"L",12},{"L2",13},{"L'",14},
    {"R",15},{"R2",16},{"R'",17}
};


class CubeState {
public:
    //vector<int> scrambleMoves;
    static cube_t moveRotate(int move, cube_t& cube) {
        int face = move / 3;
        int rotateCount = move % 3 + 1;
        cube_t ret = cube;
        //position
        for (int i = 0; i < 4; ++i) {
            ret.edgeIndex[face_edges[face][i]] = cube.edgeIndex[face_edges[face][(i + rotateCount) % 4]];
            ret.cornorIndex[face_cornors[face][i]] = cube.cornorIndex[face_cornors[face][(i + rotateCount) % 4]];
        }
        //Orientation
        //edgeOrientation
        /*只有前面和后面旋转90°或者 270°才能改变方向
        *只对棱块，由于不是每个棱块都有U/D色，不能以U/D为基准，这里定义魔方的六个面为三组，
        *U/D为高级色，F/B为中级色，L/R为低级色 ，
        *对于某个棱块，若其更高级的色在其所在位置更高级的面，则视为颜色正确，标记为0，否则错误，标记为1，
        *例如：FR这个棱块在UR棱块位置，若其F色在U面，则其状态正确，标记为0，若R色在U面，则其状态错误，标记为1.
        */
        for (int i = 0; i < 4; ++i) {
            if ((face == 2 || face == 3) && (rotateCount == 1 || rotateCount == 3)) {
                ret.edgeOrientation[face_edges[face][i]] = cube.edgeOrientation[face_edges[face][(i + rotateCount) % 4]] == 1 ? 0 : 1;
            }
            else {
                ret.edgeOrientation[face_edges[face][i]] = cube.edgeOrientation[face_edges[face][(i + rotateCount) % 4]];
            }
        }
        //cornorsOrientation
        /*旋转上下两面是不会改变角块方向的,且其余面若旋转两次也是不会影响角块的方向的
        *对角块，以U/D面为基准，
        *当某个块U/D面的色在U/D面时候，其状态即为正确，
        *否则观察其U/D色那一面逆时针旋转了几次，旋转一次标记为1，旋转两次标记为2
        */
        if (face >1 &&(rotateCount==1 || rotateCount==3)){
            if (rotateCount == 1) {
                ret.cornorOrientation[face_cornors[face][0]] = decreaseCornorOri(cube.cornorOrientation[face_cornors[face][1]]);
                ret.cornorOrientation[face_cornors[face][1]] = increaseCornorOri(cube.cornorOrientation[face_cornors[face][2]]);
                ret.cornorOrientation[face_cornors[face][2]] = decreaseCornorOri(cube.cornorOrientation[face_cornors[face][3]]);
                ret.cornorOrientation[face_cornors[face][3]] = increaseCornorOri(cube.cornorOrientation[face_cornors[face][0]]);
            }
            else {
                ret.cornorOrientation[face_cornors[face][0]] = decreaseCornorOri(cube.cornorOrientation[face_cornors[face][3]]);
                ret.cornorOrientation[face_cornors[face][1]] = increaseCornorOri(cube.cornorOrientation[face_cornors[face][0]]);
                ret.cornorOrientation[face_cornors[face][2]] = decreaseCornorOri(cube.cornorOrientation[face_cornors[face][1]]);
                ret.cornorOrientation[face_cornors[face][3]] = increaseCornorOri(cube.cornorOrientation[face_cornors[face][2]]);
            }
        }
        else {
            for (int i = 0; i<4; ++i) {
                ret.cornorOrientation[face_cornors[face][i]] = cube.cornorOrientation[face_cornors[face][(i + rotateCount) % 4]];
            }
        }
        
        return ret;
    };

    //cube_t scrambleCube(int moveNums, cube_t& cube) {
    //    srand(static_cast<unsigned int>(std::time(nullptr)));
    //    cube_t ret = cube;
    //    //scrambleMoves.clear();
    //    for (int i = 0; i < moveNums; ++i) {
    //        int index = rand() % 18;
    //        ret = moveRotate(str2move[moves[index]],ret);
    //        cout << moves[index] << " ";
    //    }
    //    cout << endl;
    //    return ret;
    //};


    cube_t generateCube(string str) {
        cube_t cube;
        if (str[4] != 'B' || str[13] != 'L' || str[22] != 'U' || str[31] != 'R' || str[40] != 'F' || str[49] != 'D') {
            printf("not legal center block!!\n");

        }
        for (int i = 0; i < 8; i++) {
            int8_t face1 = map_cornors[i][0] - 1;
            int8_t face2 = map_cornors[i][1] - 1;
            int8_t face3 = map_cornors[i][2] - 1;
            for (int j = 0; j < 8; j++) {
                if (cornors[j][0] == str[face1] && cornors[j][1] == str[face2] && cornors[j][2] == str[face3]) {
                    cube.cornorIndex[i] = j;
                    cube.cornorOrientation[i] = 0;
                    break;
                }
                else if (cornors[j][1] == str[face1] && cornors[j][2] == str[face2] && cornors[j][0] == str[face3]) {
                    cube.cornorIndex[i] = j;
                    cube.cornorOrientation[i] = 2;
                    break;
                }
                else if (cornors[j][2] == str[face1] && cornors[j][0] == str[face2] && cornors[j][1] == str[face3]) {
                    cube.cornorIndex[i] = j;
                    cube.cornorOrientation[i] = 1;
                    break;
                }

            }
        }

        for (int i = 0; i < 12; i++) {
            int8_t face1 = map_edges[i][0] - 1;
            int8_t face2 = map_edges[i][1] - 1;
            for (int j = 0; j < 12; j++) {
                if (edges[j][0] == str[face1] && edges[j][1] == str[face2]) {
                    cube.edgeIndex[i] = j;
                    cube.edgeOrientation[i] = 0;
                    break;
                }
                else if (edges[j][1] == str[face1] && edges[j][0] == str[face2]) {
                    cube.edgeIndex[i] = j;
                    cube.edgeOrientation[i] = 1;
                    break;
                }

            }
        }

        printCube(cube);
        return cube;
    }

    void printCube(cube_t cube) {
        for (int i = 0; i < 12; i++) {
            printf("edge block index : %d oriention %d\n", cube.edgeIndex[i], cube.edgeOrientation[i]);
        }
        for (int i = 0; i < 8; i++) {
            printf("cornor block index : %d oriention %d\n", cube.cornorIndex[i], cube.cornorOrientation[i]);
        }
        printf("\n");
    }


private:
    //cube_t cube;
    //U, R2, F2, D, L2, B2
    const vector<string> moves = { "U","U2","U'","D","D2","D'","F","F2","F'","B","B2","B'","L","L2","L'","R","R2","R'"};

    static int8_t increaseCornorOri(int8_t input) {
        int8_t tmp = input;
        if (input < 2) {
            tmp = 1;
        }
        else {
            tmp = -2;
        }
        return (input+tmp);
    }
    static int8_t decreaseCornorOri(int8_t input) {
        int8_t tmp = input;
        if (input > 0) {
            tmp = -1;
        }
        else {
            tmp = 2;
        }
        return (input + tmp);
    }

};

#endif