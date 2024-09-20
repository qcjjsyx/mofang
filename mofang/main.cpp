#include "RubikCube.hpp"
#include "iostream"
#include "Solution.hpp"

using namespace std;

int main() {
    Solution solution = Solution(5);
    cout << solution.DFS(0, 10) << endl;
    cout << "hello";
}
