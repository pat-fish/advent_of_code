#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

vector<string> input;

int read_input() {
    ifstream inputFile("../part1/pr1p1.txt");

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

int get_zeros() {
    int sum = 50;
    int count = 0;
    for (int i = 0; i < input.size(); i++) {
        string curr = input[i];
        string dir = curr.substr(0,1);
        string len = curr.substr(1);
        int prev = sum;
        
        if (dir == "L") {
            sum -= stoi(len);
            for (int i = sum; i < prev; i++) {
                // count turns that land on 0
                if (i % 100 == 0) {
                    count++;
                }
            }

        } else {
            sum += stoi(len);
            for (int i = sum; i > prev; i--) {
                // count turns that land on 0
                if (i % 100 == 0) {
                    count++;
                }
            }
        }
    }

    return count;
}

int main() {
    read_input();
    int count = get_zeros();

    cout << count << endl;
    return 0;
}