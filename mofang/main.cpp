#include "RubikCube.hpp"
#include "iostream"
#include "Solution.hpp"

using namespace std;

int main() {
    Solution solution = Solution(10);
    cout << solution.DFS(0, 15) << endl;
    cout << "hello";
}
