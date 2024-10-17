#include "RubikCube.hpp"
#include "iostream"
#include "Solution.hpp"
#include "CubeState.hpp"
using namespace std;

int main() {
	cube_t cube;
	CubeState cubeState = CubeState();
	cubeState.printCube(cube);
	cube_t ret = cubeState.scrambleCube(20, cube);
	cubeState.printCube(ret);
}
