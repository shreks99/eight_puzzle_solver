#include<bits/stdc++.h>
#include "board.h"
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
            {7, 8, 0} // 0 represents the empty tile
        };
    } else if(choice == 2){  
        size = inputBoard(puzzle);
        //TODO: Can run validity check on the input!
    }
        printBoard(puzzle);
    return 0;
}