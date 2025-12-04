#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

vector<string> input = {};

int trav_input() {
    ifstream inputFile("./pr3p1.txt");
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

int joltage_sum() {
    int sum = 0;
    // iter through lines in input vector
    for (int i = 0; i < input.size(); i++) {
        int first_dig = 0;
        int first_ind = 0;
        int second_dig = 0;
        int n = input[i].size();

        // find first digit
        for (int first = 0; first < n - 1; first++) {
            int curr = stoi(input[i].substr(first, 1));
            if (curr > first_dig) {
                first_dig = curr;
                first_ind = first;
                if (curr == 9) {
                    break;
                }
            }
        }
        // find second digit
        for (int second = first_ind+1; second < n; second++) {
            int curr = stoi(input[i].substr(second, 1));
            if (curr > second_dig) {
                second_dig = curr;
                if (curr == 9) {
                    break;
                }
            }
        }

        // add to sum
        sum += (10*first_dig) + second_dig;
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
    int sum = joltage_sum();

    cout << sum << endl;
    return 0;
}