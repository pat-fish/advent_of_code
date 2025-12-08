#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct range {
    long long lower;
    long long upper;
};

vector<range> ranges;
vector<long long> ids;

int read_input() {
    fstream inputFile("./pr5p1.txt");

    if (!inputFile.is_open()) {
        cerr << "Error opening file" << endl;
        return 1;
    }

    string line;
    int isRange = 1;
    while (getline(inputFile, line)) {
        if (line == "") {
            isRange = 0;
            continue; // empty line
        }
        
        if (isRange) {
            int index = line.find("-");
            long long lower = stoll(line.substr(0,index));
            long long upper = stoll(line.substr(index+1));
            range range = {lower, upper};
            ranges.push_back(range);
        } else {
            long long curr = stoll(line);
            ids.push_back(curr);
        }
    }

    return 0;
}

int num_valid_ids() {
    int count = 0;
    for (long long id : ids) {
        for (range range : ranges) {
            long long lower = range.lower;
            long long upper = range.upper;
            
            if (id >= lower && id <= upper) {
                count++;
                break;
            }
        }
    }

    return count;
}

int main() {
    read_input();
    int valid_ids = num_valid_ids();

    cout << valid_ids << endl;
    return 0;
}