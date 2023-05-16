#include<bits/stdc++.h>
#include "board.h"
#include "general_search.h"
using namespace std;


int main() {
     ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
    cout<<"\n\t:::: Welcome to Shrey Sinha(86239477) 8 puzzle solver! :::";
    cout<<"\nPlease type '1' to use a default puzzle, or '2' to enter your own puzzle!Please be sure to press ENTER after making your choice! \nChoice ::";
    int choice = 1;
    int size = 3;
    cin>>choice;
    vector<vector<int>> puzzle;
    if(choice == 1){
        puzzle = {
            {1, 2, 3},
            {4, 5, 6},
            {0, 7, 8} // 0 represents the empty tile
        };
    } else if(choice == 2){  
        size = inputBoard(puzzle);
        //TODO: Can run validity check on the input!
    }
        printBoard(puzzle);

    int queueing_fun;
    cout<<"\nEnter your choice of algorithm \n1. Uniform Cost Search"
                <<"\n2. A* with the Misplaced Tile heuristic."
                <<"\n3. A* with the Manhattan distance heuristic"
                <<"\nChoice ::";
    cin>>queueing_fun;
    auto start = std::chrono::high_resolution_clock::now();
    generalSearch(puzzle,queueing_fun);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    cout << "\nExecution Time: " << duration.count() << " milliseconds";
    return 0;
}