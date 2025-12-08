#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<string> input_str;
vector<int> indices;
vector<vector<int>> input;

int read_input() {
    fstream inputFile("./pr6p1.txt");
    // fstream inputFile("./example.txt");


    if (!inputFile.is_open()) {
        cerr << "Error opening file" << endl;
        return 1;
    }

    string line;
    int lines = 0;
    while(getline(inputFile, line)) {
        input_str.push_back(line);
        lines++;
    }
    lines--;

    // get indices of operand
    for (int i = 0; i < input_str[lines].size(); i++) {
        if (input_str[lines].substr(i,1) == "+" || input_str[lines].substr(i,1) == "*") {
            indices.push_back(i);
        }
    }

    // transcribe nums to input
    for (int i = 0; i < indices.size(); i++) {
        int index = indices[i];
        // push curr problem to input
        vector<int> curr_line;
        for (int l = 0; l < lines; l++) {
            string curr;
            if (i != indices.size()-1) {
                int curr_len = indices[i+1] - indices[i];
                curr = input_str[l].substr(index, curr_len);
            } else {
                curr = input_str[l].substr(index);
            }
            curr_line.push_back(stoi(curr));
        }

        input.push_back(curr_line);
    }

    return 0;
}

long long get_sum() {
    long long total = 0;
    for (int i = 0; i < indices.size(); i++) {
        int isMultiply = 1;
        if (input_str[input_str.size() - 1].substr(indices[i],1) == "+") {
            isMultiply = 0;
        }
        
        if (isMultiply) {
            long long product = 1;
            for (int j = 0; j < input[i].size(); j++) {
                product *= input[i][j];
            }
            total += product;
        } else {
            int sum = 0;
            for (int j = 0; j < input[i].size(); j++) {
                sum += input[i][j];
            }
            total += sum;
        }
    }

    return total;
}

int main() {
    read_input();
    long long total = get_sum();
    
    cout << total << endl;
    return 0;
}