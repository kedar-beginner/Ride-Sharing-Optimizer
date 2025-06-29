#include "graph.hpp"
#include <fstream>
#include <sstream>
#include <set>
#include <algorithm>
using namespace std;

void Graph::addEdge(const string& u, const string& v, int w) {
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w); // undirected
}

bool Graph::loadFromCSV(const string& filename) {
    ifstream file(filename);
    if (!file) return false;

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string u, v, weightStr;
        getline(ss, u, ',');
        getline(ss, v, ',');
        getline(ss, weightStr, ',');
        int w = stoi(weightStr);
        addEdge(u, v, w);
    }
    return true;
}

pair<int, vector<string>> Graph::dijkstra(const string& src, const string& dest) {
    unordered_map<string, int> dist;
    unordered_map<string, string> parent;
    for (auto& pair : adj) dist[pair.first] = INT_MAX;
    dist[src] = 0;

    using pii = pair<int, string>;
    priority_queue<pii, vector<pii>, greater<>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [cost, node] = pq.top(); pq.pop();

        for (auto& [neigh, weight] : adj[node]) {
            if (dist[neigh] > dist[node] + weight) {
                dist[neigh] = dist[node] + weight;
                parent[neigh] = node;
                pq.push({dist[neigh], neigh});
            }
        }
    }

    vector<string> path;
    if (dist[dest] == INT_MAX) return {-1, path};

    for (string at = dest; at != src; at = parent[at])
        path.push_back(at);
    path.push_back(src);
    reverse(path.begin(), path.end());

    return {dist[dest], path};
}
