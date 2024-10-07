#include <iostream>
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int id, u, v, weight;
};

int findMinCost(int start, const vector<Edge>& edges, int n, vector<int>& route) {
    vector<bool> visited(n, false);
    visited[start] = true;
    int totalCost = 0;
    int currentNode = start;

    for (int i = 0; i < n - 1; ++i) {
        int minCost = numeric_limits<int>::max();
        Edge* nextEdge = nullptr;

        for (const auto& edge : edges) {
            if ((edge.u == currentNode && !visited[edge.v]) || 
                (edge.v == currentNode && !visited[edge.u])) {
                if (edge.weight < minCost) {
                    minCost = edge.weight;
                    nextEdge = const_cast<Edge*>(&edge);
                }
            }
        }
        if (!nextEdge) {
            break;
        }

        visited[nextEdge->u] = true;
        visited[nextEdge->v] = true;
        totalCost += nextEdge->weight;
        currentNode = (nextEdge->u == currentNode) ? nextEdge->v : nextEdge->u;

        route.push_back(nextEdge->id);
    }

    for (const auto& edge : edges) {
        if ((edge.u == currentNode && edge.v == start) || (edge.v == currentNode && edge.u == start)) {
            totalCost += edge.weight;
            route.push_back(edge.id);
            break;
        }
    }
    return totalCost;
}

int main() {
    int n, e;
    cin >> n >> e; 

    vector<Edge> edges(e);
    for (int i = 0; i < e; ++i) {
        cin >> edges[i].id >> edges[i].u >> edges[i].v >> edges[i].weight;
    }
    int start; cin >> start;
    vector<int> route;
    int totalCost = findMinCost(start, edges, n, route);
    
    cout << "Cost: " << totalCost << endl;
    cout << "Route: ";
    for (size_t i = 0; i < route.size(); ++i) {
        cout << route[i];
        if (i < route.size() - 1) {
            cout << ", ";
        }
    }
    cout << endl;
    return 0;
}
