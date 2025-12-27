#include <string>
#include <vector>
#include "structs.hpp"

using namespace std;

// constructor
UnionFind::UnionFind(vector<junction_box> boxes) {
    int N = boxes.size();
    count = N;

    for (int i = 0; i < N; i++) {
        parent[boxes[i]] = boxes[i];
        sz[boxes[i]] = 1;
    }
}

junction_box UnionFind::find(junction_box p) {
    if (parent[p] == p) {
        return p;
    }
    // else find root parent and redefine parent[p]
    return parent[p] = find(parent[p]);
}

void UnionFind::unite(junction_box p, junction_box q) {
    junction_box rootP = find(p);
    junction_box rootQ = find(q);

    if (rootP == rootQ) return;

    if (sz[rootP] < sz[rootQ]) {
        parent[rootP] = rootQ;
        sz[rootQ] += sz[rootP];
    } else {
        parent[rootQ] = rootP;
        sz[rootP] += sz[rootQ];
    }

    count--; // update count
}

int UnionFind::connected(junction_box p, junction_box q) {
    if (parent[p] == parent[q]) {
        return 1;
    } else {
        return 0;
    }
}

void UnionFind::populate_pq(vector<junction_box> boxes) {
    // vector<junction_box> found;
    for (int i = 0; i < boxes.size(); i++) {
        size_pq.push(sz[boxes[i]]);
        // found.push_back(boxes[i]);
    }
}

int UnionFind::getCount() {
    return count;
}

priority_queue<int> UnionFind::getSizePQ() {
    return size_pq;
}

unordered_map<junction_box, int> UnionFind::getSize() {
    return sz;
}
