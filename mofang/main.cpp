#include "RubikCube.hpp"
#include "iostream"
#include "Solution.hpp"
#include "CubeState.hpp"
#include "NewSolution.hpp"
#include "memory"
#include "utility.hpp"
using namespace std;





int main() {
	Utility utility;
	utility.readFromCamera();
	/*shared_ptr<NewSolution> prs(new NewSolution());
	
	char s[55] = "BBBBBBRRRLLBLLBLLBUUUUUUUUUFRRFRRFRRLLLFFFFFFDDDDDDDDD";
	CubeState cubeState;
	cube_t cube = cubeState.generateCube(s);

	prs->solve(cube);*/
}
