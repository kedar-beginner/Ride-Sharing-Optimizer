#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include "graph.hpp"
#include "structs.hpp"
using namespace std;

vector<Driver> loadDrivers(const string& file) {
    ifstream f(file);
    vector<Driver> drivers;
    string name, location;
    while (f >> name >> location) {
        drivers.push_back({name, location});
    }
    return drivers;
}

Rider getRiderDetails() {
    Rider r;
    cout << "Enter Rider Name: ";
    cin >> r.name;
    cout << "Enter Pickup Node: ";
    cin >> r.pickup;
    cout << "Enter Drop Node: ";
    cin >> r.drop;
    return r;
}

void simulateRide(Graph& g) {
    Rider r = getRiderDetails();
    vector<Driver> drivers = loadDrivers("data/drivers.txt");

    int bestCost = numeric_limits<int>::max();
    vector<string> bestRoute;
    string bestDriver;

    for (auto& d : drivers) {
        auto [toPickupCost, path1] = g.dijkstra(d.location, r.pickup);
        auto [tripCost, path2] = g.dijkstra(r.pickup, r.drop);
        if (toPickupCost == -1 || tripCost == -1) continue;

        int totalCost = toPickupCost + tripCost;
        if (totalCost < bestCost) {
            bestCost = totalCost;
            bestDriver = d.name;
            bestRoute = path1;
            bestRoute.insert(bestRoute.end(), path2.begin() + 1, path2.end());
        }
    }

    if (bestDriver.empty()) {
        cout << "No route found to fulfill the request.\n";
        return;
    }

    cout << "\nAssigned Driver: " << bestDriver << "\nTotal Cost: " << bestCost << "\nRoute: ";
    for (const auto& node : bestRoute) cout << node << " ";
    cout << "\n";
}

int main() {
    Graph g;
    if (!g.loadFromCSV("data/city_graph.csv")) {
        cerr << "Failed to load city graph.\n";
        return 1;
    }

    while (true) {
        cout << "\nRide Sharing Optimizer Menu\n";
        cout << "1. Simulate New Ride\n";
        cout << "2. Exit\n";
        cout << "Choice: ";
        int choice;
        cin >> choice;

        if (choice == 1) simulateRide(g);
        else break;
    }

    return 0;
}
