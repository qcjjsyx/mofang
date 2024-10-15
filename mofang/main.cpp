#include "RubikCube.hpp"
#include "iostream"
#include "Solution.hpp"
#include "CubeState.hpp"
using namespace std;

int main() {
	cube_t cube;
	CubeState cubeState = CubeState();
	cubeState.printCube(cube);
	cubeState.scrambleCube(10, cube);
	cubeState.printCube(cube);
}
