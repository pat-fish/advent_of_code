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
    ifstream inputFile("../part1/pr4p1.txt");
    // ifstream inputFile("../part1/example.txt");


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
    // reset adj table for each iter
    for (int col = 0; col < (sizeof(input[0]) / sizeof(input[0][0])); col++) {
        for (int row = 0; row < sizeof(input) / sizeof(input[0]); row++) {
            adj[row][col] = 0;
        }
    }

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
                input[row][col] = 0; // for next iter
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
    int total = 0;
    int iter_count;
    read_input();

    do {
        pop_adj_table();
        iter_count = accessible_rolls();
        total += iter_count;
    } while (iter_count > 0);

    cout << total << endl;
    return 0;
}