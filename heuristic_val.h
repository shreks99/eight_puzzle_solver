#include <iostream>
#include <vector>
using namespace std;

int  misplacedTileHeuristic(vector<vector<int>>& problem) {
    int misplaced = 0;
    int n = problem.size();
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++) 
            if(problem[i][j] != 0 && problem[i][j] != i * n + j + 1)
                misplaced++;
    }
    return misplaced;
}

int manhattanDistanceHeuristic(const vector<vector<int>>& problem) {
    int manhattanDistance = 0;
    int n = problem.size();
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {            
            // Skip the blank tile (0)
            if (problem[i][j] == 0)
                continue;
        
            // Calculate the expected row and column for the current value
            int row = (problem[i][j] - 1) / n;
            int col = (problem[i][j] - 1) % n;
            
            // Calculate the Manhattan distance for the current tile
            int dis = abs(i - row) + abs(j - col);
            
            // Add the Manhattan distance to the total
            manhattanDistance += dis;
        }
    }
    
    return manhattanDistance;
}

int calculateHeuristic(vector<vector<int>> problem, int queueing_fun) {
    if(queueing_fun == 1) { //Uniform Cost Search
        return 0 + 1;  //f(n) + h(n)
    } else if(queueing_fun == 2) {  //A* Misplaced tile
        return misplacedTileHeuristic(problem);
    } else if(queueing_fun == 3) {  //Manhattan Distance heuristic
        return manhattanDistanceHeuristic(problem);
    }
    return 0;
}