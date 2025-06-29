#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <unordered_map>
#include <vector>
#include <string>
#include <queue>
#include <utility>
#include <climits>
using namespace std;


class Graph {
public:
    void addEdge(const string& u, const string& v, int w);
    bool loadFromCSV(const string& filename);
    pair<int, vector<string>> dijkstra(const string& src, const string& dest);

private:
    unordered_map<string, vector<pair<string, int>>> adj;
};

#endif
