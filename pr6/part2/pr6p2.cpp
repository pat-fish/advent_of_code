#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<string> input_str;
vector<int> indices;
vector<vector<int>> input;

int read_input() {
    fstream inputFile("../part1/pr6p1.txt");
    // fstream inputFile("../part1/example.txt");


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
        vector<int> curr_line;
        int curr_len;
        if (i != indices.size() - 1) {
            curr_len = indices[i+1] - indices[i];
        } else {
            curr_len = (input_str[0].size() - indices[i]) + 1;
        }

        // iter through lines from index to index+curr_len
        for (int l = 0; l < curr_len-1; l++) {
            string curr = "";
            
            for (int s = 0; s < lines; s++) {
                curr += input_str[s].substr(index+l, 1);
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