#include<vector>
#include<unordered_set>
#include <iostream>
#include <queue>
#include "heuristic_val.h"

using namespace std;

struct Problem_State {
    vector<vector<int>> problem;
    int cost;
    int depth;
    vector<pair<int, int>> path;
    Problem_State(vector<vector<int>> p, int c,int d,vector<pair<int, int>> path)
        : problem(p), cost(c), depth(d), path(path){}
};
struct Problem_StateComparator {
    bool operator()(const Problem_State& s1, const Problem_State& s2) const {
        if(s1.cost == s2.cost) s1.depth < s2.depth;
        return s1.cost > s2.cost;
    }
};

// Custom hash function for vector<vector<int>>
struct VectorHash {
    size_t operator()(const vector<vector<int>>& v) const {
        size_t seed = v.size();
        for (const auto& row : v) {
            seed ^= row.size() + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            for (const auto& elem : row) {
                seed ^= elem + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
        }
        return seed;
    }
};
    const vector<pair<int, int>> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} }; // Up, Down, Left, Right

//Can make generalised version of this
bool isGoalState(const vector<vector<int>>& currState) {
    vector<vector<int>> goalState;
    if(currState.size() == 3) {
        goalState = {
            {1,2,3},
            {4,5,6},
            {7,8,0}
        };
    }else if(currState.size() == 4) {
        goalState = {
            {1,2,3,4},
            {5,6,7,8},
            {9,10,11,12},
            {13,14,15,0}
        };
    } else if(currState.size() == 5) {
        goalState = {
            {1,2,3,4,5},
            {6,7,8,9,10},
            {11,12,13,14,15},
            {16,17,18,19,20},
            {21,22,23,24,0}
        };
    }
    return currState == goalState;
}

void printState(Problem_State currState) {
    cout << "Cost: " << currState.cost << "\n";
    cout << "Depth: " << currState.depth << "\n";

    cout << "Path: ";
    for (const auto& move : currState.path) {
        cout << "(" << move.first << ", " << move.second << ") ";
    }
    cout << "\n";
    cout << "Board:" << "\n";
    for (const auto& row : currState.problem) {
        for (const auto& tile : row) {
            cout << tile << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}
vector<Problem_State> generateSuccessor(Problem_State currState,int queueing_fun) {
    vector<Problem_State> newStateList;
    //Finding empty tile(0)
    int oldX0 = -1,oldY0 = -1;
    for(int i=0;i<currState.problem.size();i++) {
        for(int j=0;j<currState.problem[i].size();j++){
            if(currState.problem[i][j] == 0) {
                oldX0 = i;
                oldY0 = j;
                break;
            }
        }
    }
    //Generate new states by moving the tile in different directions and check validity
    for(const auto& dir: directions) {
        int newX0 = oldX0 + dir.first;
        int newY0 = oldY0 + dir.second;

        //Check validity
        if(newX0 >=0 && newX0 <currState.problem.size() && newY0 >=0 && newY0 < currState.problem[newX0].size()) {
            vector<vector<int>> newState = currState.problem;
            swap(newState[oldX0][oldY0],newState[newX0][newY0]);
            vector<pair<int, int>> newPath = currState.path;
            newPath.push_back({ newX0, newY0 });
            newStateList.push_back(Problem_State(newState,currState.cost+calculateHeuristic(newState,queueing_fun),currState.depth+1,newPath));
        }
    }
    //  cout << "Generated successor states:" << "\n";
    // for (const auto& successor : newStateList) {
    //     printState(successor);
    // }
    return newStateList;
}

void generalSearch(vector<vector<int>> problem,int queueing_fun) {
    priority_queue<Problem_State,vector<Problem_State>,Problem_StateComparator> pqueue;
    unordered_set<vector<vector<int>>, VectorHash> visited;
    int h = calculateHeuristic(problem,queueing_fun); //Calculate h(n) hueristic cost according to the algoritm
    pqueue.push(Problem_State(problem,h,0,{})); //nodes = make-queue(make-Node(problem.initial state))
    while(!pqueue.empty()) {
        Problem_State currState = pqueue.top();
        pqueue.pop();
         if(visited.count(currState.problem)) continue;
        visited.insert(currState.problem);

        if(isGoalState(currState.problem)) {
            cout << "Generated answer states:" << "\n";
            
          printState(currState);
            return;
        }
        vector<Problem_State> successorList = generateSuccessor(currState,queueing_fun);
       // cout<<"\nSuccessorList Size ::"<<successorList.size();
        for(const auto& node: successorList) {

            if(visited.count(node.problem)) {
                //cout << "\nGenerated visited states:" << "\n";         
               // printState(node);
                continue;
            }
            
            pqueue.push(node);
        }        
    }

}