#ifndef RUBIKCUBE_H
#define RUBIKCUBE_H

#include <iostream>
#include <vector>
#include<cstdlib>
#include<ctime>
#include<string>

using namespace std;

class RubikCube {
private:
    

    // 旋转一个面90度顺时针
    void rotateFace(vector<vector<char>>& face) {
        vector<vector<char>> temp = face;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                face[j][2 - i] = temp[i][j];
            }
        }
    }

    //旋转一个面90度逆时针
    void rotateFaceIneverse(vector<vector<char>>& face) {
        vector<vector<char>> temp = face;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                face[2 - j][i] = temp[i][j];
            }
        }
    }

public:
    vector<vector<vector<char>>> cube;
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
            cube[4][2-i][2] = cube[5][i][0];
            cube[5][i][0] = cube[2][i][0];
            cube[2][i][0] = temp[i];
        }
    }

    void rotateLeftIneverse() {
        rotateFaceIneverse(cube[1]);
        vector<char> temp = { cube[0][0][0], cube[0][1][0], cube[0][2][0] };
        for (int i = 0; i < 3; ++i) {
            cube[0][i][0] = cube[2][i][0];
            cube[2][i][0] = cube[5][i][0];
            cube[5][i][0] = cube[4][2 - i][2];
            cube[4][2 - i][2] = temp[i];
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
            cube[4][2-i][0] = temp[i];
        }
    }

    void rotateRightInverse() {
        rotateFaceIneverse(cube[3]);
        vector<char> temp = { cube[0][0][2], cube[0][1][2], cube[0][2][2] };
        for (int i = 0; i < 3; ++i) {
            cube[0][i][2] = cube[4][2 - i][0];
            cube[4][2 - i][0] = cube[5][i][2];
            cube[5][i][2] = cube[2][i][2];
            cube[2][i][2] = temp[i];
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

    void rotateTopInverse() {
        rotateFaceIneverse(cube[0]);
        vector<char> temp = { cube[1][0][0], cube[1][0][1], cube[1][0][2] };
        for (int i = 0; i < 3; ++i) {
            cube[1][0][i] = cube[4][0][i];
            cube[4][0][i] = cube[3][0][i];
            cube[3][0][i] = cube[2][0][i];
            cube[2][0][i] = temp[i];
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
    void rotateBottomInverse() {
        rotateFaceIneverse(cube[5]);
        vector<char> temp = { cube[1][2][0], cube[1][2][1], cube[1][2][2] };
        for (int i = 0; i < 3; ++i) {
            cube[1][2][i] = cube[2][2][i];
            cube[2][2][i] = cube[3][2][i];
            cube[3][2][i] = cube[4][2][i];
            cube[4][2][i] = temp[i];
        }
    }
    // 旋转前面
    void rotateFront() {
        rotateFace(cube[2]);
        vector<char> temp = { cube[0][2][0], cube[0][2][1], cube[0][2][2] };
        for (int i = 0; i < 3; ++i) {
            cube[0][2][i] = cube[1][2 - i][2];
            cube[1][2 - i][2] = cube[5][0][2 - i];
            cube[5][0][2 - i] = cube[3][i][0];
            cube[3][i][0] = temp[i];
        }
    }

    void rotateFrontInverse() {
        rotateFaceIneverse(cube[2]);
        vector<char> temp = { cube[0][2][0], cube[0][2][1], cube[0][2][2] };
        for (int i = 0; i < 3; ++i) {
            cube[0][2][i] = cube[3][i][0];
            cube[3][i][0] = cube[5][0][2 - i];
            cube[5][0][2 - i] = cube[1][2 - i][2];
            cube[1][2 - i][2] = temp[i];
        }
    }
    // 旋转背面
    void rotateBack() {
        rotateFace(cube[4]);
        vector<char> temp = { cube[0][0][0], cube[0][0][1], cube[0][0][2] };
        for (int i = 0; i < 3; ++i) {
            cube[0][0][i] = cube[3][i][2];
            cube[3][i][2] = cube[5][2][i];
            cube[5][2][i] = cube[1][2 - i][0];
            cube[1][2 - i][0] = temp[i];
        }
    }

    void rotateBackInverse() {
        rotateFaceIneverse(cube[4]);
        vector<char> temp = { cube[0][0][0], cube[0][0][1], cube[0][0][2] };
        for (int i = 0; i < 3; ++i) {
            cube[0][0][i] = cube[1][2 - i][0];
            cube[1][2 - i][0] = cube[5][2][i];
            cube[5][2][i] = cube[3][i][2];
            cube[3][i][2] = temp[i];
        }
    }
    void applyRotate(const string& move) {
        if (move == "L") rotateLeft();
        else if (move == "R") rotateRight();
        else if (move == "U") rotateTop();
        else if (move == "D") rotateBottom();
        else if (move == "F") rotateFront();
        else if (move == "B") rotateBack();
        else if (move == "_L") rotateLeftIneverse();
        else if (move == "_R") rotateRightInverse();
        else if (move == "_U") rotateTopInverse();
        else if (move == "_D") rotateBottomInverse();
        else if (move == "_F") rotateFrontInverse();
        else if (move == "_B") rotateBackInverse();
    }
    void applyRotateInverse(const string& move) {
        if (move == "L") rotateLeftIneverse();
        else if (move == "R") rotateRightInverse();
        else if (move == "U") rotateTopInverse();
        else if (move == "D") rotateBottomInverse();
        else if (move == "F") rotateFrontInverse();
        else if (move == "B") rotateBackInverse();
        else if (move == "_L") rotateLeft();
        else if (move == "_R") rotateRight();
        else if (move == "_U") rotateTop();
        else if (move == "_D") rotateBottom();
        else if (move == "_F") rotateFront();
        else if (move == "_B") rotateBack();
    }
    // 随机打乱魔方
    void scramble(int moves) {
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

    //检查是否复原成功
    bool isSolved() {
        char colors[] = { 'W', 'G', 'R', 'B', 'O', 'Y' };  // 初始颜色顺序
        for (int face = 0; face < 6; ++face) {
            char color = colors[face];
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    if (cube[face][i][j] != color) {
                        return false;  // 只要有一个块的颜色不对，魔方就没有复原
                    }
                }
            }
        }
        return true;  // 所有面都符合初始颜色
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