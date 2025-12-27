#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <functional>
#include <cmath>
#include "../part1/structs.hpp"

using namespace std;

// overload > operation for min pq
bool operator>(const junction_pair& lhs, const junction_pair& rhs) {
    return lhs.dist > rhs.dist;
}

vector<junction_box> boxes;
vector<junction_box> input;
priority_queue<junction_pair, vector<junction_pair>, greater<junction_pair>> junction_pairs;

int read_input() {
    ifstream inputFile("c:/Users/patri/OneDrive/Desktop/Other/advent_of_code/pr8/part1/pr8p1.txt");
    // ifstream inputFile("c:/Users/patri/OneDrive/Desktop/Other/advent_of_code/pr8/part1/example.txt");


    if (!inputFile.is_open()) {
        cerr << "Error opening file" << endl;
        return 1;
    }

    string line;
    while (getline(inputFile, line)) {
        int x = stoi(line.substr(0,line.find(",")));
        line = line.substr(line.find(",")+1);
        int y = stoi(line.substr(0,line.find(",")));
        line = line.substr(line.find(",")+1);
        int z = stoi(line);

        junction_box curr = {x, y, z};
        input.push_back(curr);
    }

    boxes = input;
    return 0;
}

int pop_pq() {
    // work from back of vector for 0(1)
    for (int i = boxes.size() - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            junction_box a = boxes[i];
            junction_box b = boxes[j];
            double dist = sqrt(pow((a.x-b.x),2)+pow((a.y-b.y),2)+pow((a.z-b.z),2));
            junction_pairs.push({a,b,dist});
        }
        boxes.erase(boxes.begin() + i);
    }

    return 0;
}

long long make_connections() {
    UnionFind uf(input);
    int count = uf.getCount();
    junction_pair curr;

    while (count > 1) {
        curr = junction_pairs.top();
        junction_pairs.pop();
        if (!uf.connected(curr.a, curr.b)) {
            uf.unite(curr.a, curr.b);
        }
        count = uf.getCount();
    }

    long long product = curr.a.x * curr.b.x;

    return product;
}

int main() {
    // pop min heap pq with all possible pairs, 
    // sorting pairs in order of magnitude
    // use union-find structure for circuit matching
    read_input();
    pop_pq();
    long long x_product = make_connections();

    cout << x_product << endl;
    return 0;
}