#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct coords {
    long long x;
    long long y;
};

vector<coords> input;

int read_input() {
    ifstream inputFile("./pr9p1.txt");
    // ifstream inputFile("./example.txt");


    if (!inputFile.is_open()) {
        cerr << "Error opening file" << endl;
        return 1;
    }

    string line;
    while (getline(inputFile, line)) {
        coords curr;
        curr.x = stoll(line.substr(0,line.find(",")));
        line = line.substr(line.find(",")+1);
        curr.y = stoll(line);
        input.push_back(curr);
    }

    return 0;
}

long long find_max_rect() {
    long long max = 0;
    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input.size(); j++) {
            if (i != j) {
                long long curr = (abs(input[i].x - input[j].x)+1) * (abs(input[i].y - input[j].y)+1);
                if (curr > max) {
                    max = curr;
                }
            }
        }
    }

    return max;
}

int main() {
    /*
    brute force largest area
    return largest area
    */
    read_input();
    long long max_rect = find_max_rect();

    cout << max_rect << endl;
    return 0;
}