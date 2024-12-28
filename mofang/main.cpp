#include "RubikCube.hpp"
#include "iostream"
#include "Solution.hpp"
#include "CubeState.hpp"
#include "NewSolution.hpp"
#include "memory"
#include "utility.hpp"
using namespace std;





int main() {
	Utility utility;//opencvÄ£¿é
	//utility.readFromCamera();
	shared_ptr<NewSolution> prs(new NewSolution());
	
	//string s = "BBBBBBRRRLLBLLBLLBUUUUUUUUUFRRFRRFRRLLLFFFFFFDDDDDDDDD";
	string s1= "GGGGGGRRROOGOOGOOGYYYYYYYYYBRRBRRBRROOOBBBBBBWWWWWWWWW";
	string s2 = utility.trans(s1);
	//cout << s2 << endl;
	CubeState cubeState;
	cube_t cube = cubeState.generateCube(s2);

	prs->solve(cube);
}
