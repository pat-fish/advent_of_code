#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>

using namespace std;

// int splitters[140][140] = {0};
// vector<vector<int>> splitters(141, vector<int>(141,0));
vector<vector<int>> splitters;

int read_input() {
    fstream inputFile("./pr7p1.txt");
    // fstream inputFile("./example.txt");


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

int trace_beam(int s_index) {
    int count = 0;
    // use set to prevent double counts
    set<int> beams = {s_index};
    
    for (int i = 0; i < splitters.size(); i++) { // line by line through input
        set<int> updated_beams = beams;

        for (int beam : beams) {
            if (splitters[i][beam] == 1) {
                updated_beams.erase(beam);
                if (beam > 0) {
                    updated_beams.insert(beam-1);
                }
                if (beam < splitters.size() - 1) {
                    updated_beams.insert(beam+1);
                }
                count++;
            }
        }

        // update beams
        beams = updated_beams;
    }

    return count;
}

int main() {
    /*
    transcribe splitter locations
    trace beam from starting location
    */
    int s_index = read_input();
    int split_count = trace_beam(s_index);

    cout << split_count << endl;
    return 0;
}