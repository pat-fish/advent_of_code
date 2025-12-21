#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

vector<vector<int>> splitters;

int read_input() {
    fstream inputFile("../part1/pr7p1.txt");
    // fstream inputFile("../part1/example.txt");


    if (!inputFile.is_open()) {
        cerr << "Error opening file" << endl;
        return 1;
    }

    string line;
    // get index of S
    getline(inputFile, line);
    int s_index = line.find("S");

    // transcribe splitter locations
    int row = 0;
    while (getline(inputFile, line)) {
        vector<int> new_row;
        splitters.push_back(new_row);
        for (int i = 0; i < line.size(); i++) {
            if (line.substr(i,1) == "^") {
                splitters[row].push_back(1);
            } else {
                splitters[row].push_back(0);
            }
        }
        row++;
    }

    return s_index;
}

long long trace_beam(int s_index) {
    long long count = 0;
    unordered_map<int, long long> beams = {{s_index,1}};
    
    int is_split_row = 0;
    for (int i = 0; i < splitters.size(); i++) { // line by line through input
        unordered_map<int,long long> updated_beams = beams;

        for (int beam = 0;  beam < splitters.size(); beam++) {
            if (beams[beam] != 0 && splitters[i][beam] == 1) { // check that beam hits splitter
                if (beam > 0) {
                    updated_beams[beam-1] += updated_beams[beam];
                }
                if (beam < splitters.size() - 1) {
                    updated_beams[beam+1] += updated_beams[beam];
                }
                updated_beams[beam] = 0;
            }
        }

        // update beams
        beams = updated_beams;
    }

    // count = sum of num of paths to each splitter
    for (int beam = 0; beam < splitters.size(); beam++) {
        count += beams[beam];
    }

    return count;
}

int main() {
    /*
    transcribe splitter locations
    trace beam from starting location
    */
    int s_index = read_input();
    long long timeline_count = trace_beam(s_index);

    cout << timeline_count << endl;
    return 0;
}