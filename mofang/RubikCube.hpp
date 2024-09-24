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
    

    // ��תһ����90��˳ʱ��
    void rotateFace(vector<vector<char>>& face) {
        vector<vector<char>> temp = face;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                face[j][2 - i] = temp[i][j];
            }
        }
    }

    //��תһ����90����ʱ��
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
    // ���캯������ʼ��ħ��
    RubikCube() {
        cube.resize(6, vector<vector<char>>(3, vector<char>(3)));
        initializeCube();
    }

    // ��ʼ��ħ����ÿ���棬ʹ���ַ���ʾ��ɫ
    void initializeCube() {
        char colors[] = { 'W', 'G', 'R', 'B', 'O', 'Y' }; // W: ��, G: ��, R: ��, B: ��, O: ��, Y: ��
        for (int face = 0; face < 6; ++face) {
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    cube[face][i][j] = colors[face];
                }
            }
        }
    }

    // ��ת����
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

    // ��ת����
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

    // ��ת����
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

    // ��ת����
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
    // ��תǰ��
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
    // ��ת����
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
    // �������ħ��
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

    //����Ƿ�ԭ�ɹ�
    bool isSolved() {
        char colors[] = { 'W', 'G', 'R', 'B', 'O', 'Y' };  // ��ʼ��ɫ˳��
        for (int face = 0; face < 6; ++face) {
            char color = colors[face];
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    if (cube[face][i][j] != color) {
                        return false;  // ֻҪ��һ�������ɫ���ԣ�ħ����û�и�ԭ
                    }
                }
            }
        }
        return true;  // �����涼���ϳ�ʼ��ɫ
    }

    // ���ħ����״̬
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