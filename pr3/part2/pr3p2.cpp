#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

vector<string> input = {};

int trav_input() {
    ifstream inputFile("../part1/pr3p1.txt");
    // ifstream inputFile("../part1/example.txt");


    if (!inputFile.is_open()) {
        cerr << "Error opening file" << endl;
        return 1;
    }

    string line;
    while (getline(inputFile, line)) {
        input.push_back(line);
    }

    return 0;
}

long long joltage_sum() {
    unsigned long long sum = 0;
    // iter through lines in input vector
    for (int curr_line = 0; curr_line < input.size(); curr_line++) {
        int vals[12] = {0};
        int inds[12] = {0}; // array for index of each val
        int n = input[curr_line].size();

        // work backwards from most sig number
        for (int i = 11; i >= 0; i--) {
            int j;
            if (i == 11) {
                j = 0;
            } else {
                j = inds[i+1] + 1;
            }

            for (; j < n - i; j++) {
                int curr = stoi(input[curr_line].substr(j, 1));
                if (curr > vals[i]) {
                    vals[i] = curr;
                    inds[i] = j;

                    if (curr == 9) {
                        break;
                    }
                }
            }
        }

        // add to sum
        for (int i = 11; i >= 0; i--) {
            sum += (vals[i] * pow(10,i));
        }
    }
    
    return sum;
}

int main() {
    /*
    trav input line by line
    first digit = largest val from (0,n-2)
    second digit = largest val after first digit
    find total sum
    */

    trav_input();
    long long sum = joltage_sum();

    cout << sum << endl;
    return 0;
}