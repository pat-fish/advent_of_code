#ifndef STRUCTS_H
#define STRUCTS_H
#include <vector>
#include <unordered_map>
#include <queue>

struct junction_box {
    int x;
    int y;
    int z;
    bool operator==(const junction_box& other) const noexcept {
        return x == other.x && y == other.y && z == other.z;
    }
};

namespace std {
template<>
struct hash<junction_box> {
    size_t operator()(const junction_box& jb) const noexcept {
        size_t h1 = std::hash<int>{}(jb.x);
        size_t h2 = std::hash<int>{}(jb.y);
        size_t h3 = std::hash<int>{}(jb.z);
        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
};
}

struct junction_pair {
    junction_box a;
    junction_box b;
    double dist;
};

class UnionFind {
private:
    std::unordered_map<junction_box, junction_box> parent;
    std::unordered_map<junction_box, int> sz;
    int count;
    std::priority_queue<int> size_pq;

public:
    UnionFind(std::vector<junction_box> boxes);
    junction_box find(junction_box p);
    void unite(junction_box p, junction_box q);
    int connected(junction_box p, junction_box q);
    int getCount();
    void populate_pq(std::vector<junction_box>);
    std::priority_queue<int> getSizePQ();
    std::unordered_map<junction_box, int> getSize();
};

#endif