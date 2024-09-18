#include "RubikCube.hpp"
#include "iostream"


using namespace std;

int main() {
    RubikCube cube;

    cout << "Initial Cube:" << endl;
    cube.printCube();

    cube.rotateLeft();
    cout << "Cube after rotating left face:" << endl;
    cube.printCube();

    cube.rotateRight();
    cout << "Cube after rotating right face:" << endl;
    cube.printCube();

    cube.rotateTop();
    cout << "Cube after rotating top face:" << endl;
    cube.printCube();

    cube.rotateBottom();
    cout << "Cube after rotating bottom face:" << endl;
    cube.printCube();

    cube.rotateFront();
    cout << "Cube after rotating front face:" << endl;
    cube.printCube();

    cube.rotateBack();
    cout << "Cube after rotating back face:" << endl;
    cube.printCube();

    return 0;
}
