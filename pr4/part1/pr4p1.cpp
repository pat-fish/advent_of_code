#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// padded matrices to avoid edge cases
int input[142][142] = {0};
int adj[142][142] = {0};
// int input[12][12] = {0};
// int adj[12][12] = {0};

int read_input() {
    ifstream inputFile("./pr4p1.txt");
    // ifstream inputFile("./example.txt");


    if (!inputFile.is_open()) {
        cerr << "Error opening file" << endl;
        return 1;
    }

    string line;
    int row = 1;
    while (getline(inputFile, line)) {
        for (int col = 0; col < line.size(); col++) {
            if (line.substr(col, 1) == "@") {
                input[row][col+1] = 1;
            }
        }
        row++;
    }

    return 0;
}

int pop_adj_table() {
    for (int col = 1; col < (sizeof(input[0]) / sizeof(input[0][0])) - 1; col++) {
        for (int row = 1; row < (sizeof(input) / sizeof(input[0])) - 1; row++) {
            int curr = input[row][col];

            // update adj squares for matrix
            adj[row-1][col-1] += curr;
            adj[row-1][col] += curr;
            adj[row-1][col+1] += curr;
            adj[row][col-1] += curr;
            adj[row][col+1] += curr;
            adj[row+1][col-1] += curr;
            adj[row+1][col] += curr;
            adj[row+1][col+1] += curr;
        }
    }

    return 0;
}

int accessible_rolls() {
    int count = 0;
    for (int col = 1; col < (sizeof(adj[0]) / sizeof(adj[0][0])) - 1; col++) {
        for (int row = 1; row < (sizeof(adj) / sizeof(adj[0])) - 1; row++) {
            if (input[row][col] == 1 && adj[row][col] < 4) {
                count++;
            }
        }
    }

    return count;
}

int main() {
    /*
    read input to 2d matrix
    0 = . 1 = @
    if adjacent indices sum to < 4 add to sum
    return sum
    */
    read_input();
    pop_adj_table();
    int count = accessible_rolls();

    cout << count << endl;
    return 0;
}