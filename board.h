#include<iostream>

#include<vector>

void printBoard(const std::vector<std::vector<int>>& puzzle) {
    for (const auto& row : puzzle) {
        for (const auto& tile : row) {
            std::cout << tile << " ";
        }
        std::cout << "\n";
    }

}

int inputBoard(std::vector<std::vector<int>>& puzzle) {
    int size;
    std::cout<<"\nEnter your puzzle, use a zero to represent the blank!";
        std::cout<<"\nSize ::";
        std::cin>>size;
        for (int i = 0; i < size; ++i) {
            std::vector<int> row;
            std::cout<<"Enter the "<<i + 1<<" row, use spaces between numbers: ";
            for (int j = 0; j < size; ++j) {
                int tile;
                std::cin >> tile;
                row.push_back(tile);
            }
            puzzle.push_back(row);
        }
    return size;
}