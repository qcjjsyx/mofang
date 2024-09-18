#ifndef RUBIKCUBE_H
#define RUBIKCUBE_H

#include <iostream>
#include <vector>
#include<cstdlib>
#include<ctime>

using namespace std;

class RubikCube {
private:
    vector<vector<vector<char>>> cube;

    // 旋转一个面90度顺时针
    void rotateFace(vector<vector<char>>& face) {
        vector<vector<char>> temp = face;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                face[j][2 - i] = temp[i][j];
            }
        }
    }

public:
    // 构造函数，初始化魔方
    RubikCube() {
        cube.resize(6, vector<vector<char>>(3, vector<char>(3)));
        initializeCube();
    }

    // 初始化魔方的每个面，使用字符表示颜色
    void initializeCube() {
        char colors[] = { 'W', 'G', 'R', 'B', 'O', 'Y' }; // W: 白, G: 绿, R: 红, B: 蓝, O: 橙, Y: 黄
        for (int face = 0; face < 6; ++face) {
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    cube[face][i][j] = colors[face];
                }
            }
        }
    }

    // 旋转左面
    void rotateLeft() {
        rotateFace(cube[1]);
        vector<char> temp = { cube[0][0][0], cube[0][1][0], cube[0][2][0] };
        for (int i = 0; i < 3; ++i) {
            cube[0][i][0] = cube[4][2 - i][2];
            cube[4][i][2] = cube[5][i][0];
            cube[5][i][0] = cube[2][2 - i][0];
            cube[2][i][0] = temp[i];
        }
    }

    // 旋转右面
    void rotateRight() {
        rotateFace(cube[3]);
        vector<char> temp = { cube[0][0][2], cube[0][1][2], cube[0][2][2] };
        for (int i = 0; i < 3; ++i) {
            cube[0][i][2] = cube[2][i][2];
            cube[2][i][2] = cube[5][i][2];
            cube[5][i][2] = cube[4][2 - i][0];
            cube[4][i][0] = temp[2 - i];
        }
    }

    // 旋转上面
    void rotateTop() {
        rotateFace(cube[0]);
        vector<char> temp = { cube[1][0][0], cube[1][0][1], cube[1][0][2] };
        for (int i = 0; i < 3; ++i) {
            cube[1][0][i] = cube[2][0][i];
            cube[2][0][i] = cube[3][0][i];
            cube[3][0][i] = cube[4][0][i];
            cube[4][0][i] = temp[i];
        }
    }

    // 旋转下面
    void rotateBottom() {
        rotateFace(cube[5]);
        vector<char> temp = { cube[1][2][0], cube[1][2][1], cube[1][2][2] };
        for (int i = 0; i < 3; ++i) {
            cube[1][2][i] = cube[4][2][i];
            cube[4][2][i] = cube[3][2][i];
            cube[3][2][i] = cube[2][2][i];
            cube[2][2][i] = temp[i];
        }
    }

    // 旋转前面
    void rotateFront() {
        rotateFace(cube[2]);
        vector<char> temp = { cube[0][2][0], cube[0][2][1], cube[0][2][2] };
        for (int i = 0; i < 3; ++i) {
            cube[0][2][i] = cube[1][2 - i][2];
            cube[1][i][2] = cube[5][0][i];
            cube[5][0][i] = cube[3][2 - i][0];
            cube[3][i][0] = temp[i];
        }
    }

    // 旋转背面
    void rotateBack() {
        rotateFace(cube[4]);
        vector<char> temp = { cube[0][0][0], cube[0][0][1], cube[0][0][2] };
        for (int i = 0; i < 3; ++i) {
            cube[0][0][i] = cube[3][i][2];
            cube[3][i][2] = cube[5][2][2 - i];
            cube[5][2][i] = cube[1][2 - i][0];
            cube[1][i][0] = temp[i];
        }
    }

    // 随机打乱魔方
    void scramble(int moves = 20) {
        srand(time(0));
        for (int i = 0; i < moves; ++i) {
            int randMove = rand() % 6;
            switch (randMove)
            {
            case 0: rotateLeft(); break;
            case 1: rotateRight(); break;
            case 2: rotateTop(); break;
            case 3: rotateBottom(); break;
            case 4: rotateFront(); break;
            case 5: rotateBack(); break;
            }
        }
    }

    // 输出魔方的状态
    void printCube() {
        for (int face = 0; face < 6; ++face) {
            cout << "Face " << face << ":\n";
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    cout << cube[face][i][j] << ' ';
                }
                cout << endl;
            }
            cout << endl;
        }
    }
};

#endif