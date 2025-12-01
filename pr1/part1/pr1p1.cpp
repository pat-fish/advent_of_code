#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> input;

int read_input() {
    ifstream inputFile("./pr1p1.txt");
    // ifstream inputFile("./example.txt");


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

        if (dir == "L") {
            sum -= stoi(len);
        } else {
            sum += stoi(len);
        }

        if (sum % 100 == 0) {
            count++;
        }
    }

    return count;
}

int main() {

    /*
    read input and find first char (if L go left, if R go right)
    add to total sum using specified weight, if sum % 90 == 0, add to count
    count starts @ 50
    return count
    */
    read_input();
    int count = get_zeros();

    cout << count << endl;
    return 0;
}