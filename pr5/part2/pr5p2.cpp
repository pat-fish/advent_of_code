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

int read_input() {
    fstream inputFile("../part1/pr5p1.txt");
    // fstream inputFile("./example.txt");


    if (!inputFile.is_open()) {
        cerr << "Error opening file" << endl;
        return 1;
    }

    string line;
    while (getline(inputFile, line)) {
        if (line == "") {
            break;
        }

        int index = line.find("-");
        long long lower = stoll(line.substr(0,index));
        long long upper = stoll(line.substr(index+1));
        range range = {lower, upper};
        ranges.push_back(range);
    }

    return 0;
}

long long num_valid_ranges() {
    // remove all overlaps
    for (int i = 0; i < ranges.size(); i++) {
        for (int j = 0; j < ranges.size(); j++) {
            if (i != j) {
                range update = ranges[i];
                range comp = ranges[j];
                if (update.upper >= comp.lower && update.upper <= comp.upper) {
                    update.upper = (comp.lower - 1);
                    ranges[i].upper = update.upper;
                }

                // remove invalid ranges
                if (update.upper < update.lower) {
                    ranges.erase(ranges.begin() + i);
                    i--;
                    break;
                }
            }
        }
    }

    // count num of valid ids
    long long count = 0;
    for (range range: ranges) {
        long long curr = (range.upper - range.lower) + 1;
        count += curr;
    }

    return count;
}

int main() {
    read_input();
    long long valid_ranges = num_valid_ranges();

    cout << valid_ranges << endl;
    return 0;
}